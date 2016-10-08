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

#include "ReaperEntryPoints.h"
#include "Application.h"
#include "InvalidEntryPointException.h"

namespace reaper_api 
{
   HWND (*GetMainHwnd)();
   int (*plugin_register)(const char* name, void* infostruct);
   
   const char* (*GetAppVersion)();

   void (*GetProjectPath)(char* buf, int buf_sz);
   ReaProject* (*EnumProjects)(int idx, char* projfn, int projfn_sz);

   void (*format_timestr_pos)(double tpos, char* buf, int buf_sz, int modeoverride);
   double (*parse_timestr)(const char* buf);

   int (*EnumProjectMarkers)(int idx, bool* isrgnOut, double* posOut, double* rgnendOut, const char** nameOut, int* markrgnindexnumberOut);
   int (*AddProjectMarker2)(ReaProject* proj, bool isrgn, double pos, double rgnend, const char* name, int wantidx, int color);
   bool (*DeleteProjectMarker)(ReaProject* proj, int markrgnindexnumber, bool isrgn);
}

namespace ultraschall { namespace reaper {

static const bool OnCustomAction(KbdSectionInfo*, int cmdId, int, int, int, HWND)
{
   return Application::OnCustomAction(cmdId);
}
   
void ImportReaperEntryPoint(reaper_plugin_info_t* ppi, void*& entryPoint, const char* entryPointName)
{
   (*((void **)&(entryPoint)) = (void *)ppi->GetFunc(entryPointName));
   if(0 == entryPoint)
   {
      throw InvalidEntryPointException(entryPointName);
   }
}
   
ReaperEntryPoints::ReaperEntryPoints(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t* ppi)
{
   instance_ = instance;

   ImportReaperEntryPoint(ppi, (void*&)reaper_api::GetMainHwnd, "GetMainHwnd");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::plugin_register, "plugin_register");

   ImportReaperEntryPoint(ppi, (void*&)reaper_api::GetAppVersion, "GetAppVersion");

   ImportReaperEntryPoint(ppi, (void*&)reaper_api::GetProjectPath, "GetProjectPath");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::EnumProjects, "EnumProjects");

   ImportReaperEntryPoint(ppi, (void*&)reaper_api::format_timestr_pos, "format_timestr_pos");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::parse_timestr, "parse_timestr");

   ImportReaperEntryPoint(ppi, (void*&)reaper_api::EnumProjectMarkers, "EnumProjectMarkers");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::AddProjectMarker2, "AddProjectMarker2");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::DeleteProjectMarker, "DeleteProjectMarker");
   
   reaper_api::plugin_register("hookcommand2", (void*)OnCustomAction);
}

REAPER_PLUGIN_HINSTANCE ReaperEntryPoints::instance_ = 0;

void ReaperEntryPoints::Setup(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t* pPluginInfo)
{
   static ReaperEntryPoints entryPoints(instance, pPluginInfo);
}

}}

