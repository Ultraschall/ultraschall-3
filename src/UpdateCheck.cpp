////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
//
// The MIT License (MIT)
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

#ifdef _WIN32
#define CURL_STATICLIB
#else  // #ifdef _WIN32
#endif // #ifdef _WIN32
#include <curl/curl.h>
#include <curl/easy.h>

#include "Common.h"
#include "Platform.h"
#include "StringUtilities.h"
#include "SystemProperties.h"
#include "UIMessageSupervisor.h"
#include "UpdateCheck.h"
#include "VersionHandler.h"

namespace ultraschall { namespace reaper {

size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream)
{
    PRECONDITION_RETURN(ptr != 0, 0);
    PRECONDITION_RETURN(nmemb > 0, 0);
    PRECONDITION_RETURN(stream != 0, 0);

    std::string        data((const char*)ptr, (size_t)size * nmemb);
    std::stringstream& os = *((std::stringstream*)stream);
    os << data << std::endl;
    return size * nmemb;
}

double QueryCurrentTimeAsSeconds()
{
    const std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
    const std::chrono::duration<double>                      seconds
        = std::chrono::duration_cast<std::chrono::seconds>(currentTime.time_since_epoch());
    return seconds.count();
}

void UpdateCheck()
{
    if(SystemProperty<bool>::Get(UPDATE_SECTION_NAME, "update_check") == true)
    {
        bool updateCheckRequired = false;

        static const std::string LAST_UPDATE_CHECK_NAME = "last_update_check";
        if(SystemProperty<std::string>::Exists(UPDATE_SECTION_NAME, LAST_UPDATE_CHECK_NAME) == true)
        {
            const std::string previousUpdateCheckpoint
                = SystemProperty<std::string>::Get(UPDATE_SECTION_NAME, LAST_UPDATE_CHECK_NAME);
            if(previousUpdateCheckpoint.empty() == false)
            {
                try
                {
                    const double previousTimestamp = std::stod(previousUpdateCheckpoint);
                    if(previousTimestamp > 0)
                    {
                        const double        now                = QueryCurrentTimeAsSeconds();
                        const double        delta              = (now - previousTimestamp);
                        static const double ONE_DAY_IN_SECONDS = 60.0 * 60.0 * 24.0;
                        if(delta > ONE_DAY_IN_SECONDS) // standard timeout (24h)
                        {
                            updateCheckRequired = true;
                        }
                    }
                    else // inconsistency in reaper-extstate.ini (timeout less or equal to zero make no sense), force
                         // update check
                    {
                        updateCheckRequired = true;
                    }
                }
                catch(
                    std::invalid_argument&) // inconsistency in reaper-extstate.ini (number format), force update check
                {
                    updateCheckRequired = true;
                }
                catch(std::out_of_range&) // inconsistency in reaper-extstate.ini (overflow), force update check
                {
                    updateCheckRequired = true;
                }
            }
            else // inconsistency in reaper-extstate.ini, force update check
            {
                updateCheckRequired = true;
            }
        }
        else // initial status, force update check
        {
            updateCheckRequired = true;
        }

        if(true == updateCheckRequired)
        {
            void* curlHandle = curl_easy_init();
            if(curlHandle != 0)
            {
                const std::string url = "https://ultraschall.io/ultraschall_release.txt";
                curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curlHandle, CURLOPT_FOLLOWLOCATION, 1L);
                curl_easy_setopt(curlHandle, CURLOPT_NOSIGNAL, 1);
                curl_easy_setopt(curlHandle, CURLOPT_ACCEPT_ENCODING, "deflate");
                curl_easy_setopt(curlHandle, CURLOPT_WRITEFUNCTION, write_data);

                std::stringstream out;
                curl_easy_setopt(curlHandle, CURLOPT_WRITEDATA, &out);

                const CURLcode res = curl_easy_perform(curlHandle);
                if(res == CURLE_OK)
                {
                    std::string remoteVersion = out.str();
                    if(remoteVersion.empty() == false)
                    {
                        UnicodeStringTrim(remoteVersion);
                        const std::string localVersion = VersionHandler::PluginVersion();
                        if(remoteVersion > localVersion)
                        {
                            UIMessageSupervisor supervisor;
                            std::string message = "An update for Ultraschall is available. Go to "
                                                  "http://ultraschall.fm/install to download the updated version ";
                            message += remoteVersion + ".";
                            supervisor.RegisterSuccess(message);
                        }
                    }
                }

                curl_easy_cleanup(curlHandle);
                curlHandle = 0;

                const double      nextTimestamp        = QueryCurrentTimeAsSeconds();
                const std::string nextUpdateCheckpoint = std::to_string(nextTimestamp);
                if(nextUpdateCheckpoint.empty() == false)
                {
                    SystemProperty<std::string>::Save(
                        UPDATE_SECTION_NAME, LAST_UPDATE_CHECK_NAME, nextUpdateCheckpoint);
                }
            }
        }
    }
}

}} // namespace ultraschall::reaper
