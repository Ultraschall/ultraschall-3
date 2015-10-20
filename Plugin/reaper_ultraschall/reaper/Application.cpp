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
#include <ResourceManager.h>
#include <StringUtilities.h>
#include <TextFileReader.h>

#include "Application.h"
#include "EntryPoints.h"
#include "FileManager.h"
#include "MessageBox.h"

namespace ultraschall { namespace reaper {

Application::Application() :
   instance_(0), pPluginInfo_(0), pPluginRegister_(0)
{
}

Application::~Application()
{
   pPluginRegister_ = 0;
   pPluginInfo_ = 0;
   instance_ = 0;
}

Application& Application::Instance()
{
   static Application self;
   return self;
}

const ServiceStatus Application::Start(const framework::StartupInformation& startupInformation)
{
   PRECONDITION_RETURN(HealthCheck(), SERVICE_FAILURE);
   PRECONDITION_RETURN(startupInformation.data != 0, SERVICE_FAILURE);
   
   ApplicationStartupInformation* pData = reinterpret_cast<ApplicationStartupInformation*>(startupInformation.data);
   PRECONDITION_RETURN(pData != 0, SERVICE_FAILURE);
   
   REAPER_PLUGIN_HINSTANCE instance = pData->instance;
   PRECONDITION_RETURN(instance != 0, SERVICE_FAILURE);
   
   reaper_plugin_info_t* pPluginInfo = pData->pPluginInfo;
   PRECONDITION_RETURN(pPluginInfo != 0, SERVICE_FAILURE);
   PRECONDITION_RETURN(pPluginInfo->caller_version == REAPER_PLUGIN_VERSION, SERVICE_FAILURE);
   PRECONDITION_RETURN(pPluginInfo->GetFunc != 0, SERVICE_FAILURE);

   instance_ = instance;
   pPluginInfo_ = pPluginInfo;
   bool started = (Register("hookcommand2", (void*)Application::OnCustomAction2) != 0);
   if(started == true)
   {
      return SERVICE_SUCCESS;
   }
   else
   {
      instance_ = 0;
      pPluginInfo_ = 0;

      return SERVICE_FAILURE;
   }
}

void Application::Stop()
{
   pPluginInfo_ = 0;
   instance_ = 0;
}

const int32_t Application::Register(const char* name, void* pInfoStruct) const
{
   if(0 == pPluginRegister_)
   {
      *((void**)(&pPluginRegister_)) = pPluginInfo_->GetFunc("plugin_register");
   }
   
   int commandId = 0;
   
   if(0 != pPluginRegister_)
   {
      commandId = (*pPluginRegister_)(name, pInfoStruct);
   }

   return commandId;
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

const bool Application::OnCustomAction2(KbdSectionInfo* sec, int cmdId, int val, int valhw, int relmode, HWND hwnd)
{
   PRECONDITION_RETURN(cmdId != 0, false);

   bool executed = false;
   
   CustomActionManager& manager = CustomActionManager::Instance();
   ICustomAction* pCustomAction = 0;
   ServiceStatus status = manager.LookupCustomAction(cmdId, pCustomAction);
   if(ServiceSucceeded(status) && (pCustomAction != 0))
   {
      status = pCustomAction->Execute();
      if(ServiceSucceeded(status))
      {
      }
      
      framework::SafeRelease(pCustomAction);

      executed = true;
   }
   
   return executed;
}
   
HWND Application::GetMainHwnd() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, 0);

   HWND hwnd = 0;

   if(0 == EntryPoints::pGetMainHwnd_)
   {
      *((void **)&EntryPoints::pGetMainHwnd_) = pPluginInfo_->GetFunc("GetMainHwnd");
   }

   if(EntryPoints::pGetMainHwnd_ != 0)
   {
      hwnd = (*EntryPoints::pGetMainHwnd_)();
   }

   return hwnd;
}

const intptr_t Application::GetCurrentProject() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, 0);
   
   intptr_t currentProject = 0;
   
   if(0 == EntryPoints::pEnumProjects_)
   {
      *((void **)&EntryPoints::pEnumProjects_) = pPluginInfo_->GetFunc("EnumProjects");
   }
   
   if(EntryPoints::pEnumProjects_ != 0)
   {
      currentProject = reinterpret_cast<intptr_t>((*EntryPoints::pEnumProjects_)(-1, 0, 0));
   }
   
   return currentProject;
      
}
   
