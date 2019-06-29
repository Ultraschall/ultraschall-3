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

#include "Application.h"
#include "ServiceStatus.h"
#include "UIMessageSupervisor.h"

#include "CustomActionManager.h"

#include "InsertChapterMarkersAction.h"
#include "InsertMediaPropertiesAction.h"
#include "SaveChapterMarkersAction.h"
#include "SaveChapterMarkersToProjectAction.h"
#include "SystemProperties.h"

#include "ReaperEntryPoints.h"

extern "C"
{
    REAPER_PLUGIN_DLL_EXPORT int REAPER_PLUGIN_ENTRYPOINT(
        REAPER_PLUGIN_HINSTANCE hInstance, reaper_plugin_info_t *pPluginInfo)
    {
        if (pPluginInfo != 0)
        {
            static bool started = false;
            if (false == started)
            {
                if (ultraschall::reaper::ReaperEntryPoints::Setup(hInstance, pPluginInfo) == true)
                {
                    if (ultraschall::reaper::QuerySetPluginVersion() == true)
                    {
                        ultraschall::reaper::Application &application = ultraschall::reaper::Application::Instance();
                        if (ServiceSucceeded(application.Start()))
                        {
                            application.RegisterCustomAction<ultraschall::reaper::InsertChapterMarkersAction>();
                            application.RegisterCustomAction<ultraschall::reaper::SaveChapterMarkersAction>();
                            application.RegisterCustomAction<ultraschall::reaper::SaveChapterMarkersToProjectAction>();
                            application.RegisterCustomAction<ultraschall::reaper::InsertMediaPropertiesAction>();
                            started = true;
                        }
                    }
                }
                else
                {
                    ultraschall::reaper::UIMessageSupervisor supervisor;
                    supervisor.RegisterFatalError("Ultraschall failed to load!");
                    supervisor.RegisterFatalError(
                        "You are trying to load a version of REAPER that is not compatible to Ultraschall 3.");
                }
            }

            return 1;
        }
        else
        {
            static bool stopped = false;
            if (false == stopped)
            {
                ultraschall::reaper::Application &application = ultraschall::reaper::Application::Instance();
                application.Stop();

                stopped = true;
            }

            return 0;
        }
    }
}

#ifdef _WIN32
BOOL APIENTRY DllMain(HMODULE, ULONG ul_reason_for_call, LPVOID)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
#else  // #ifdef _WIN32
#endif // #ifdef _WIN32
