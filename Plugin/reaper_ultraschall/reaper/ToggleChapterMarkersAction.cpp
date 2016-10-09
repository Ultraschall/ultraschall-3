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

#include "ToggleChapterMarkersAction.h"
#include "CustomActionFactory.h"

namespace ultraschall {
namespace reaper {

static DeclareCustomAction<ToggleChapterMarkersAction> action;

ToggleChapterMarkersAction::ToggleChapterMarkersAction()
{
	framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
	ServiceStatus status = resourceManager.RegisterLocalizedString(actionNameId_);
	if(ServiceSucceeded(status))
	{
		resourceManager.SetLocalizedString(actionNameId_, "en-EN", "ULTRASCHALL: Toggle chapter markers");
		resourceManager.SetLocalizedString(actionNameId_, "de-DE", "ULTRASCHALL: Kapitelmarken an- und ausschalten");
	}
}

ToggleChapterMarkersAction::~ToggleChapterMarkersAction()
{
	framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
	resourceManager.UnregisterLocalizedString(actionNameId_);
}

const char* ToggleChapterMarkersAction::UniqueId()
{
	return "ULTRASCHALL_TOGGLE_CHAPTER_MARKERS";
}

ServiceStatus ToggleChapterMarkersAction::CreateCustomAction(ICustomAction*& pCustomAction)
{
	pCustomAction = new ToggleChapterMarkersAction();
	PRECONDITION_RETURN(pCustomAction != 0, SERVICE_FAILURE);
	return SERVICE_SUCCESS;
}

const char* ToggleChapterMarkersAction::LocalizedName() const
{
	framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
	return resourceManager.GetLocalizedString(actionNameId_);
}

ServiceStatus ToggleChapterMarkersAction::Execute()
{
	ServiceStatus status = SERVICE_SUCCESS;
	return status;
}

}
}

