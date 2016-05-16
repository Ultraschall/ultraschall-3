////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2014-2016 Ultraschall (http://ultraschall.fm)
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

#include "ReaperVersionCheck.h"
#include "ReaperEntryPoints.h"
#include "FileManager.h"
#include "StringUtilities.h"
#include "VersionString.h"

namespace ultraschall { namespace reaper {

std::string QueryRawReaperVersion()
{
    std::string version;
    
    const std::vector<std::string> versionTokens = framework::split(reaper_api::GetAppVersion(), '/');
    const size_t MIN_VERSION_TOKEN_COUNT = 1;
    if(versionTokens.size() >= MIN_VERSION_TOKEN_COUNT)
    {
        version = versionTokens[0];
    }

    return version;
}

VersionString QueryReaperVersion()
{
    VersionString versionString = VersionString::Invalid();

    const std::string version = QueryRawReaperVersion();
    if(version.empty() == false)
    {
        const std::vector<std::string> versionTokens = framework::split(version, '/');
        const size_t MIN_VERSION_TOKEN_COUNT = 1;
        if(versionTokens.size() >= MIN_VERSION_TOKEN_COUNT)
        {
            versionString = VersionString::FromString(versionTokens[0]);
        }
    }

    return versionString;
}

bool ReaperVersionCheck()
{
    bool result = false;

    VersionString versionString = QueryReaperVersion();
    if(versionString.IsValid() == true)
    {
        const uint8_t MIN_REQUIRED_REAPER_MAJOR_VERSION = 5;
        const uint8_t MIN_REQUIRED_REAPER_MINOR_VERSION = 1;
        if((versionString.MajorVersion() >= MIN_REQUIRED_REAPER_MAJOR_VERSION) &&
           (versionString.MinorVersion() >= MIN_REQUIRED_REAPER_MINOR_VERSION))
        {
            result = true;
        }
    }

    return result;
}

bool ReaperPlatformCheck()
{
    bool supported = false;
    const std::string version = reaper_api::GetAppVersion();
    const std::vector<std::string> versionTokens = framework::split(version, '/');
    const size_t MIN_VERSION_TOKENS_COUNT = 2;
    if(versionTokens.size() >= MIN_VERSION_TOKENS_COUNT)
    {
        const std::string platform = versionTokens[1];
        supported = (platform == "x64");
    }

    return supported;
}

}}
