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

#include <string>
#include <iomanip>

#include <ServiceManager.h>
#include <ResourceManager.h>
#include <StringUtilities.h>
#include <TextFileReader.h>

#include "Application.h"
#include "ReaperEntryPoints.h"
#include "ReaperVersionCheck.h"
#include "SWSVersionCheck.h"
#include "FileManager.h"
#include "MessageBox.h"

namespace ultraschall {
    namespace reaper {

        Application::Application()
        {
        }

        Application::~Application()
        {
        }

        Application& Application::Instance()
        {
            static Application self;
            return self;
        }

        const ServiceStatus Application::Start()
        {
            PRECONDITION_RETURN(HealthCheck(), SERVICE_FAILURE);

            return SERVICE_SUCCESS;
        }

        void Application::Stop()
        {
        }

        const int32_t Application::Register(const char* name, void* pInfoStruct) const
        {
            return reaper_api::plugin_register(name, pInfoStruct);
        }

        const bool Application::OnCustomAction(const int32_t id)
        {
            PRECONDITION_RETURN(id != 0, false);

            bool executed = false;

            CustomActionManager& manager = CustomActionManager::Instance();
            ICustomAction* pCustomAction = 0;
            ServiceStatus status = manager.LookupCustomAction(id, pCustomAction);
            if(ServiceSucceeded(status) && (pCustomAction != 0))
            {
                pCustomAction->Execute();
                framework::SafeRelease(pCustomAction);
                executed = true;
            }

            return executed;
        }

        const intptr_t Application::GetCurrentProject() const
        {
            return (intptr_t)reaper_api::EnumProjects(-1, 0, 0);
        }

        const std::string Application::GetExportPathName() const
        {
            std::string projectPath;

            char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
            reaper_api::GetProjectPath(buffer, MAX_REAPER_STRING_BUFFER_SIZE);
            if(strlen(buffer) > 0)
            {
                projectPath = buffer;
            }

            return projectPath;
        }

