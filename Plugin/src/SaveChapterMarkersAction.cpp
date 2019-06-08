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

#include "SaveChapterMarkersAction.h"
#include "CustomActionFactory.h"
#include "StringUtilities.h"
#include "FileManager.h"
#include "UIFileDialog.h"
#include "UIMessageSupervisor.h"
#include "ReaperProjectManager.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<SaveChapterMarkersAction> action;

ServiceStatus SaveChapterMarkersAction::Execute()
{
    PRECONDITION_RETURN(ValidateProject() == true, SERVICE_FAILURE);

    PRECONDITION_RETURN(ConfigureTargets() == true, SERVICE_FAILURE);
    PRECONDITION_RETURN(ConfigureSources() == true, SERVICE_FAILURE);

    // caution! requires ConfigureSources() to be called beforehand
    PRECONDITION_RETURN(ValidateChapterMarkers(chapterMarkers_) == true, SERVICE_FAILURE);

    ServiceStatus       status = SERVICE_FAILURE;
    UIMessageSupervisor supervisor;

    std::ofstream os(target_, std::ios::out);
    if(os.is_open() == true)
    {
        for(size_t i = 0; i < chapterMarkers_.size(); i++)
        {
            const UnicodeString timestamp = SecondsToString(chapterMarkers_[i].Position());
            const UnicodeString item      = timestamp + " " + chapterMarkers_[i].Name();
            os << item << std::endl;
        }

        os.close();

        supervisor.RegisterSuccess("The chapter markers have been saved successfully.");
        status = SERVICE_SUCCESS;
    }
    else
    {
        UnicodeStringStream os;
        os << "Failed to open " << target_ << ".";
        supervisor.RegisterError(os.str());
        status = SERVICE_FAILURE;
    }

    return status;
}

bool SaveChapterMarkersAction::ConfigureTargets()
{
    bool                result = false;
    UIMessageSupervisor supervisor;

    target_.clear();

    // TODO use SaveFileDialog instead of FolderBrowser
    UIFileDialog fileDialog("Export chapter markers", GetProjectDirectory());
    target_ = fileDialog.BrowseForDirectory();
    if(target_.empty() == false)
    {
        target_ += FileManager::PathSeparator() + GetProjectName() + ".chapters.txt";
        result = true;
    }
    else
    {
        supervisor.RegisterWarning("The export operation has been canceled.");
        target_.clear();
        result = false;
    }

    return result;
}

bool SaveChapterMarkersAction::ConfigureSources()
{
    bool                result = false;
    UIMessageSupervisor supervisor;
    size_t              invalidAssetCount = 0;

    chapterMarkers_ = ReaperProjectManager::Instance().CurrentProject().AllMarkers();
    if(chapterMarkers_.empty() == true)
    {
        supervisor.RegisterWarning("No chapters have been set.");
        invalidAssetCount++;
    }
    else
    {
        result = true;
    }

    if(invalidAssetCount >= 1)
    {
        UnicodeStringStream os;
        os << "Your project does not meet the minimum requirements for the export to continue. Specify at least one "
              "chapter marker.";
        supervisor.RegisterError(os.str());
        result = false;
    }

    return result;
}

}} // namespace ultraschall::reaper
