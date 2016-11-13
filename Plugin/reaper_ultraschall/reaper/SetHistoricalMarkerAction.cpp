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

#include "SetHistoricalMarkerAction.h"
#include "CustomActionFactory.h"
#include "ProjectManager.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<SetHistoricalMarkerAction> action;

SetHistoricalMarkerAction::SetHistoricalMarkerAction()
{
}

SetHistoricalMarkerAction::~SetHistoricalMarkerAction()
{
}

const char* SetHistoricalMarkerAction::UniqueId()
{
   return "ULTRASCHALL_SET_HISTORICAL_CHAPTER_MARKER";
}

ServiceStatus SetHistoricalMarkerAction::CreateCustomAction(ICustomAction*& pCustomAction)
{
   pCustomAction = new SetHistoricalMarkerAction();
   PRECONDITION_RETURN(pCustomAction != 0, SERVICE_FAILURE);
   return SERVICE_SUCCESS;
}

const char* SetHistoricalMarkerAction::LocalizedName() const
{
   return "ULTRASCHALL: Set chapter marker back in time (2 min)";
}

ServiceStatus SetHistoricalMarkerAction::Execute()
{
   ProjectManager& projectManager = ProjectManager::Instance();
   Project currentProject = projectManager.CurrentProject();
   const double currentPosition = currentProject.CurrentPosition();
   currentProject.InsertHistoricalMarker();

   return SERVICE_SUCCESS;
}

}
}

