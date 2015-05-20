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

#ifndef __ULTRASCHALL_REAPER_APPLICATION_H_INCL__
#define __ULTRASCHALL_REAPER_APPLICATION_H_INCL__

#include <Framework.h>

#include "Reaper.h"

#include "CustomActionManager.h"
#include "CustomActionFactory.h"

#include "ProjectMarker.h"
#include "Track.h"

namespace framework = ultraschall::framework;

namespace ultraschall { namespace reaper {

class Application
{
public:
   virtual ~Application();

   static Application& Instance();

   const bool Start(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t* pPluginInfo);
   void Stop();

   template<class CustomActionType> const ServiceStatus RegisterCustomAction() const;
   static const bool OnCustomAction(const int32_t id, const int16_t flags);

   static const size_t MAX_REAPER_STRING_BUFFER_SIZE = 4096;

   HWND GetMainHwnd() const;

   const std::string ExportPath() const;
   const std::string ProjectPath() const;
   const std::string ProjectFile() const;
   const std::string ProjectFolder() const;

   static const std::vector<std::string> SplitString(const std::string& input, const char delimiter);

   const std::string TimestampToString(const double timestamp) const;
   const double StringToTimestamp(const std::string& input) const;

   const intptr_t GetCurrentProject() const;
   
   const std::vector<ProjectMarker> ProjectMarkers() const;
   const int32_t SetProjectMarker(const ProjectMarker& projectMarker) const;
   const bool DeleteProjectMarker(const ProjectMarker& projectMarker) const;
   void DeleteAllProjectMarkers() const;
   
   const std::vector<Track> Tracks() const;
private:
   Application();

   REAPER_PLUGIN_HINSTANCE instance_;
   reaper_plugin_info_t* pPluginInfo_;
};

struct custom_action_register_t
{
   int uniqueSectionId; // 0/100=main/main alt, 32063=media explorer, 32060=midi editor, 32061=midi event list editor, 32062=midi inline editor, etc
   const char* idStr; // must be unique accross all sections
   const char* name;
   void *extra; // reserved for future use

   custom_action_register_t() :
      uniqueSectionId(0), idStr(0), name(0), extra(0)
   {
   }
};

template<class CustomActionType> const ServiceStatus Application::RegisterCustomAction() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, SERVICE_FAILURE);

   ServiceStatus status = SERVICE_FAILURE;

   const std::string& name = CustomActionType::Name();
   const std::string& uniqueId = CustomActionType::UniqueId();

   CustomActionFactory& factory = CustomActionFactory::Instance();
   ICustomAction* pCustomAction = 0;
   status = factory.CreateCustomAction(name, pCustomAction);
   if(ServiceSucceeded(status) && (pCustomAction != 0))
   {
      custom_action_register_t action;
      action.idStr = uniqueId.c_str();
      action.name = name.c_str();
      const int32_t id = pPluginInfo_->Register("custom_action", (void*)&action);
      if(id != 0)
      {
         CustomActionManager& manager = CustomActionManager::Instance();
         status = manager.RegisterCustomAction(id, pCustomAction);
      }

      framework::SafeRelease(pCustomAction);
   }

   return status;
}

}}

#endif // #ifndef __ULTRASCHALL_REAPER_APPLICATION_H_INCL__
