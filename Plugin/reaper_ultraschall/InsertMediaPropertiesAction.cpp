////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 Ultraschall (http://ultraschall.fm)
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
#include "Framework.h"
#include "ITagWriter.h"
#include "InsertMediaPropertiesAction.h"
#include "NotificationWindow.h"
#include "StringUtilities.h"
#include "SystemProperties.h"
#include "TimeUtilities.h"

namespace ultraschall { namespace reaper {

class ErrorRecord
{
public:
    ErrorRecord(const std::string& target, const std::string& message) : target_(target), message_(message) {}

    inline const std::string& Target() const
    {
        return target_;
    }

    inline const std::string& Message() const
    {
        return message_;
    }

private:
    std::string target_;
    std::string message_;
};

static DeclareCustomAction<InsertMediaPropertiesAction> action;

ServiceStatus InsertMediaPropertiesAction::Execute()
{
    ProjectManager& projectManager = ProjectManager::Instance();
    Project         currentProject = projectManager.CurrentProject();
    if (Project::Validate(currentProject) == true)
    {
        ResetAssets();

        targetNames_ = FindTargetFiles(currentProject);
        if (targetNames_.empty() == true)
        {
            std::stringstream os;
            os << "Ultraschall can't find a suitable media file.";
            os << "\r\n\r\n";
            os << "Please select an alternative media file from the file selection dialog after closing this message.";
            os << "\r\n\r\n";

            NotificationWindow::Show(os.str(), false);

            const std::string targetName = FileManager::BrowseForTargetAudioFiles("Select media file...");
            if (targetName.empty() == false)
            {
                targetNames_.push_back(targetName);
            }
        }

        if ((targetNames_.empty() == false) && (ConfigureAssets() == true))
        {
            std::vector<std::string> errorMessages;
            if (ValidateChapterMarkers(errorMessages) == true)
            {
                std::vector<ErrorRecord> errorRecords;

                for (size_t i = 0; i < targetNames_.size(); i++)
                {
                    const std::string& targetName = targetNames_[i];

                    ITagWriter* pTagWriter = CreateTagWriter(targetNames_[i]);
                    if (pTagWriter != 0)
                    {
                        BasicMediaInformation properties = BasicMediaInformation::ParseString(currentProject.Notes());
                        if (pTagWriter->InsertStandardProperties(targetName, properties) == false)
                        {
                            errorRecords.push_back(ErrorRecord(targetName, "Failed to insert tags."));
                        }

                        if (cover_.empty() == false)
                        {
                            if (pTagWriter->InsertCoverImage(targetName, cover_) == false)
                            {
                                errorRecords.push_back(ErrorRecord(targetName, "Failed to insert cover image."));
                            }
                        }

                        if (chapters_.empty() == false)
                        {
                            if (pTagWriter->InsertChapterMarkers(targetName, chapters_, true) == false)
                            {
                                errorRecords.push_back(ErrorRecord(targetName, "Failed to insert chapter markers."));
                            }
                        }

                        framework::SafeRelease(pTagWriter);
                    }
                }

                if (errorRecords.size() > 0)
                {
                    for (size_t j = 0; j < errorRecords.size(); j++)
                    {
                        std::stringstream os;
                        os << "Ultraschall found the following errors while processing media files:";
                        os << "\r\n\r\n";
                        os << FileManager::StripPath(errorRecords[j].Target()) << ": " << errorRecords[j].Message() << "\r\n";
                        os << "\r\n\r\n";

                        NotificationWindow::Show(os.str(), true);
                    }
                }
                else
                {
                    if (SafetyMode::IsBasic() == true)
                    {
                        std::stringstream os;
                        os << "The following media files have been updated successfully:\r\n\r\n";
                        for (size_t k = 0; k < targetNames_.size(); k++)
                        {
                            os << FileManager::StripPath(targetNames_[k]);
                            if (k < (targetNames_.size() - 1))
                            {
                                os << "\r\n";
                            }
                        }
                        os << "\r\n\r\n";

                        NotificationWindow::Show(os.str(), false);
                    }
                }
            }
            else
            {
                if (SafetyLevel::IsStrict() == true)
                {
                    if (errorMessages.empty() == false)
                    {
                        std::ostringstream os;
                        os << "Ultraschall failed to validate chapter markers.";
                        os << "\r\n\r\n";
                        for (size_t l = 0; l < errorMessages.size(); l++)
                        {
                            os << errorMessages[l];
                        }
                        os << "\r\n\r\n";

                        NotificationWindow::Show(os.str(), true);
                    }
                }
            }
        }
    }
    else
    {
        NotificationWindow::Show("The REAPER project must be saved before the export can continue", true);
    }

    return SERVICE_SUCCESS;
}

std::vector<std::string> InsertMediaPropertiesAction::FindTargetFiles(const Project& project)
{
    std::vector<std::string> targetNames;

    const std::string projectFolder = project.FolderName();
    const std::string projectName   = project.Name();

    PRECONDITION_RETURN(projectFolder.empty() == false, targetNames);
    PRECONDITION_RETURN(projectName.empty() == false, targetNames);

    static const size_t MAX_FILE_EXTENSIONS                 = 3;
    static const char*  fileExtensions[MAX_FILE_EXTENSIONS] = {"mp3", "mp4", "m4a"};
    for (size_t i = 0; i < MAX_FILE_EXTENSIONS; i++)
    {
        std::string targetName = FileManager::AppendPath(projectFolder, projectName) + "." + fileExtensions[i];
        if (FileManager::FileExists(targetName) != false)
        {
            targetNames.push_back(targetName);
        }
    }

    return targetNames;
}

std::string InsertMediaPropertiesAction::FindCoverImage(const Project& project)
{
    const std::string projectFolder = project.FolderName();
    const std::string projectName   = project.Name();

    PRECONDITION_RETURN(projectFolder.empty() == false, std::string());
    PRECONDITION_RETURN(projectName.empty() == false, std::string());

    std::string coverImage;

    std::vector<std::string> imageNames;
    imageNames.push_back(FileManager::AppendPath(projectFolder, "cover") + ".jpg");
    imageNames.push_back(FileManager::AppendPath(projectFolder, "cover") + ".jpeg");
    imageNames.push_back(FileManager::AppendPath(projectFolder, "cover") + ".png");
    imageNames.push_back(FileManager::AppendPath(projectFolder, projectName) + ".jpg");
    imageNames.push_back(FileManager::AppendPath(projectFolder, projectName) + ".jpeg");
    imageNames.push_back(FileManager::AppendPath(projectFolder, projectName) + ".png");
    const size_t imageIndex = FileManager::FileExists(imageNames);
    if (imageIndex != -1)
    {
        coverImage = imageNames[imageIndex];
    }

    return coverImage;
}

ITagWriter* InsertMediaPropertiesAction::CreateTagWriter(const std::string& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, 0);
    PRECONDITION_RETURN(targetName.length() > 4, 0);

