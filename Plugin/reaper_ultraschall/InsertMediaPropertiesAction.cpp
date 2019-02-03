////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include "CustomActionFactory.h"
#include "FileManager.h"
#include "ITagWriter.h"
#include "InsertMediaPropertiesAction.h"
#include "StringUtilities.h"
#include "SystemProperties.h"
#include "TimeUtilities.h"
#include "UIFileDialog.h"
#include "UIMessageDialog.h"

namespace ultraschall { namespace reaper {

class ErrorRecord
{
public:
    ErrorRecord(const UnicodeString& target, const UnicodeString& message) : target_(target), message_(message) {}

    inline const UnicodeString& Target() const
    {
        return target_;
    }

    inline const UnicodeString& Message() const
    {
        return message_;
    }

private:
    UnicodeString target_;
    UnicodeString message_;
};

static DeclareCustomAction<InsertMediaPropertiesAction> action;

ServiceStatus InsertMediaPropertiesAction::Execute()
{
    ProjectManager& projectManager = ProjectManager::Instance();
    Project         currentProject = projectManager.CurrentProject();
    if(Project::Validate(currentProject) == true)
    {
        ResetAssets();

        targetNames_ = FindTargetFiles(currentProject);
#ifndef ULTRASCHALL_BROADCASTER
        if(targetNames_.empty() == true)
        {
            std::stringstream os;
            os << "Ultraschall can't find a suitable media file.";
            os << "\r\n\r\n";
            os << "Please select an alternative media file from the file selection dialog after closing this message.";
            os << "\r\n\r\n";

            UIMessageDialog::Show(os.str());

            UIFileDialog        fileDialog("Select audio file");
            const UnicodeString targetName = fileDialog.BrowseForAudio();
            if(targetName.empty() == false)
            {
                targetNames_.push_back(targetName);
            }
        }
#endif // #ifndef ULTRASCHALL_BROADCASTER

        if((targetNames_.empty() == false) && (ConfigureAssets() == true))
        {
            UnicodeStringArray errorMessages;
            if(ValidateChapterMarkers(errorMessages) == true)
            {
                std::vector<ErrorRecord> errorRecords;

                for(size_t i = 0; i < targetNames_.size(); i++)
                {
                    const UnicodeString& targetName = targetNames_[i];

                    ITagWriter* pTagWriter = CreateTagWriter(targetNames_[i]);
                    if(pTagWriter != 0)
                    {
                        BasicMediaInformation properties = BasicMediaInformation::ParseString(currentProject.Notes());
                        if(pTagWriter->InsertProperties(targetName, properties) == false)
                        {
                            errorRecords.push_back(ErrorRecord(targetName, "Failed to insert tags."));
                        }

                        if(cover_.empty() == false)
                        {
                            if(pTagWriter->InsertCoverImage(targetName, cover_) == false)
                            {
                                errorRecords.push_back(ErrorRecord(targetName, "Failed to insert cover image."));
                            }
                        }

                        if(chapters_.empty() == false)
                        {
                            if(pTagWriter->ReplaceChapterMarkers(targetName, chapters_) == false)
                            {
                                errorRecords.push_back(ErrorRecord(targetName, "Failed to insert chapter markers."));
                            }
                        }

                        SafeRelease(pTagWriter);
                    }
                }

                if(errorRecords.size() > 0)
                {
#ifndef ULTRASCHALL_BROADCASTER
                    for(size_t j = 0; j < errorRecords.size(); j++)
                    {
                        std::stringstream os;
                        os << "Ultraschall found the following errors while processing media files:";
                        os << "\r\n\r\n";
                        os << FileManager::StripPath(errorRecords[j].Target()) << ": " << errorRecords[j].Message()
                           << "\r\n";
                        os << "\r\n\r\n";

                        UIMessageDialog::ShowError(os.str());
                    }
#endif // #ifndef ULTRASCHALL_BROADCASTER
                }
                else
                {
#ifndef ULTRASCHALL_BROADCASTER

                    std::stringstream os;
                    os << "The following media files have been updated successfully:\r\n\r\n";
                    for(size_t k = 0; k < targetNames_.size(); k++)
                    {
                        os << FileManager::StripPath(targetNames_[k]);
                        if(k < (targetNames_.size() - 1))
                        {
                            os << "\r\n";
                        }
                    }
                    os << "\r\n\r\n";

                    UIMessageDialog::Show(os.str());
#endif // #ifndef ULTRASCHALL_BROADCASTER
                }
            }
            else
            {
                if(errorMessages.empty() == false)
                {
#ifndef ULTRASCHALL_BROADCASTER
                    std::ostringstream os;
                    os << "Ultraschall failed to validate chapter markers.";
                    os << "\r\n\r\n";
                    for(size_t l = 0; l < errorMessages.size(); l++)
                    {
                        os << errorMessages[l];
                    }
                    os << "\r\n\r\n";

                    UIMessageDialog::ShowError(os.str());
#endif // #ifndef ULTRASCHALL_BROADCASTER
                }
            }
        }
    }
    else
    {
        UIMessageDialog::ShowError("The REAPER project must be saved before the export can continue");
    }

    return SERVICE_SUCCESS;
}

UnicodeStringArray InsertMediaPropertiesAction::FindTargetFiles(const Project& project)
{
    UnicodeStringArray targetNames;

    const UnicodeString projectFolder = project.FolderName();
    const UnicodeString projectName   = project.Name();

    PRECONDITION_RETURN(projectFolder.empty() == false, targetNames);
    PRECONDITION_RETURN(projectName.empty() == false, targetNames);

    static const size_t MAX_FILE_EXTENSIONS                 = 3;
    static const char*  fileExtensions[MAX_FILE_EXTENSIONS] = {"mp3", "mp4", "m4a"};
    for(size_t i = 0; i < MAX_FILE_EXTENSIONS; i++)
    {
        UnicodeString targetName = FileManager::AppendPath(projectFolder, projectName) + "." + fileExtensions[i];
        if(FileManager::FileExists(targetName) != false)
        {
            targetNames.push_back(targetName);
        }
    }

    return targetNames;
}

UnicodeString InsertMediaPropertiesAction::FindCoverImage(const Project& project)
{
    const UnicodeString projectFolder = project.FolderName();
    const UnicodeString projectName   = project.Name();

    PRECONDITION_RETURN(projectFolder.empty() == false, UnicodeString());
    PRECONDITION_RETURN(projectName.empty() == false, UnicodeString());

    UnicodeString coverImage;

    UnicodeStringArray imageNames;
    imageNames.push_back(FileManager::AppendPath(projectFolder, "cover") + ".jpg");
    imageNames.push_back(FileManager::AppendPath(projectFolder, "cover") + ".jpeg");
    imageNames.push_back(FileManager::AppendPath(projectFolder, "cover") + ".png");
    imageNames.push_back(FileManager::AppendPath(projectFolder, projectName) + ".jpg");
    imageNames.push_back(FileManager::AppendPath(projectFolder, projectName) + ".jpeg");
    imageNames.push_back(FileManager::AppendPath(projectFolder, projectName) + ".png");
    const size_t imageIndex = FileManager::FileExists(imageNames);
    if(imageIndex != -1)
    {
        coverImage = imageNames[imageIndex];
    }

    return coverImage;
}

ITagWriter* InsertMediaPropertiesAction::CreateTagWriter(const UnicodeString& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, 0);
    PRECONDITION_RETURN(targetName.length() > 4, 0);

