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

#include <ServiceManager.h>

#include "Application.h"
#include "EntryPoints.h"

namespace ultraschall { namespace reaper {

Application::Application() :
   instance_(0), pPluginInfo_(0)
{
}

Application::~Application()
{
   pPluginInfo_ = 0;
   instance_ = 0;
}

Application& Application::Instance()
{
   static Application self;
   return self;
}

const bool Application::Start(REAPER_PLUGIN_HINSTANCE instance, reaper_plugin_info_t* pPluginInfo)
{
   PRECONDITION_RETURN(instance != 0, false);
   PRECONDITION_RETURN(pPluginInfo != 0, false);
   PRECONDITION_RETURN(pPluginInfo->caller_version == REAPER_PLUGIN_VERSION, false);
   PRECONDITION_RETURN(pPluginInfo->GetFunc != 0, false);

   bool started = false;

   instance_ = instance;
   pPluginInfo_ = pPluginInfo;
   started = (pPluginInfo_->Register("hookcommand", (void*)Application::OnCustomAction) != 0);
   if(started == false)
   {
      instance_ = 0;
      pPluginInfo_ = 0;
   }

   return started;
}

void Application::Stop()
{
   pPluginInfo_ = 0;
   instance_ = 0;
}

const bool Application::OnCustomAction(const int32_t id, const int16_t)
{
   PRECONDITION_RETURN(id != 0, false);

   bool executed = false;

   CustomActionManager& manager = CustomActionManager::Instance();
   ICustomAction* pCustomAction = 0;
   ServiceStatus status = manager.LookupCustomAction(id, pCustomAction);
   if(ServiceSucceeded(status) && (pCustomAction != 0))
   {
      status = pCustomAction->Execute();
      if(ServiceSucceeded(status))
      {
         executed = true;
      }

      framework::SafeRelease(pCustomAction);
   }

   return executed;
}

HWND Application::GetMainHwnd() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, 0);

   HWND hwnd = 0;

   if(0 == EntryPoints::pfnGetMainHwnd_)
   {
      *((void **)&EntryPoints::pfnGetMainHwnd_) = pPluginInfo_->GetFunc("GetMainHwnd");
   }

   if(EntryPoints::pfnGetMainHwnd_ != 0)
   {
      hwnd = (*EntryPoints::pfnGetMainHwnd_)();
   }

   return hwnd;
}

const intptr_t Application::GetCurrentProject() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, 0);
   
   intptr_t currentProject = 0;
   
   if(0 == EntryPoints::EnumProjects_)
   {
      *((void **)&EntryPoints::EnumProjects_) = pPluginInfo_->GetFunc("EnumProjects");
   }
   
   if(EntryPoints::EnumProjects_ != 0)
   {
      currentProject = reinterpret_cast<intptr_t>((*EntryPoints::EnumProjects_)(-1, 0, 0));
   }
   
   return currentProject;
      
}
   
const std::string Application::ExportPath() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::string());

   std::string projectPath;

   if (0 == EntryPoints::pfnGetProjectPath_)
   {
      *((void **)&EntryPoints::pfnGetProjectPath_) = pPluginInfo_->GetFunc("GetProjectPath");
   }

   if (0 != EntryPoints::pfnGetProjectPath_)
   {
      char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
      (*EntryPoints::pfnGetProjectPath_)(buffer, MAX_REAPER_STRING_BUFFER_SIZE);
      if (strlen(buffer) > 0)
      {
         projectPath = buffer;
      }
   }

   return projectPath;
}

const std::string Application::ProjectPath() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::string());

   std::string result;

   if(0 == EntryPoints::pfnEnumProjects_)
   {
      *((void **)&EntryPoints::pfnEnumProjects_) = pPluginInfo_->GetFunc("EnumProjects");
   }

   if(0 != EntryPoints::pfnEnumProjects_)
   {
      char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = { 0 };
      (*EntryPoints::pfnEnumProjects_)(-1, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
      if(strlen(buffer) > 0)
      {
         result = buffer;
      }
   }

   return result;
}

