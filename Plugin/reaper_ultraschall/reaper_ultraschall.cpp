////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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
#include "ReaperEntryPoints.h"
#include "ServiceStatus.h"
#include "UIMessageDialog.h"

#include "CustomActionManager.h"

#include "InsertChapterMarkersAction.h"
#include "InsertMediaPropertiesAction.h"
#include "SaveChapterMarkersAction.h"
#include "SaveChapterMarkersToProjectAction.h"
#include "SystemProperties.h"

namespace reaper = ultraschall::reaper;

extern "C" {
REAPER_PLUGIN_DLL_EXPORT int REAPER_PLUGIN_ENTRYPOINT(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t* pPluginInfo)
{
    reaper::Application& application = reaper::Application::Instance();

    if (pPluginInfo != 0)
    {
        static bool started = false;
        if (false == started)
        {
            if (reaper::ReaperEntryPoints::Setup(instance, pPluginInfo) == true)
            {
                if (reaper::QuerySetPluginVersion() == true)
                {
                    if (ServiceSucceeded(application.Start()))
                    {
                        application.RegisterCustomAction<reaper::InsertChapterMarkersAction>();
                        application.RegisterCustomAction<reaper::SaveChapterMarkersAction>();
                        application.RegisterCustomAction<reaper::SaveChapterMarkersToProjectAction>();
                        application.RegisterCustomAction<reaper::InsertMediaPropertiesAction>();

                        started = true;
                    }
                }
            }
            else
            {
#ifndef ULTRASCHALL_BROADCASTER
                std::string errorReason = "You are trying to load a version of REAPER that is not compatible to Ultraschall 3.";
                reaper::UIMessageDialog::ShowError("Ultraschall failed to load!", errorReason);
#endif // #ifndef ULTRASCHALL_BROADCASTER
            }
        }

        return 1;
    }
    else
    {
        static bool stopped = false;
        if (false == stopped)
        {
            application.Stop();
            stopped = true;
        }

        return 0;
    }
}
}

#ifdef ULTRASCHALL_PLATFORM_WIN32
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
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32
