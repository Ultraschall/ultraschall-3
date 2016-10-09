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

#ifndef __ULTRASCHALL_REAPER_ENTRY_POINTS_H_INCL__
#define __ULTRASCHALL_REAPER_ENTRY_POINTS_H_INCL__

// disable 'unreferenced formal parameter'
#pragma warning(disable: 4100)
// Include base SDK header
#include <reaper_plugin.h>
#pragma warning(default: 4100)

// This must be included after 'reaper_plugin.h'.
#define REAPERAPI_DECL
#define REAPERAPI_NO_LICE
#define REAPERAPI_MINIMAL
#define REAPERAPI_WANT_GetMainHwnd
#define REAPERAPI_WANT_plugin_register
#define REAPERAPI_WANT_GetAppVersion
#define REAPERAPI_WANT_GetProjectPath
#define REAPERAPI_WANT_EnumProjects
#define REAPERAPI_WANT_format_timestr_pos
#define REAPERAPI_WANT_parse_timestr
#define REAPERAPI_WANT_EnumProjectMarkers
#define REAPERAPI_WANT_EnumProjectMarkers2
#define REAPERAPI_WANT_EnumProjectMarkers3
#define REAPERAPI_WANT_AddProjectMarker2
#define REAPERAPI_WANT_SetProjectMarker3
#define REAPERAPI_WANT_DeleteProjectMarker

namespace reaper_api {
#include <reaper_plugin_functions.h>
}

namespace ultraschall { namespace reaper {

class ReaperEntryPoints
{
public:
   static REAPER_PLUGIN_HINSTANCE instance_;
   
   static void Setup(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t* pPluginInfo);
private:
   ReaperEntryPoints(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t* pPluginInfo);
};

}}

#endif // #ifndef __ULTRASCHALL_REAPER_ENTRY_POINTS_H_INCL__
