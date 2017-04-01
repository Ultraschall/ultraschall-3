////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 Ultraschall (http://ultraschall.fm)
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
#include <sstream>
#include <chrono>
#include <ctime>

#ifdef ULTRASCHALL_PLATFORM_WIN32
#define CURL_STATICLIB
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32
#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>

#include <Framework.h>
#include <StringUtilities.h>

#include "UpdateCheck.h"
#include "VersionHandler.h"
#include "NotificationWindow.h"
#include "ReaperEntryPoints.h"
#include "SystemProperties.h"

namespace ultraschall
{
namespace reaper
{

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
   PRECONDITION_RETURN(ptr != 0, 0);
   PRECONDITION_RETURN(nmemb > 0, 0);
   PRECONDITION_RETURN(stream != 0, 0);

   std::string data((const char *)ptr, (size_t)size * nmemb);
   std::stringstream& os = *((std::stringstream *)stream);
   os << data << std::endl;
   return size * nmemb;
}

double QueryCurrentDateTimeAsSeconds()
{
   std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
   std::chrono::duration<double> ticks = currentTime.time_since_epoch();
   return ticks.count();
}

void UpdateCheck()
{
   bool updateCheckRequired = false;
   std::string lastUpdateCheck;

   if(GetBooleanSystemProperty(UPDATE_SECTION_NAME, "update_check") == true)
   {
      static const std::string LAST_UPDATE_CHECK_NAME = "last_update_check";
      if (HasSystemProperty(UPDATE_SECTION_NAME, LAST_UPDATE_CHECK_NAME) == true)
      {
         lastUpdateCheck = GetSystemProperty(UPDATE_SECTION_NAME, LAST_UPDATE_CHECK_NAME);
         if (lastUpdateCheck.empty() == false)
         {
            std::istringstream is(lastUpdateCheck);
            double lastUpdateCheckTimestamp = 0;
            is >> lastUpdateCheckTimestamp;
            
            static const double delta = 60 * 60 * 24;
            const double now = QueryCurrentDateTimeAsSeconds();
            if ((now - lastUpdateCheckTimestamp) >= delta)
            {
               updateCheckRequired = true;
            }
         }
      }
      else
      {
         updateCheckRequired = true;
      }

      if (updateCheckRequired == true)
      {
         void *curlHandle = curl_easy_init();
         if(curlHandle != nullptr)
         {
            const std::string url = "https://ultraschall.io/ultraschall_release.txt";
            curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curlHandle, CURLOPT_FOLLOWLOCATION, 1L);
            curl_easy_setopt(curlHandle, CURLOPT_NOSIGNAL, 1);
            curl_easy_setopt(curlHandle, CURLOPT_ACCEPT_ENCODING, "deflate");
            curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);
            
            std::stringstream out;
            curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &out);
            
            CURLcode res = curl_easy_perform(curlHandle);
            if(res == CURLE_OK)
            {
               std::string remoteVersion = out.str();
               if(remoteVersion.empty() == false)
               {
                  framework::StringTrim(remoteVersion);
                  const std::string localVersion = VersionHandler::PluginVersion();
                  if(remoteVersion > localVersion)
                  {
                     std::string message = "An update for Ultraschall is available. Go to http://ultraschall.fm/install to download the new version ";
                     message += remoteVersion + ".";
                     NotificationWindow::Show(message);
                  }
               }
            }
            
            curl_easy_cleanup(curlHandle);
            curlHandle = nullptr;
            
            std::ostringstream os;
            os << QueryCurrentDateTimeAsSeconds();
            lastUpdateCheck = os.str();
            SetSystemProperty(UPDATE_SECTION_NAME, LAST_UPDATE_CHECK_NAME, lastUpdateCheck, true);
         }
      }
   }
}

}
}
