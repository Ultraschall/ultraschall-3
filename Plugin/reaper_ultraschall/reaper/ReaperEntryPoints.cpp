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

#include "ReaperEntryPoints.h"
#include "InvalidEntryPointException.h"

#include "Application.h"
#include "ProjectManager.h"
#include "ProjectCallback.h"

namespace reaper_api 
{
   HWND (*GetMainHwnd)();
   int (*plugin_register)(const char* name, void* infostruct);
   
   const char* (*GetAppVersion)();

   void (*GetProjectPath)(char* buf, int buf_sz);
   void (*GetProjectPathEx)(ReaProject* proj, char* buf, int buf_sz);
   ReaProject* (*EnumProjects)(int idx, char* projfn, int projfn_sz);

   void (*format_timestr_pos)(double tpos, char* buf, int buf_sz, int modeoverride);
   double (*parse_timestr)(const char* buf);

   void(*PreventUIRefresh)(int prevent_count);

   int(*CountProjectMarkers)(ReaProject* proj, int* num_markersOut, int* num_regionsOut);
   int (*EnumProjectMarkers)(int idx, bool* isrgnOut, double* posOut, double* rgnendOut, const char** nameOut, int* markrgnindexnumberOut);
   int (*EnumProjectMarkers2)(ReaProject* proj, int idx, bool* isrgnOut, double* posOut, double* rgnendOut, const char** nameOut, int* markrgnindexnumberOut);
   int (*EnumProjectMarkers3)(ReaProject* proj, int idx, bool* isrgnOut, double* posOut, double* rgnendOut, const char** nameOut, int* markrgnindexnumberOut, int* colorOut);
   int (*AddProjectMarker2)(ReaProject* proj, bool isrgn, double pos, double rgnend, const char* name, int wantidx, int color);
   bool (*SetProjectMarker3)(ReaProject* proj, int markrgnindexnumber, bool isrgn, double pos, double rgnend, const char* name, int color);
   bool (*DeleteProjectMarker)(ReaProject* proj, int markrgnindexnumber, bool isrgn);
   void(*GetLastMarkerAndCurRegion)(ReaProject* proj, double time, int* markeridxOut, int* regionidxOut);
   bool(*DeleteProjectMarkerByIndex)(ReaProject* proj, int markrgnidx);

   int(*GetPlayStateEx)(ReaProject* proj);
   double(*GetCursorPositionEx)(ReaProject* proj);
   double(*GetPlayPositionEx)(ReaProject* proj);
}

namespace ultraschall { namespace reaper {

static bool OnCustomAction(KbdSectionInfo*, int commandId, int, int, int, HWND)
{
   return Application::OnCustomAction(commandId);
}

static bool OnStartCommand(int commandId, int)
{
   return Application::OnStartCommand(commandId);
}
   
static bool OnStopCommand(int commandId, int)
{
   return Application::OnStopCommand(commandId);
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
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::GetProjectPathEx, "GetProjectPathEx");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::EnumProjects, "EnumProjects");

   ImportReaperEntryPoint(ppi, (void*&)reaper_api::format_timestr_pos, "format_timestr_pos");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::parse_timestr, "parse_timestr");

   ImportReaperEntryPoint(ppi, (void*&)reaper_api::PreventUIRefresh, "PreventUIRefresh");

   ImportReaperEntryPoint(ppi, (void*&)reaper_api::CountProjectMarkers, "CountProjectMarkers");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::EnumProjectMarkers, "EnumProjectMarkers");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::EnumProjectMarkers2, "EnumProjectMarkers2");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::EnumProjectMarkers3, "EnumProjectMarkers3");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::AddProjectMarker2, "AddProjectMarker2");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::DeleteProjectMarker, "DeleteProjectMarker");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::GetLastMarkerAndCurRegion, "GetLastMarkerAndCurRegion");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::DeleteProjectMarkerByIndex, "DeleteProjectMarkerByIndex");

   ImportReaperEntryPoint(ppi, (void*&)reaper_api::GetPlayStateEx, "GetPlayStateEx");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::GetCursorPositionEx, "GetCursorPositionEx");
   ImportReaperEntryPoint(ppi, (void*&)reaper_api::GetPlayPositionEx, "GetPlayPositionEx");

   reaper_api::plugin_register("hookcommand2", (void*)OnCustomAction);
   reaper_api::plugin_register("hookcommand", (void*)OnStartCommand);
   reaper_api::plugin_register("hookpostcommand", (void*)OnStopCommand);
}

REAPER_PLUGIN_HINSTANCE ReaperEntryPoints::instance_ = 0;

void ReaperEntryPoints::Setup(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t* pPluginInfo)
{
   static ReaperEntryPoints entryPoints(instance, pPluginInfo);
   static ReaperProjectEntryPoints projectEntryPointes;
}

static bool ProcessExtensionLine(const char *line, ProjectStateContext *ctx, bool isUndo, struct project_config_extension_t*)
{
   PRECONDITION_RETURN(line != 0, false);
   PRECONDITION_RETURN(ctx != 0, false);
   PRECONDITION_RETURN(false == isUndo, false);

   bool processed = false;

   ProjectManager& projectManager = ProjectManager::Instance();
   Project currentProject = projectManager.CurrentProject();
   if(Project::Validate(currentProject) == true)
   {
      processed = ProjectCallback::ProcessExtensionLine(currentProject, line, *ctx);
   }

   return processed;
}

static void SaveExtensionConfig(ProjectStateContext *ctx, bool isUndo, struct project_config_extension_t*)
{
   PRECONDITION(ctx != 0);
   PRECONDITION(false == isUndo);

   ProjectManager& projectManager = ProjectManager::Instance();
   Project currentProject = projectManager.CurrentProject();
   if(Project::Validate(currentProject) == true)
   {
      ProjectCallback::SaveExtensionConfig(currentProject, *ctx);
   }
}

static void BeginLoadProjectState(bool isUndo, struct project_config_extension_t*)
{
   PRECONDITION(false == isUndo);

   ProjectManager& projectManager = ProjectManager::Instance();
   Project currentProject = projectManager.CurrentProject();
   if(Project::Validate(currentProject) == true)
   {
      ProjectCallback::BeginLoadProjectState(currentProject);
   }
}

project_config_extension_t ReaperProjectEntryPoints::projectConfigExtension_ = { 0 };

ReaperProjectEntryPoints::ReaperProjectEntryPoints()
{
   projectConfigExtension_.BeginLoadProjectState = BeginLoadProjectState;
   projectConfigExtension_.ProcessExtensionLine = ProcessExtensionLine;
   projectConfigExtension_.SaveExtensionConfig = SaveExtensionConfig;
   projectConfigExtension_.userData = 0;

   reaper_api::plugin_register("projectconfig", (void*)&projectConfigExtension_);
}

}}

