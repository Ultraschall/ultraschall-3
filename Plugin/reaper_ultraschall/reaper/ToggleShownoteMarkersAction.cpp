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

#include <ResourceManager.h>

#include "ToggleShownoteMarkersAction.h"
#include "CustomActionFactory.h"

namespace ultraschall {
namespace reaper {

static DeclareCustomAction<ToggleShownoteMarkersAction> action;

ToggleShownoteMarkersAction::ToggleShownoteMarkersAction()
{
	framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
	ServiceStatus status = resourceManager.RegisterLocalizedString(actionNameId_);
	if(ServiceSucceeded(status))
	{
		resourceManager.SetLocalizedString(actionNameId_, "en-EN", "ULTRASCHALL: Toggle shownote markers");
		resourceManager.SetLocalizedString(actionNameId_, "de-DE", "ULTRASCHALL: Shownotes an- und ausschalten");
	}
}

ToggleShownoteMarkersAction::~ToggleShownoteMarkersAction()
{
	framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
	resourceManager.UnregisterLocalizedString(actionNameId_);
}

const char* ToggleShownoteMarkersAction::UniqueId()
{
	return "ULTRASCHALL_TOGGLE_SHOWNOTE_MARKERS";
}

ServiceStatus ToggleShownoteMarkersAction::CreateCustomAction(ICustomAction*& pCustomAction)
{
	pCustomAction = new ToggleShownoteMarkersAction();
	PRECONDITION_RETURN(pCustomAction != 0, SERVICE_FAILURE);
	return SERVICE_SUCCESS;
}

const char* ToggleShownoteMarkersAction::LocalizedName() const
{
	framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
	return resourceManager.GetLocalizedString(actionNameId_);
}

ServiceStatus ToggleShownoteMarkersAction::Execute()
{
	ServiceStatus status = SERVICE_SUCCESS;
	return status;
}

}
}

