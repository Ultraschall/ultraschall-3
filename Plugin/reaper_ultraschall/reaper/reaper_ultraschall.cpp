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

#include <TraceUtilities.h>
#include <ServiceStatus.h>

#include "Application.h"
#include "NotificationWindow.h"
#include "ReaperEntryPoints.h"

#include "CustomActionManager.h"

#include "InsertChapterMarkersAction.h"
#include "SaveChapterMarkersAction.h"
#include "SaveChapterMarkersToProjectAction.h"
#include "InsertMP3ChapterMarkersAction.h"
#include "SystemProperties.h"

namespace reaper = ultraschall::reaper;

extern "C"
{
	REAPER_PLUGIN_DLL_EXPORT int REAPER_PLUGIN_ENTRYPOINT(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t *pPluginInfo)
	{
		reaper::Application& application = reaper::Application::Instance();

		if(pPluginInfo != 0)
		{
         Trace0(TRACE_LEVEL_INFO, "Ultraschall is starting-up...");

			static bool started = false;
			if(false == started)
			{
            if(reaper::ReaperEntryPoints::Setup(instance, pPluginInfo) == true)
            {
               Trace0(TRACE_LEVEL_INFO, "REAPER connection established.");

               if(reaper::QuerySetPluginVersion() == true)
               {
                  Trace0(TRACE_LEVEL_INFO, "Theme/Plugin versions successfully matched.");

                  if(ServiceSucceeded(application.Configure()))
                  {
                     if(ServiceSucceeded(application.Start()))
                     {
                        application.RegisterCustomAction<reaper::InsertChapterMarkersAction>();
                        Trace0(TRACE_LEVEL_INFO, "'InsertChapterMarkersAction' activated.");

                        application.RegisterCustomAction<reaper::SaveChapterMarkersAction>();
                        Trace0(TRACE_LEVEL_INFO, "'SaveChapterMarkersAction' activated.");

                        application.RegisterCustomAction<reaper::SaveChapterMarkersToProjectAction>();
                        Trace0(TRACE_LEVEL_INFO, "'SaveChapterMarkersToProjectAction' activated.");

                        application.RegisterCustomAction<reaper::InsertMP3ChapterMarkersAction>();
                        Trace0(TRACE_LEVEL_INFO, "'InsertMP3ChapterMarkersAction' activated.");

                        Trace0(TRACE_LEVEL_INFO, "Ultraschall is running.");

                        started = true;
                     }
                  }
               }
               else
               {
                  Trace0(TRACE_LEVEL_ERROR, "Failed to match Theme/Plugin versions.");
               }

            }
            else
            {
               Trace0(TRACE_LEVEL_ERROR, "Failed to establish REAPER connection.");
               std::string errorReason = "You are trying to load a version of REAPER that is not compatible to Ultraschall 3.";
               reaper::NotificationWindow::Show("Ultraschall failed to load!", errorReason, true);
            }
			}

         Trace0(TRACE_LEVEL_INFO, "done.");
         
         return 1;
		}
		else
		{
         Trace0(TRACE_LEVEL_INFO, "Ultraschall is shutting down...");
         
         static bool stopped = false;
			if(false == stopped)
			{
				application.Stop();
				stopped = true;
			}

         Trace0(TRACE_LEVEL_INFO, "done.");
         
         return 0;
		}
	}
}

#ifdef ULTRASCHALL_PLATFORM_WIN32
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