    ITagWriter*       tagWriter  = 0;
    const TARGET_TYPE targetType = EvaluateFileType(targetName);
    if(targetType == MP3_TARGET)
    {
        tagWriter = new MP3TagWriter();
    }
    else if(targetType == MP4_TARGET)
    {
        tagWriter = new MP4TagWriter();
    }

    return tagWriter;
}

UnicodeString InsertMediaPropertiesAction::NormalizeTargetName(const UnicodeString& targetName)
{
    UnicodeString firstStage  = targetName;
    UnicodeString secondStage = StringTrimRight(firstStage);
    return StringLowercase(secondStage);
}

InsertMediaPropertiesAction::TARGET_TYPE InsertMediaPropertiesAction::EvaluateFileType(const UnicodeString& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, INVALID_TARGET_TYPE);

    TARGET_TYPE         type             = INVALID_TARGET_TYPE;
    const UnicodeString cookedTargetName = NormalizeTargetName(targetName);
    const size_t        extensionOffset  = targetName.rfind(".");
    if(extensionOffset != UnicodeString::npos)
    {
        const UnicodeString fileExtension
            = targetName.substr(extensionOffset + 1, targetName.length() - extensionOffset);
        if(fileExtension.empty() == false)
        {
            if(fileExtension == "mp3")
            {
                type = MP3_TARGET;
            }
            else if(fileExtension == "mp4")
            {
                type = MP4_TARGET;
            }
            else if(fileExtension == "m4a")
            {
                type = MP4_TARGET;
            }
        }
    }