    ITagWriter*       tagWriter  = 0;
    const TARGET_TYPE targetType = EvaluateFileType(targetName);
    if (targetType == MP3_TARGET)
    {
        tagWriter = new MP3TagWriter();
    }
    else if (targetType == MP4_TARGET)
    {
        tagWriter = new MP4TagWriter();
    }

    return tagWriter;
}

std::string InsertMediaPropertiesAction::NormalizeTargetName(const std::string& targetName)
{
    std::string firstStage  = targetName;
    std::string secondStage = framework::StringTrimRight(firstStage);
    return framework::StringLowercase(secondStage);
}

InsertMediaPropertiesAction::TARGET_TYPE InsertMediaPropertiesAction::EvaluateFileType(const std::string& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, INVALID_TARGET_TYPE);

    TARGET_TYPE       type             = INVALID_TARGET_TYPE;
    const std::string cookedTargetName = NormalizeTargetName(targetName);
    const size_t      extensionOffset  = targetName.rfind(".");
    if (extensionOffset != std::string::npos)
    {
        const std::string fileExtension = targetName.substr(extensionOffset + 1, targetName.length() - extensionOffset);
        if (fileExtension.empty() == false)
        {
            if (fileExtension == "mp3")
            {
                type = MP3_TARGET;
            }
            else if (fileExtension == "mp4")
            {
                type = MP4_TARGET;
            }
            else if (fileExtension == "m4a")
            {
                type = MP4_TARGET;
            }
        }
    }

