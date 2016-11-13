////////////////////////////////////////////////////////////////////////////////
// 
// Copyright (c) 2016 Ultraschall (http://ultraschall.fm)
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

#include "SetChapterMarkerAction.h"
#include "CustomActionFactory.h"
#include "ProjectManager.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<SetChapterMarkerAction> action;

SetChapterMarkerAction::SetChapterMarkerAction()
{
}

SetChapterMarkerAction::~SetChapterMarkerAction()
{
}

const char* SetChapterMarkerAction::UniqueId()
{
   return "ULTRASCHALL_SET_CHAPTER_MARKER";
}

ServiceStatus SetChapterMarkerAction::CreateCustomAction(ICustomAction*& pCustomAction)
{
   pCustomAction = new SetChapterMarkerAction();
   PRECONDITION_RETURN(pCustomAction != 0, SERVICE_FAILURE);
   return SERVICE_SUCCESS;
}

const char* SetChapterMarkerAction::LocalizedName() const
{
   return "ULTRASCHALL: Set chapter marker";
}

ServiceStatus SetChapterMarkerAction::Execute()
{
   ProjectManager& projectManager = ProjectManager::Instance();
   Project currentProject = projectManager.CurrentProject();
   currentProject.InsertChapterMarker("<Insert chapter here>");

   return SERVICE_SUCCESS;
}

}
}

