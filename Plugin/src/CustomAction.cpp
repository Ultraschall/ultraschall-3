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

#include "CustomAction.h"
#include "FileManager.h"
#include "ReaperProjectManager.h"
#include "StringUtilities.h"
#include "UIMessageSupervisor.h"

namespace ultraschall { namespace reaper {

bool CustomAction::ValidateCustomActionId(const int32_t id)
{
    return id != INVALID_CUSTOM_ACTION_ID;
}

bool CustomAction::ValidateProject()
{
    UIMessageSupervisor supervisor;

    const bool isValid = (GetProjectDirectory().empty() == false) && (GetProjectName().empty() == false);
    if(isValid == false)
    {
        supervisor.RegisterError("This action requires that you save the current project. Save the current project and "
                                 "execute the current action again.");
    }

    return isValid;
}

bool CustomAction::RegisterProject()
{
    bool registered = false;

    ReaperProjectManager& projectManager          = ReaperProjectManager::Instance();
    void*                 currentProjectReference = projectManager.CurrentProjectReference();
    if(currentProjectReference != nullptr)
    {
        const ReaperProject& currentProject = projectManager.LookupProject(currentProjectReference);
        if(ReaperProject::Validate(currentProject) == false)
        {
            registered = projectManager.InsertProject(currentProjectReference);
        }
        else
        {
            registered = true;
        }
    }

    return registered;
}

UnicodeString CustomAction::GetProjectDirectory()
{
    const ReaperProjectManager& projectManager = ReaperProjectManager::Instance();
    ReaperProject               currentProject = projectManager.CurrentProject();
    return currentProject.FolderName();
}

UnicodeString CustomAction::GetProjectName()
{
    const ReaperProjectManager& projectManager = ReaperProjectManager::Instance();
    ReaperProject               currentProject = projectManager.CurrentProject();
    return currentProject.Name();
}

UnicodeString CustomAction::CreateProjectPath(const UnicodeString& extension)
{
    UnicodeString path = FileManager::AppendPath(GetProjectDirectory(), GetProjectName());
    if(extension.empty() == false)
    {
        path += extension;
    }

    return path;
}

bool CustomAction::ValidateChapterMarkers(const MarkerArray& markers)
{
    UIMessageSupervisor supervisor;

    bool valid = true;

    for(size_t i = 0; i < markers.size(); i++)
    {
        const Marker&       current      = markers[i];
        const UnicodeString safeName     = current.Name();
        const double        safePosition = current.Position();

        ReaperProjectManager& projectManager = ReaperProjectManager::Instance();
        ReaperProject         currentProject = projectManager.CurrentProject();
        if(currentProject.IsValidPosition(current.Position()) == false)
        {
            UnicodeStringStream os;
            os << "Chapter marker '" << ((safeName.empty() == false) ? safeName : UnicodeString("Unknown"))
               << "' is out of track range.";
            supervisor.RegisterError(os.str());
            valid = false;
        }

        if(current.Name().empty() == true)
        {
            UnicodeStringStream os;
            os << "Chapter marker at '" << SecondsToString(safePosition) << "' has no name.";
            supervisor.RegisterError(os.str());
            valid = false;
        }
    }

    return valid;
}

}} // namespace ultraschall::reaper
