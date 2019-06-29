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

#include "InsertChapterMarkersAction.h"
#include "CustomActionFactory.h"
#include "FileManager.h"
#include "ReaperProjectManager.h"
#include "StringUtilities.h"
#include "UIFileDialog.h"
#include "UIMessageSupervisor.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<InsertChapterMarkersAction> action;

ServiceStatus InsertChapterMarkersAction::Execute()
{
    PRECONDITION_RETURN(ValidateProject() == true, SERVICE_FAILURE);

    PRECONDITION_RETURN(ConfigureSources() == true, SERVICE_FAILURE);
    PRECONDITION_RETURN(ConfigureTargets() == true, SERVICE_FAILURE);

    PRECONDITION_RETURN(ValidateChapterMarkers(chapterMarkers_) == true, SERVICE_FAILURE);

    ServiceStatus       status = SERVICE_FAILURE;
    UIMessageSupervisor supervisor;

    ReaperProjectManager& projectManager = ReaperProjectManager::Instance();
    ReaperProject         currentProject = projectManager.CurrentProject();

    size_t addedTags = 0;
    for(size_t i = 0; i < chapterMarkers_.size(); i++)
    {
        if(currentProject.InsertChapterMarker(chapterMarkers_[i].Name(), chapterMarkers_[i].Position()) == true)
        {
            addedTags++;
        }
        else
        {
            UnicodeStringStream os;
            os << "Chapter marker '" << chapterMarkers_[i].Name() << "' at position '"
               << SecondsToString(chapterMarkers_[i].Position()) << "' could not be added.";
            supervisor.RegisterError(os.str());
        }
    }

    if(chapterMarkers_.size() != addedTags)
    {
        UnicodeStringStream os;
        os << "Not all chapter markers were added.";
        supervisor.RegisterError(os.str());
    }

    return status;
}

bool InsertChapterMarkersAction::ConfigureTargets()
{
    UIMessageSupervisor supervisor;

    chapterMarkers_.clear();

    const UnicodeStringArray lines = FileManager::ReadTextFile(source_);
    if(lines.empty() == false)
    {
        for(size_t i = 0; i < lines.size(); i++)
        {
            const UnicodeStringArray items = UnicodeStringTokenize(lines[i], ' ');
            if(items.empty() == false)
            {
                const double position = StringToSeconds(items[0]);
                if(position >= 0)
                {
                    UnicodeString name;
                    if(items.size() > 1)
                    {
                        name = items[1];
                    }

                    for(size_t j = 2; j < items.size(); j++)
                    {
                        name += " " + items[j];
                    }

                    chapterMarkers_.push_back(Marker(position, name, 0));
                }
                else
                {
                    UnicodeStringStream os;
                    os << "Line " << (i + 1) << ": Invalid timestamp in '" << lines[i] << "'.";
                    supervisor.RegisterWarning(os.str());
                }
            }
            else
            {
                UnicodeStringStream os;
                os << "Line " << (i + 1) << ": Invalid format in '" << lines[i] << "'.";
                supervisor.RegisterError(os.str());
            }
        }
    }
    else
    {
        UnicodeStringStream os;
        os << "The file '" << source_ << "' does not contain chapter markers";
        supervisor.RegisterWarning(os.str());
    }

    return chapterMarkers_.empty() == false;
}

bool InsertChapterMarkersAction::ConfigureSources()
{
    source_.clear();

    UIFileDialog fileDialog("Import chapter markers");
    source_ = fileDialog.BrowseForChapters();
    return source_.empty() == false;
}

}} // namespace ultraschall::reaper
