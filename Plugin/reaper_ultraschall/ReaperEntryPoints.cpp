////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy// The MIT License (MIT)
//

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
#include "ReaperProjectManager.h"

namespace reaper_api {
HWND (*GetMainHwnd)();

int (*plugin_register)(const char* name, void* infostruct);

const char* (*GetAppVersion)();
const char* (*GetExePath)();

void (*GetProjectPath)(char* buf, int buf_sz);
void (*GetProjectPathEx)(ReaProject* proj, char* buf, int buf_sz);
ReaProject* (*EnumProjects)(int idx, char* projfn, int projfn_sz);

void (*format_timestr_pos)(double tpos, char* buf, int buf_sz, int modeoverride);
double (*parse_timestr)(const char* buf);

void (*PreventUIRefresh)(int prevent_count);

int (*CountProjectMarkers)(ReaProject* proj, int* num_markersOut, int* num_regionsOut);
int (*EnumProjectMarkers)(int idx, bool* isrgnOut, double* posOut, double* rgnendOut, const char** nameOut, int* markrgnindexnumberOut);
int (*EnumProjectMarkers2)(ReaProject* proj, int idx, bool* isrgnOut, double* posOut, double* rgnendOut, const char** nameOut, int* markrgnindexnumberOut);
int (*EnumProjectMarkers3)(
    ReaProject* proj, int idx, bool* isrgnOut, double* posOut, double* rgnendOut, const char** nameOut, int* markrgnindexnumberOut, int* colorOut);
int (*AddProjectMarker2)(ReaProject* proj, bool isrgn, double pos, double rgnend, const char* name, int wantidx, int color);
bool (*SetProjectMarker3)(ReaProject* proj, int markrgnindexnumber, bool isrgn, double pos, double rgnend, const char* name, int color);
bool (*DeleteProjectMarker)(ReaProject* proj, int markrgnindexnumber, bool isrgn);
void (*GetLastMarkerAndCurRegion)(ReaProject* proj, double time, int* markeridxOut, int* regionidxOut);
bool (*DeleteProjectMarkerByIndex)(ReaProject* proj, int markrgnidx);

int (*GetPlayStateEx)(ReaProject* proj);
double (*GetCursorPositionEx)(ReaProject* proj);
double (*GetPlayPositionEx)(ReaProject* proj);

void (*GetSetProjectNotes)(ReaProject* proj, bool set, char* notesNeedBig, int notesNeedBig_sz);
int (*SetProjExtState)(ReaProject* proj, const char* extname, const char* key, const char* value);
int (*GetProjExtState)(ReaProject* proj, const char* extname, const char* key, char* valOutNeedBig, int valOutNeedBig_sz);

bool (*HasExtState)(const char* section, const char* key);
void (*SetExtState)(const char* section, const char* key, const char* value, bool persist);
const char* (*GetExtState)(const char* section, const char* key);
void (*DeleteExtState)(const char* section, const char* key, bool persist);

MediaItem* (*GetMediaItem)(ReaProject* proj, int itemidx);
double (*GetMediaItemInfo_Value)(MediaItem* item, const char* parmname);
} // namespace reaper_api

namespace ultraschall { namespace reaper {

static bool OnCustomAction(KbdSectionInfo*, int commandId, int, int, int, HWND)
{
    return Application::OnCustomAction(commandId);
}

bool ImportReaperEntryPoint(reaper_plugin_info_t* ppi, void*& entryPoint, const std::string& entryPointName)
{
    PRECONDITION_RETURN(ppi != 0, false);
    PRECONDITION_RETURN(entryPointName.empty() == false, false);

    (*((void**)&(entryPoint)) = (void*)ppi->GetFunc(entryPointName.c_str()));
    if (entryPoint != 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

#define LOAD_AND_VERIFY_REAPER_ENTRY_POINT(__rp__, __ep__, __ep_name__)                         \
    {                                                                                           \
        const bool __ep_loaded__ = ImportReaperEntryPoint(__rp__, (void*&)__ep__, __ep_name__); \
        if ((__ep_loaded__ == false) || (0 == __ep__))                                          \
        {                                                                                       \
            return false;                                                                       \
        }                                                                                       \
    }

bool ReaperEntryPoints::LoadEntryPoints(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t* ppi)
{
    PRECONDITION_RETURN(instance != 0, false);
    PRECONDITION_RETURN(ppi != 0, false);

    instance_ = instance;

    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetMainHwnd, "GetMainHwnd");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::plugin_register, "plugin_register");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetAppVersion, "GetAppVersion");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetExePath, "GetExePath");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetProjectPath, "GetProjectPath");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetProjectPathEx, "GetProjectPathEx");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::EnumProjects, "EnumProjects");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::format_timestr_pos, "format_timestr_pos");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::parse_timestr, "parse_timestr");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::PreventUIRefresh, "PreventUIRefresh");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::CountProjectMarkers, "CountProjectMarkers");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::EnumProjectMarkers, "EnumProjectMarkers");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::EnumProjectMarkers2, "EnumProjectMarkers2");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::EnumProjectMarkers3, "EnumProjectMarkers3");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::AddProjectMarker2, "AddProjectMarker2");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::DeleteProjectMarker, "DeleteProjectMarker");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetLastMarkerAndCurRegion, "GetLastMarkerAndCurRegion");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::DeleteProjectMarkerByIndex, "DeleteProjectMarkerByIndex");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetPlayStateEx, "GetPlayStateEx");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetCursorPositionEx, "GetCursorPositionEx");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetPlayPositionEx, "GetPlayPositionEx");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetSetProjectNotes, "GetSetProjectNotes");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::SetProjExtState, "SetProjExtState");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetProjExtState, "GetProjExtState");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::HasExtState, "HasExtState");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::SetExtState, "SetExtState");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetExtState, "GetExtState");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::DeleteExtState, "DeleteExtState");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetMediaItem, "GetMediaItem");
    LOAD_AND_VERIFY_REAPER_ENTRY_POINT(ppi, reaper_api::GetMediaItemInfo_Value, "GetMediaItemInfo_Value");

    reaper_api::plugin_register("hookcommand2", (void*)OnCustomAction);

    return true;
}

REAPER_PLUGIN_HINSTANCE ReaperEntryPoints::instance_ = 0;

bool ReaperEntryPoints::Setup(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t* pPluginInfo)
{
    return ReaperEntryPoints::LoadEntryPoints(instance, pPluginInfo);
}

}} // namespace ultraschall::reaper
