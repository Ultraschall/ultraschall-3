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
#include "AddChaptersAction.h"
#include "ReplaceChaptersAction.h"
#include "SaveChaptersAction.h"
#include "SaveChaptersToProjectAction.h"
#include "InsertTranscriptAction.h"

namespace reaper = ultraschall::reaper;

extern "C"
{
REAPER_PLUGIN_DLL_EXPORT int REAPER_PLUGIN_ENTRYPOINT(REAPER_PLUGIN_HINSTANCE hInstance, reaper_plugin_info_t *pPluginInfo)
{
   reaper::Application& application = reaper::Application::Instance();

   if (pPluginInfo != 0)
   {
      reaper::ApplicationStartupInformation reaperStartupInformation;
      reaperStartupInformation.instance = hInstance;
      reaperStartupInformation.pPluginInfo = pPluginInfo;

      framework::StartupInformation startupInformation;
      startupInformation.data = &reaperStartupInformation;
      if(ServiceSucceeded(application.Configure()))
      {
         if(ServiceSucceeded(application.Start(startupInformation)))
         {
            application.RegisterCustomAction<reaper::AddChaptersAction>();
            application.RegisterCustomAction<reaper::ReplaceChaptersAction>();
            application.RegisterCustomAction<reaper::SaveChaptersAction>();
            application.RegisterCustomAction<reaper::SaveChaptersToProjectAction>();
            application.RegisterCustomAction<reaper::InsertTranscriptAction>();

            return 1;
         }
      }

      return 0;
   }
   else
   {
      application.Stop();
      
      return 0;
   }
}
}

#ifdef WIN32
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
#endif