const std::string Application::ProjectFile() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::string());
   
   std::string result;
   
   const std::string projectPath = ProjectPath();
   if(projectPath.empty() == false)
   {
#ifdef WIN32
      const char PATH_DELIMITER_CHAR = '\\';
#else
      const char PATH_DELIMITER_CHAR = '/';
#endif
      const std::vector<std::string> pathComponents = Application::SplitString(projectPath, PATH_DELIMITER_CHAR);
      if(pathComponents.empty() == false)
      {
         result = pathComponents[pathComponents.size() - 1];
      }
   }
   
   return result;
}

const std::string Application::ProjectFolder() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::string());
   
   std::string result;
   
   const std::string projectPath = ProjectPath();
   if(projectPath.empty() == false)
   {
#ifdef WIN32
      const char PATH_DELIMITER_CHAR = '\\';
#else
      const char PATH_DELIMITER_CHAR = '/';
#endif
      const std::vector<std::string> pathComponents = Application::SplitString(projectPath, PATH_DELIMITER_CHAR);
      if(pathComponents.empty() == false)
      {
         for(size_t i = 0; i < pathComponents.size() - 1; i++)
         {
            result += pathComponents[i] + PATH_DELIMITER_CHAR;
         }
      }
   }
   
   return result;
}
   
const std::vector<std::string> Application::SplitString(const std::string& input, const char delimiter)
{
   std::vector<std::string> tokens;
   std::stringstream stream(input);
   std::string token;

   while (std::getline(stream, token, delimiter))
   {
      tokens.push_back(token);
   }

   return tokens;
}

struct Timestamp 
{
   int hours;
   int minutes;
   int seconds;
   int milliSeconds;

   Timestamp() :
      hours(0), minutes(0), seconds(0), milliSeconds(0)
   {
   }

   static Timestamp FromString(const std::string& str)
   {
      std::vector<std::string> items = Application::SplitString(str, ':');
      std::reverse(items.begin(), items.end());

      Timestamp timestamp;

      std::vector<std::string> buffer = Application::SplitString(items[0], '.');
      for(size_t i = 0; i < buffer.size(); ++i)
      {
         switch(i) {
         case 0:
            timestamp.seconds = std::atoi(buffer[0].c_str());
            break;

         case 1:
            timestamp.milliSeconds = std::atoi(buffer[1].c_str());
            break;

         default:
            break;
         }
      }

      for(size_t i = 0; i < items.size(); ++i) 
      {
         switch(i) {
         case 1:
            timestamp.minutes = std::atoi(items[1].c_str());
            break;

         case 2:
            timestamp.hours = std::atoi(items[2].c_str());
            break;

         default:
            break;
         }
      }

      return timestamp;
   }

   std::string ToString() const
   {
      std::stringstream buffer;
      buffer << std::setfill('0');
      buffer << std::setw(2) << hours << ":";
      buffer << std::setw(2) << minutes << ":";
      buffer << std::setw(2) << seconds << ".";
      buffer << std::setw(3) << milliSeconds;

      return buffer.str();
   }
};

const std::string Application::TimestampToString(const double timestamp) const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::string());

   std::string result;

   if (0 == EntryPoints::pfn_format_timestr_pos_)
   {
      *((void **)&EntryPoints::pfn_format_timestr_pos_) = pPluginInfo_->GetFunc("format_timestr_pos");
   }

   if (0 != EntryPoints::pfn_format_timestr_pos_)
   {
      char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = { 0 };
      (*EntryPoints::pfn_format_timestr_pos_)(timestamp, buffer, MAX_REAPER_STRING_BUFFER_SIZE, 0);
      if (strlen(buffer) > 0)
      {
         result = Timestamp::FromString(buffer).ToString();
      }
   }

   return result;
}

const double Application::StringToTimestamp(const std::string& input) const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, -1);
   PRECONDITION_RETURN(input.empty() == false, -1);

   double result = -1;

   if(0 == EntryPoints::pfn_parse_timestr_)
   {
      *((void **)&EntryPoints::pfn_parse_timestr_) = pPluginInfo_->GetFunc("parse_timestr");
   }

   if(0 != EntryPoints::pfn_parse_timestr_)
   {
      result = (*EntryPoints::pfn_parse_timestr_)(input.c_str());
   }

   return result;
}

