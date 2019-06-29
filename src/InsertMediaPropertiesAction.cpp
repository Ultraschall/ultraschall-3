////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
//
// The MIT License (MIT)
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
#include "TagWriterFactory.h"
#include "TimeUtilities.h"
#include "UIFileDialog.h"
#include "UIMessageSupervisor.h"
#include "ReaperProjectManager.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<InsertMediaPropertiesAction> action;

ServiceStatus InsertMediaPropertiesAction::Execute()
{
    PRECONDITION_RETURN(ValidateProject() == true, SERVICE_FAILURE);

    PRECONDITION_RETURN(ConfigureTargets() == true, SERVICE_FAILURE);
    PRECONDITION_RETURN(ConfigureSources() == true, SERVICE_FAILURE);

	// caution! requires ConfigureSources() to be called beforehand
    PRECONDITION_RETURN(ValidateChapterMarkers(chapterMarkers_) == true, SERVICE_FAILURE);

    ServiceStatus       status = SERVICE_FAILURE;
    UIMessageSupervisor supervisor;
    size_t              errorCount = 0;

    for(size_t i = 0; i < targets_.size(); i++)
    {
        ITagWriter* pTagWriter = TagWriterFactory::Create(targets_[i]);
        if(pTagWriter != 0)
        {
            if(pTagWriter->InsertProperties(targets_[i], mediaProperties_) == false)
            {
                UnicodeStringStream os;
                os << "Failed to insert tags into " << targets_[i] << ".";
                supervisor.RegisterError(os.str());
                errorCount++;
            }

            if(pTagWriter->InsertCoverImage(targets_[i], coverImage_) == false)
            {
                UnicodeStringStream os;
                os << "Failed to insert cover image into " << targets_[i] << ".";
                supervisor.RegisterError(os.str());
                errorCount++;
            }

            if(pTagWriter->ReplaceChapterMarkers(targets_[i], chapterMarkers_) == false)
            {
                UnicodeStringStream os;
                os << "Failed to insert chapter markers into " << targets_[i] << ".";
                supervisor.RegisterError(os.str());
                errorCount++;
            }

            SafeRelease(pTagWriter);
        }
    }

    if(0 == errorCount)
    {
        for(size_t i = 0; i < targets_.size(); i++)
        {
            UnicodeStringStream os;
            os << targets_[i] << " has been updated successfully.";
            supervisor.RegisterSuccess(os.str());
        }

        status = SERVICE_SUCCESS;
    }

    return status;
}

bool InsertMediaPropertiesAction::ConfigureSources()
{
    bool                result = false;
    UIMessageSupervisor supervisor;
    size_t              invalidAssetCount = 0;

    mediaProperties_.Clear();
    coverImage_.clear();
    chapterMarkers_.clear();

    mediaProperties_ = MediaProperties::ParseProjectNotes();
    if(mediaProperties_.Validate() == false)
    {
        supervisor.RegisterWarning("ID3v2 tags have not been defined yet.");
        invalidAssetCount++;
    }

    coverImage_ = FindCoverImage();
    if(coverImage_.empty() == true)
    {
        supervisor.RegisterWarning("Cover image is missing.");
        invalidAssetCount++;
    }

    chapterMarkers_ = ReaperProjectManager::Instance().CurrentProject().AllMarkers();
    if(chapterMarkers_.empty() == true)
    {
        supervisor.RegisterWarning("No chapters have been set.");
        invalidAssetCount++;
    }

    if(invalidAssetCount >= 3)
    {
        supervisor.RegisterError("Specify at least one ID3v2 tag, a cover image or a chapter marker.");
        result = false;
    }
    else
    {
        result = true;
    }

    return result;
} // namespace reaper

bool InsertMediaPropertiesAction::ConfigureTargets()
{
    UIMessageSupervisor supervisor;

    targets_.clear();

#ifdef ULTRASCHALL_ENABLE_MP4
    static const size_t MAX_FILE_EXTENSIONS                 = 3;
    static const char*  fileExtensions[MAX_FILE_EXTENSIONS] = {".mp3", ".mp4", ".m4a"};
#else  // #ifdef ULTRASCHALL_ENABLE_MP4
    static const size_t MAX_FILE_EXTENSIONS                 = 1;
    static const char*  fileExtensions[MAX_FILE_EXTENSIONS] = {".mp3"};
#endif // #ifdef ULTRASCHALL_ENABLE_MP4

    for(size_t i = 0; i < MAX_FILE_EXTENSIONS; i++)
    {
        UnicodeString targetName = CreateProjectPath(fileExtensions[i]);
        if(FileManager::FileExists(targetName) != false)
        {
            targets_.push_back(targetName);
        }
    }

    if(targets_.empty() == true)
    {
        supervisor.RegisterWarning("Ultraschall can't find a suitable media file. Please select an alternative media "
                                   "file from the file selection dialog after closing this message.");
        UIFileDialog        fileDialog("Select audio file");
        const UnicodeString target = fileDialog.BrowseForAudio();
        if(target.empty() == false)
        {
            targets_.push_back(target);
        }
    }

    return targets_.empty() == false;
}

UnicodeString InsertMediaPropertiesAction::FindCoverImage()
{
    UnicodeString coverImage;

    UnicodeStringArray       files;
    const UnicodeStringArray extensions{".jpg", ".jpeg", ".png"};
    for(size_t i = 0; i < extensions.size(); i++)
    {
        files.push_back(FileManager::AppendPath(GetProjectDirectory(), "cover") + extensions[i]);
        files.push_back(FileManager::AppendPath(GetProjectDirectory(), GetProjectName()) + extensions[i]);
    }

    const size_t imageIndex = FileManager::FileExists(files);
    if(imageIndex != -1)
    {
        coverImage = files[imageIndex];
    }

    return coverImage;
}

}} // namespace ultraschall::reaper
