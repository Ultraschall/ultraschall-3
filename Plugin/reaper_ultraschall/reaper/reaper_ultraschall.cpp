////////////////////////////////////////////////////////////////////////////////
// 
// Copyright (c) 2014-2015 Ultraschall (http://ultraschall.fm)
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

#include <ServiceStatus.h>

#include "Application.h"
#include "NotificationWindow.h"
#include "ReaperEntryPoints.h"
#include "InvalidEntryPointException.h"

#include "CustomActionManager.h"

#include "AboutAction.h"
#include "UpdateCheckAction.h"

#include "InsertChapterMarkersAction.h"
#include "SaveChapterMarkersAction.h"
#include "SaveChapterMarkersToProjectAction.h"

#include "ToggleChapterMarkersAction.h"
#include "ToggleEditMarkersAction.h"
#include "ToggleShownoteMarkersAction.h"

#include "CloseProjectCommand.h"
#include "OpenProjectCommand.h"
#include "SaveProjectCommand.h"

namespace reaper = ultraschall::reaper;

extern "C"
{
	REAPER_PLUGIN_DLL_EXPORT int REAPER_PLUGIN_ENTRYPOINT(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t *pPluginInfo)
	{
		reaper::Application& application = reaper::Application::Instance();

		if(pPluginInfo != 0)
		{
			static bool started = false;
			if(false == started)
			{
				try
				{
					reaper::ReaperEntryPoints::Setup(instance, pPluginInfo);

					if(ServiceSucceeded(application.Configure()))
					{
						if(ServiceSucceeded(application.Start()))
						{
                     application.RegisterCustomAction<reaper::AboutAction>();
                     application.RegisterCustomAction<reaper::UpdateCheckAction>();

							application.RegisterCustomAction<reaper::InsertChapterMarkersAction>();
							application.RegisterCustomAction<reaper::SaveChapterMarkersAction>();
							application.RegisterCustomAction<reaper::SaveChapterMarkersToProjectAction>();

							application.RegisterCustomAction<reaper::ToggleChapterMarkersAction>();
							application.RegisterCustomAction<reaper::ToggleEditMarkersAction>();
							application.RegisterCustomAction<reaper::ToggleShownoteMarkersAction>();

                     application.RegisterCommand<reaper::CloseProjectCommand>(40860);
                     application.RegisterCommand<reaper::OpenProjectCommand>(40025);
                     application.RegisterCommand<reaper::SaveProjectCommand>(40026);

							// run the update action on startup
							application.InvokeCustomAction<reaper::UpdateCheckAction>();
						}
					}
				}
				catch(reaper::InvalidEntryPointException&)
				{
					std::string errorReason = "\
You are trying to load a version of REAPER that is not compatible to Ultraschall 2.";

					reaper::NotificationWindow::Show("Ultraschall failed to load!", errorReason, true);
					return 0;
				}

				started = true;
			}

			return 1;
		}
		else
		{
			static bool stopped = false;
			if(false == stopped)
			{
				application.Stop();
				stopped = true;
			}

			return 0;
		}
	}
}

#ifdef WIN32
BOOL APIENTRY DllMain(HMODULE, ULONG ul_reason_for_call, LPVOID)
{
	switch(ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
#endif