const std::vector<ProjectMarker> Application::ProjectMarkers() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::vector<ProjectMarker>());

   std::vector<ProjectMarker> projectMarkers;

   if(0 == EntryPoints::pfnEnumProjectMarkers_)
   {
      *((void **)&EntryPoints::pfnEnumProjectMarkers_) = pPluginInfo_->GetFunc("EnumProjectMarkers");
   }

   if(0 != EntryPoints::pfnEnumProjectMarkers_)
   {
      int nextOffset = 0;
      bool isRegion = false;
      double position = 0;
      double endOfRegion = false;
      char* buffer = 0;
      int index = 0;

      do
      {
         nextOffset = (*EntryPoints::pfnEnumProjectMarkers_)(nextOffset, &isRegion, &position, &endOfRegion, &buffer, &index);
         if(nextOffset > 0)
         {
            const ProjectMarker projectMarker(position, buffer, index);
            projectMarkers.push_back(projectMarker);
         }
      }
      while(nextOffset > 0);
   }

   return projectMarkers;
}

const int32_t Application::SetProjectMarker(const ProjectMarker& projectMarker) const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, false);

   int32_t index = -1;

   if(0 == EntryPoints::pfnAddProjectMarker2_)
   {
      *((void **)&EntryPoints::pfnAddProjectMarker2_) = pPluginInfo_->GetFunc("AddProjectMarker2");
   }

   if(0 != EntryPoints::pfnAddProjectMarker2_)
   {
      index = (*EntryPoints::pfnAddProjectMarker2_)(0, false, projectMarker.Position(), 10, projectMarker.Name().c_str(), 0, 0xffff00);
   }

   return index;
}

const bool Application::DeleteProjectMarker(const ProjectMarker& projectMarker) const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, false);
   
   bool result = false;
   
   if(0 == EntryPoints::DeleteProjectMarker)
   {
      *((void **)&EntryPoints::DeleteProjectMarker) = pPluginInfo_->GetFunc("DeleteProjectMarker");
   }
   
   if(0 != EntryPoints::DeleteProjectMarker)
   {
      result = (*EntryPoints::DeleteProjectMarker)(0, projectMarker.Index(), projectMarker.IsRegion());
   }
   
   return result;
}
   
void Application::DeleteAllProjectMarkers() const
{
   std::vector<ProjectMarker> projectMarkers = ProjectMarkers();
   const size_t noProjectMarkers = projectMarkers.size();
   for(size_t i = 0; i < noProjectMarkers; i++)
   {
      DeleteProjectMarker(projectMarkers[(noProjectMarkers - 1) - i]);
   }
}

const std::vector<Track> Application::Tracks() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::vector<Track>());

   std::vector<Track> tracks;

   if(0 == EntryPoints::pfnGetNumTracks_)
   {
      *((void **)&EntryPoints::pfnGetNumTracks_) = pPluginInfo_->GetFunc("GetNumTracks");
   }

   if(0 == EntryPoints::pfnGetTrack_)
   {
      *((void **)&EntryPoints::pfnGetTrack_) = pPluginInfo_->GetFunc("GetTrack");
   }

   if(0 == EntryPoints::pfnGetSetMediaTrackInfo_)
   {
      *((void **)&EntryPoints::pfnGetSetMediaTrackInfo_) = pPluginInfo_->GetFunc("GetSetMediaTrackInfo");
   }

   if((0 != EntryPoints::pfnGetNumTracks_) && (0 != EntryPoints::pfnGetTrack_) &&
      (0 != EntryPoints::pfnGetSetMediaTrackInfo_))
   {
      const int noTracks = (*EntryPoints::pfnGetNumTracks_)();
      for(int i = 0; i < noTracks; i++)
      {
         void* trackHandle = (*EntryPoints::pfnGetTrack_)(0, i);
         if(trackHandle != 0)
         {
            const char* trackName = reinterpret_cast<const char*>((*EntryPoints::pfnGetSetMediaTrackInfo_)(trackHandle, "P_NAME", 0));
            if(trackName != 0)
            {
               tracks.push_back(Track(trackHandle, trackName));
            }
         }
      }
   }

   return tracks;
}

}}

