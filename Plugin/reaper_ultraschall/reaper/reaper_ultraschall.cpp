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
#include "MessageBox.h"
#include "ReaperEntryPoints.h"
#include "InvalidEntryPointException.h"
#include "InsertChaptersAction.h"
#include "ReplaceChaptersAction.h"
#include "SaveChaptersAction.h"
#include "SaveChaptersToProjectAction.h"
#include "InsertTranscriptAction.h"
#include "AboutAction.h"
#include "UpdateCheckAction.h"
#include "CustomActionManager.h"
#include "ICustomAction.h"

namespace reaper = ultraschall::reaper;

extern "C"
{
REAPER_PLUGIN_DLL_EXPORT int REAPER_PLUGIN_ENTRYPOINT(REAPER_PLUGIN_HINSTANCE hInstance, reaper_plugin_info_t *pPluginInfo)
{
   reaper::Application& application = reaper::Application::Instance();
    
   if (pPluginInfo != 0)
   {
      static bool started = false;
      if(false == started)
      {
         try
         {
            reaper::ReaperEntryPoints::Setup(pPluginInfo);

            if(ServiceSucceeded(application.Configure()))
            {
               if(ServiceSucceeded(application.Start()))
               {
                  application.RegisterCustomAction<reaper::InsertChaptersAction>();
#if 0
                  application.RegisterCustomAction<reaper::ReplaceChaptersAction>();
#endif
                  application.RegisterCustomAction<reaper::SaveChaptersAction>();
                  application.RegisterCustomAction<reaper::SaveChaptersToProjectAction>();
#if 0
                  application.RegisterCustomAction<reaper::InsertTranscriptAction>();
#endif
                   application.RegisterCustomAction<reaper::AboutAction>();
                   application.RegisterCustomAction<reaper::UpdateCheckAction>();
                 
                   // run the update action on startup
                   reaper::CustomActionManager& manager = reaper::CustomActionManager::Instance();
                   reaper::ICustomAction* pCustomAction = 0;
                   ServiceStatus status = manager.LookupCustomAction(reaper::UpdateCheckAction::UniqueId(), pCustomAction);
                   if(ServiceSucceeded(status) && (pCustomAction != 0))
                   {
                     pCustomAction->Execute();
                     framework::SafeRelease(pCustomAction);
                   }
                 
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

