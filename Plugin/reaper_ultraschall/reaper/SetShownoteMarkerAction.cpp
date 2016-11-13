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

#include "SetShownoteMarkerAction.h"
#include "Application.h"
#include "ProjectManager.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<SetShownoteMarkerAction> action;

SetShownoteMarkerAction::SetShownoteMarkerAction()
{
}

SetShownoteMarkerAction::~SetShownoteMarkerAction()
{
}

const char* SetShownoteMarkerAction::UniqueId()
{
   return "ULTRASCHALL_SET_SHOWNOTE_MARKER";
}

ServiceStatus SetShownoteMarkerAction::CreateCustomAction(ICustomAction*& pCustomAction)
{
   pCustomAction = new SetShownoteMarkerAction();
   PRECONDITION_RETURN(pCustomAction != 0, SERVICE_FAILURE);
   return SERVICE_SUCCESS;
}

const char* SetShownoteMarkerAction::LocalizedName() const
{
   return "ULTRASCHALL: Set shownote marker";
}

ServiceStatus SetShownoteMarkerAction::Execute()
{
   ServiceStatus status = SERVICE_FAILURE;
   
   ProjectManager& projectManager = ProjectManager::Instance();
   Project currentProject = projectManager.CurrentProject();
   currentProject.InsertShownoteMarker();
   return status;
}

}
}