    return type;
}

bool InsertMediaPropertiesAction::ConfigureAssets()
{
    bool                     result = false;
    std::vector<std::string> messages;
    size_t                   invalidAssetCount = 0;

    ProjectManager& projectManager = ProjectManager::Instance();
    Project         currentProject = projectManager.CurrentProject();
    if (Project::Validate(currentProject) == true)
    {
        id3v2_ = BasicMediaInformation::ParseString(currentProject.Notes());
        if (id3v2_.Validate() == false)
        {
            const std::string message = "ID3v2 tags have not been defined yet.";
            messages.push_back(message);
            invalidAssetCount++;
        }

        cover_ = FindCoverImage(currentProject);
        if (cover_.empty() == true)
        {
            const std::string message = "Cover image is missing.";
            messages.push_back(message);
            invalidAssetCount++;
        }

        chapters_ = currentProject.QueryAllMarkers();
        if (chapters_.empty() == true)
        {
            const std::string message = "No chapters have been set.";
            messages.push_back(message);
            invalidAssetCount++;
        }

        if (SafetyLevel::IsStrict() == true)
        {
            if (invalidAssetCount >= 3)
            {
                std::stringstream os;
                os << "Your project does not meet the minimum requirements for the export to continue.";
                os << "\r\n\r\n";
                os << "Specify at least one ID3v2 tag, a cover image or a chapter marker.";
                os << "\r\n\r\n";

                NotificationWindow::Show(os.str(), true);

                result = false;
            }
            else if (messages.size() > 0)
            {
                std::stringstream os;

                os << "Ultraschall has found the following non-critical issues and will continue after you close "
                      "this message:\r\n\r\n";
                for (size_t i = 0; i < messages.size(); i++)
                {
                    os << (i + 1) << ") " << messages[i] << "\r\n";
                }

                os << "\r\n\r\n";

                NotificationWindow::Show(os.str(), false);

                result = true;
            }
            else
            {
                result = true;
            }
        }
        else
        {
            result = true;
        }
    }
    else
    {
        NotificationWindow::Show("The REAPER project must be saved before the export can continue", true);

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

bool InsertMediaPropertiesAction::ValidateChapterMarkers(std::vector<std::string>& errorMessages)
{
    bool valid = true;
    errorMessages.clear();

    if (SafetyLevel::IsStrict() == true)
    {
        for (size_t i = 0; i < chapters_.size(); i++)
        {
            const Marker&     current      = chapters_[i];
            const std::string safeName     = current.Name();
            const double      safePosition = current.Position();

            ProjectManager& projectManager = ProjectManager::Instance();
            Project         currentProject = projectManager.CurrentProject();
            if (currentProject.IsValidPosition(current.Position()) == false)
            {
                std::stringstream os;
                os << "Chapter marker '" << ((safeName.empty() == false) ? safeName : std::string("Unknown")) << "' is out of track range.";
                os << "\r\n";
                errorMessages.push_back(os.str());

                valid = false;
            }

            if (current.Name().empty() == true)
            {
                std::stringstream os;
                os << "Chapter marker at '" << framework::SecondsToString(safePosition) << "' has no name.";
                os << "\r\n";
                errorMessages.push_back(os.str());

                valid = false;
            }
        }
    }

    return valid;
}
}} // namespace ultraschall::reaper