        const std::string Application::GetProjectPathName() const
        {
            std::string result;

            char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
            reaper_api::EnumProjects(-1, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
            if(strlen(buffer) > 0)
            {
                result = buffer;
            }

            return result;
        }

        const std::string Application::GetProjectFileName() const
        {
            std::string result;

            const std::string projectPath = GetProjectPathName();
            if(projectPath.empty() == false)
            {
#ifndef WIN32
                const std::vector<std::string> pathComponents = framework::split(projectPath, '/');
#else
                const std::vector<std::string> pathComponents = framework::split(projectPath, '\\');
#endif // #ifndef WIN32
                if(pathComponents.empty() == false)
                {
                    result = pathComponents[pathComponents.size() - 1];
                }
            }

            return result;
        }

        const std::string Application::GetProjectFolderName() const
        {
            std::string result;

            const std::string projectPath = GetProjectPathName();
            if(projectPath.empty() == false)
            {
#ifndef WIN32
                const std::vector<std::string> pathComponents = framework::split(projectPath, '/');
#else
                const std::vector<std::string> pathComponents = framework::split(projectPath, '\\');
#endif // #ifndef WIN32

                if(pathComponents.empty() == false)
                {
                    for(size_t i = 0; i < pathComponents.size() - 1; i++)
                    {
                        result += pathComponents[i];
                        if(i < pathComponents.size() - 2)
                        {
#ifndef WIN32
                            result += '/';
#else
                            result += '\\';
#endif // #ifndef WIN32
                        }
                    }
                }
            }

            return result;
        }

        const std::string Application::GetProjectName() const
        {
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
            std::string result;

            char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
            reaper_api::format_timestr_pos(timestamp, buffer, MAX_REAPER_STRING_BUFFER_SIZE, 0);
            if(strlen(buffer) > 0)
            {
                result = Timestamp::FromString(buffer).ToString();
            }

            return result;
        }

        const double Application::StringToTimestamp(const std::string& input) const
        {
            PRECONDITION_RETURN(input.empty() == false, -1);
            return reaper_api::parse_timestr(input.c_str());
        }

        const std::vector<framework::ChapterMarker> Application::ChapterMarkers() const
        {
            std::vector<framework::ChapterMarker> chapterMarkers;

            int nextOffset = 0;
            bool isRegion = false;
            double position = 0;
            double endOfRegion = false;
            const char* buffer = 0;
            int index = 0;

            do
            {
                nextOffset = reaper_api::EnumProjectMarkers(nextOffset, &isRegion, &position, &endOfRegion, &buffer, &index);
                if(nextOffset > 0)
                {
                    const framework::ChapterMarker chapterMarker(position, buffer, index);
                    chapterMarkers.push_back(chapterMarker);
                }
            } while(nextOffset > 0);

            return chapterMarkers;
        }

        const int32_t Application::SetChapterMarker(const framework::ChapterMarker& projectMarker) const
        {
            return reaper_api::AddProjectMarker2(0, false, projectMarker.Position(), 10, projectMarker.Name().c_str(), 0, 0xffff00);
        }

        const bool Application::DeleteChapterMarker(const framework::ChapterMarker& chapterMarker) const
        {
            return reaper_api::DeleteProjectMarker(0, chapterMarker.Index(), chapterMarker.IsRegion());
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

            const std::string message("ULTRASCHALL cannot continue!");

            const std::string information1("\
The Application Support directory of your system contains an unsupported \
file that must be removed in order to use the Ultraschall REAPER Extension. Please move '\
");
            const std::string information2("\
' to a different folder on your system and restart REAPER.\
");

            const std::string information3("\
The Ultraschall REAPER Extension requires at least REAPER 5.1\
");

            const std::string information4("\
If you want to use the Ultraschall REAPER extension, you must install REAPER 5.1\
");

            const std::string information5("\
The Ultraschall REAPER Extension requires the 64-Bit version of REAPER 5.1\
");

            const std::string information6("\
If you want to use the Ultraschall REAPER extension, you must install the 64-Bit version of REAPER 5.1\
");

            const std::string information7("\
The installation of the Ultraschall REAPER extension has been corrupted. \
Please reinstall the Ultraschall REAPER extension using the original or an updated installer.\
");

#ifndef WIN32
            const std::string swsPlugin2_8SystemPath = FileManager::SystemApplicationSupportDirectory() +
                "/REAPER/UserPlugins/reaper_sws_extension.dylib";
            if((true == ok) && (FileManager::FileExists(swsPlugin2_8SystemPath) == true))
            {
                NotificationWindow::Show(message, information1 + swsPlugin2_8SystemPath + information2, true);
                ok = false;
            }

            const std::string swsPlugin2_7SystemPath = FileManager::SystemApplicationSupportDirectory() +
                "/REAPER/UserPlugins/reaper_sws.dylib";
            if((true == ok) && (FileManager::FileExists(swsPlugin2_7SystemPath) == true))
            {
                NotificationWindow::Show(message, information1 + swsPlugin2_7SystemPath + information2, true);
                ok = false;
            }

            const std::string ultraschallPluginSystemPath = FileManager::SystemApplicationSupportDirectory() +
                "/REAPER/UserPlugins/reaper_ultraschall.dylib";
            if((true == ok) && (FileManager::FileExists(ultraschallPluginSystemPath) == true))
            {
                NotificationWindow::Show(message, information1 + ultraschallPluginSystemPath + information2, true);
                ok = false;
            }
#endif

            if((true == ok) && (ReaperPlatformCheck() == false))
            {
                NotificationWindow::Show(message, information5 + " " + information6, true);
                ok = false;
            }

            if((true == ok) && (ReaperVersionCheck() == false))
            {
                NotificationWindow::Show(message, information3 + " " + information4, true);
                ok = false;
            }

            if((true == ok) && (SWSVersionCheck() == false))
            {
                NotificationWindow::Show(message, information7, true);
                ok = false;
            }

            return ok;
        }
    }
}