const std::string Application::GetExportPathName() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::string());

   std::string projectPath;

   if (0 == EntryPoints::pGetProjectPath_)
   {
      *((void **)&EntryPoints::pGetProjectPath_) = pPluginInfo_->GetFunc("GetProjectPath");
   }

   if (0 != EntryPoints::pGetProjectPath_)
   {
      char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
      (*EntryPoints::pGetProjectPath_)(buffer, MAX_REAPER_STRING_BUFFER_SIZE);
      if (strlen(buffer) > 0)
      {
         projectPath = buffer;
      }
   }

   return projectPath;
}

const std::string Application::GetProjectPathName() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::string());

   std::string result;

   if(0 == EntryPoints::pEnumProjects2_)
   {
      *((void **)&EntryPoints::pEnumProjects2_) = pPluginInfo_->GetFunc("EnumProjects");
   }

   if(0 != EntryPoints::pEnumProjects2_)
   {
      char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = { 0 };
      (*EntryPoints::pEnumProjects2_)(-1, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
      if(strlen(buffer) > 0)
      {
         result = buffer;
      }
   }

   return result;
}

const std::string Application::GetProjectFileName() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::string());
   
   std::string result;
   
   const std::string projectPath = GetProjectPathName();
   if(projectPath.empty() == false)
   {
#ifdef WIN32
      const char PATH_DELIMITER_CHAR = '\\';
#else
      const char PATH_DELIMITER_CHAR = '/';
#endif
      const std::vector<std::string> pathComponents = framework::split(projectPath, PATH_DELIMITER_CHAR);
      if(pathComponents.empty() == false)
      {
         result = pathComponents[pathComponents.size() - 1];
      }
   }
   
   return result;
}

const std::string Application::GetProjectFolderName() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::string());
   
   std::string result;
   
   const std::string projectPath = GetProjectPathName();
   if(projectPath.empty() == false)
   {
#ifdef WIN32
      const char PATH_DELIMITER_CHAR = '\\';
#else
      const char PATH_DELIMITER_CHAR = '/';
#endif
      const std::vector<std::string> pathComponents = framework::split(projectPath, PATH_DELIMITER_CHAR);
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
   
const std::string Application::GetProjectName() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::string());
   
   std::string result;
   
   const std::string projectFile = GetProjectFileName();
   if(projectFile.empty() == false)
   {
      result = projectFile.substr(0, projectFile.find('.', 0));
   }
   
   return result;
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
      std::vector<std::string> items = framework::split(str, ':');
      std::reverse(items.begin(), items.end());

      Timestamp timestamp;

      std::vector<std::string> buffer = framework::split(items[0], '.');
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

   if (0 == EntryPoints::p_format_timestr_pos_)
   {
      *((void **)&EntryPoints::p_format_timestr_pos_) = pPluginInfo_->GetFunc("format_timestr_pos");
   }

   if (0 != EntryPoints::p_format_timestr_pos_)
   {
      char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = { 0 };
      (*EntryPoints::p_format_timestr_pos_)(timestamp, buffer, MAX_REAPER_STRING_BUFFER_SIZE, 0);
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

   if(0 == EntryPoints::p_parse_timestr_)
   {
      *((void **)&EntryPoints::p_parse_timestr_) = pPluginInfo_->GetFunc("parse_timestr");
   }

   if(0 != EntryPoints::p_parse_timestr_)
   {
      result = (*EntryPoints::p_parse_timestr_)(input.c_str());
   }

   return result;
}

const std::vector<framework::ChapterMarker> Application::ChapterMarkers() const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, std::vector<framework::ChapterMarker>());

   std::vector<framework::ChapterMarker> chapterMarkers;

   if(0 == EntryPoints::pEnumProjectMarkers_)
   {
      *((void **)&EntryPoints::pEnumProjectMarkers_) = pPluginInfo_->GetFunc("EnumProjectMarkers");
   }

   if(0 != EntryPoints::pEnumProjectMarkers_)
   {
      int nextOffset = 0;
      bool isRegion = false;
      double position = 0;
      double endOfRegion = false;
      char* buffer = 0;
      int index = 0;

      do
      {
         nextOffset = (*EntryPoints::pEnumProjectMarkers_)(nextOffset, &isRegion, &position, &endOfRegion, &buffer, &index);
         if(nextOffset > 0)
         {
            const framework::ChapterMarker chapterMarker(position, buffer, index);
            chapterMarkers.push_back(chapterMarker);
         }
      }
      while(nextOffset > 0);
   }

   return chapterMarkers;
}