    return type;
}

bool InsertMediaPropertiesAction::ConfigureAssets()
{
    bool               result = false;
    UnicodeStringArray messages;
    size_t             invalidAssetCount = 0;

    ProjectManager& projectManager = ProjectManager::Instance();
    Project         currentProject = projectManager.CurrentProject();
    if(Project::Validate(currentProject) == true)
    {
        id3v2_ = BasicMediaInformation::ParseString(currentProject.Notes());
        if(id3v2_.Validate() == false)
        {
            const UnicodeString message = "ID3v2 tags have not been defined yet.";
            messages.push_back(message);
            invalidAssetCount++;
        }

        cover_ = FindCoverImage(currentProject);
        if(cover_.empty() == true)
        {
            const UnicodeString message = "Cover image is missing.";
            messages.push_back(message);
            invalidAssetCount++;
        }

        chapters_ = currentProject.AllMarkers();
        if(chapters_.empty() == true)
        {
            const UnicodeString message = "No chapters have been set.";
            messages.push_back(message);
            invalidAssetCount++;
        }

        if(invalidAssetCount >= 3)
        {
#ifndef ULTRASCHALL_BROADCASTER
            std::stringstream os;
            os << "Your project does not meet the minimum requirements for the export to continue.";
            os << "\r\n\r\n";
            os << "Specify at least one ID3v2 tag, a cover image or a chapter marker.";
            os << "\r\n\r\n";

            UIMessageDialog::ShowError(os.str());
#endif // #ifndef ULTRASCHALL_BROADCASTER
            result = false;
        }
        else if(messages.size() > 0)
        {
#ifndef ULTRASCHALL_BROADCASTER
            std::stringstream os;

            os << "Ultraschall has found the following non-critical issues and will continue after you close "
                  "this message:\r\n\r\n";
            for(size_t i = 0; i < messages.size(); i++)
            {
                os << (i + 1) << ") " << messages[i] << "\r\n";
            }

            os << "\r\n\r\n";

            UIMessageDialog::Show(os.str());
#endif // #ifndef ULTRASCHALL_BROADCASTER
            result = true;
        }
        else
        {
            result = true;
        }
    }
    else
    {
#ifndef ULTRASCHALL_BROADCASTER
        UIMessageDialog::ShowError("The REAPER project must be saved before the export can continue");
#endif // #ifndef ULTRASCHALL_BROADCASTER
        result = false;
    }

    return result;
}

void InsertMediaPropertiesAction::ResetAssets()
{
    targetNames_.clear();
    id3v2_.Reset();
    cover_.clear();
    chapters_.clear();
}

bool InsertMediaPropertiesAction::ValidateChapterMarkers(UnicodeStringArray& errorMessages)
{
    bool valid = true;
    errorMessages.clear();

    for(size_t i = 0; i < chapters_.size(); i++)
    {
        const Marker&       current      = chapters_[i];
        const UnicodeString safeName     = current.Name();
        const double        safePosition = current.Position();

        ProjectManager& projectManager = ProjectManager::Instance();
        Project         currentProject = projectManager.CurrentProject();
        if(currentProject.IsValidPosition(current.Position()) == false)
        {
            std::stringstream os;
            os << "Chapter marker '" << ((safeName.empty() == false) ? safeName : UnicodeString("Unknown"))
               << "' is out of track range.";
            os << "\r\n";
            errorMessages.push_back(os.str());

            valid = false;
        }

        if(current.Name().empty() == true)
        {
            std::stringstream os;
            os << "Chapter marker at '" << SecondsToString(safePosition) << "' has no name.";
            os << "\r\n";
            errorMessages.push_back(os.str());

            valid = false;
        }
    }

    return valid;
}
}} // namespace ultraschall::reaper