const int32_t Application::SetChapterMarker(const framework::ChapterMarker& projectMarker) const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, -1);

   int32_t index = -1;

   if(0 == EntryPoints::pAddProjectMarker2_)
   {
      *((void **)&EntryPoints::pAddProjectMarker2_) = pPluginInfo_->GetFunc("AddProjectMarker2");
   }

   if(0 != EntryPoints::pAddProjectMarker2_)
   {
      index = (*EntryPoints::pAddProjectMarker2_)(0, false, projectMarker.Position(), 10, projectMarker.Name().c_str(), 0, 0xffff00);
   }

   return index;
}

const bool Application::DeleteChapterMarker(const framework::ChapterMarker& chapterMarker) const
{
   PRECONDITION_RETURN(pPluginInfo_ != 0, false);
   
   bool result = false;
   
   if(0 == EntryPoints::pDeleteProjectMarker)
   {
      *((void **)&EntryPoints::pDeleteProjectMarker) = pPluginInfo_->GetFunc("DeleteProjectMarker");
   }
   
   if(0 != EntryPoints::pDeleteProjectMarker)
   {
      result = (*EntryPoints::pDeleteProjectMarker)(0, chapterMarker.Index(), chapterMarker.IsRegion());
   }
   
   return result;
}
   
void Application::DeleteAllChapterMarkers() const
{
   std::vector<framework::ChapterMarker> chapterMarkers = ChapterMarkers();
   const size_t numberOfChapterMarkers = chapterMarkers.size();
   for(size_t i = 0; i < numberOfChapterMarkers; i++)
   {
      DeleteChapterMarker(chapterMarkers[(numberOfChapterMarkers - 1) - i]);
   }
}

const ServiceStatus Application::Configure()
{
   framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
   resourceManager.SetLanguage("en-EN");
   return SERVICE_SUCCESS;
}

const bool Application::InsertTransriptItem(const framework::TranscriptItem transcriptItem) const
{
   return true;
}

const bool Application::HealthCheck()
{
   bool ok = true;

   const std::string message("Ultraschall cannot continue!");
   
   const std::string information1("\
The Application Support directory of your system contains an unsupported \
file that must be removed in order to use the Ultraschall REAPER Extension. Please move '\
");
   const std::string information2("\
' to a different folder on your system and restart REAPER.\
");

   const std::string information3("\
The Ultraschall REAPER Extension requires REAPER 5.x.\
");

   const std::string information4("\
If you want to use the Ultraschall REAPER extension, you must install REAPER 5.x.\
");
   
   const std::string information5("\
\
");
   
   
   const std::string swsPlugin2_8SystemPath = FileManager::SystemApplicationSupportDirectory() +
                                              "/REAPER/UserPlugins/reaper_sws_extension.dylib";
   if(FileManager::FileExists(swsPlugin2_8SystemPath) == true)
   {
      MessageBox::Show(message, information1 + swsPlugin2_8SystemPath + information2, true);
      ok = false;
   }
   
   const std::string swsPlugin2_7SystemPath = FileManager::SystemApplicationSupportDirectory() +
                                              "/REAPER/UserPlugins/reaper_sws.dylib";
   if(FileManager::FileExists(swsPlugin2_7SystemPath) == true)
   {
      MessageBox::Show(message, information1 + swsPlugin2_7SystemPath + information2, true);
      ok = false;
   }

   const std::string ultraschallPluginSystemPath = FileManager::SystemApplicationSupportDirectory() +
                                                   "/REAPER/UserPlugins/reaper_ultraschall.dylib";
   if(FileManager::FileExists(ultraschallPluginSystemPath) == true)
   {
      MessageBox::Show(message, information1 + ultraschallPluginSystemPath + information2, true);
      ok = false;
   }
   
   const std::string reaperVersionFile = FileManager::UserApplicationSupportDirectory() +
                                         "/REAPER/reaper-install-rev.txt";
   if(FileManager::FileExists(reaperVersionFile) == true)
   {
      std::vector<std::string> lines = framework::TextFileReader::ReadLines(reaperVersionFile);
      if(lines.empty() == false)
      {
         if(lines[0][0] != '5')
         {
            MessageBox::Show(message, information3 + " " + information4 , true);
            ok = false;
         }
      }
   }
   else
   {
      MessageBox::Show(message, information3 + " " + information4 , true);
      ok = false;
   }
   
   return ok;
}
    
}}

