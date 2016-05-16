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
#include <sstream>
#include <Framework.h>
#include <StringUtilities.h>
#include "VersionString.h"

namespace ultraschall { namespace reaper {

VersionString::VersionString(const uint8_t majorVersion, const uint8_t minorVersion, 
                             const uint8_t servicePackVersion, const uint8_t hotfixVersion) :
    majorVersion_(majorVersion), minorVersion_(minorVersion), 
    servicePackVersion_(servicePackVersion), hotfixVersion_(hotfixVersion)
{
}

uint8_t VersionString::VersionValueFromString(const std::string& str)
{
    uint8_t versionValue = INVALID_VERSION_VALUE;

    if(str.empty() == false)
    {
        int valueBuffer = static_cast<int>(INVALID_VERSION_VALUE);
        if((std::istringstream(str.c_str()) >> valueBuffer).fail() == false)
        {
            versionValue = static_cast<uint8_t>(valueBuffer);
        }
        else
        {
            versionValue = INVALID_VERSION_VALUE;
        }
    }

    return versionValue;
}

VersionString VersionString::FromString(const std::string& str, const bool setDefaults)
{
    PRECONDITION_RETURN(str.empty() == false, VersionString::Invalid());

    VersionString result = VersionString::Invalid();

    std::vector<std::string> versionParts = framework::split(str, VERSION_PARTS_SEPARATOR);
    if(versionParts.size() >= MIN_VERSION_COMPONENTS_COUNT)
    {
        result.SetMajorVersion(VersionValueFromString(versionParts[0]));
        result.SetMinorVersion(VersionValueFromString(versionParts[1]));

        if(versionParts.size() >= (MIN_VERSION_COMPONENTS_COUNT + 1))
        {
            result.SetServicePackVersion(VersionValueFromString(versionParts[2]));
        }
        else if(setDefaults == true)
        {
            result.SetServicePackVersion(DEFAULT_SERVICE_PACK_VERSION);
        }

        if(versionParts.size() >= (MIN_VERSION_COMPONENTS_COUNT + 2))
        {
            result.SetServicePackVersion(VersionValueFromString(versionParts[3]));
        }
        else if(setDefaults == true)
        {
            result.SetHotfixVersion(DEFAULT_HOTFIX_VERSION);
        }
    }

    return result;
}

std::string VersionString::StringFromVersionValue(const uint8_t versionValue)
{
    if(versionValue != 0)
    {
        std::stringstream stream;
        stream << versionValue;
        return stream.str();
    }
    else
    {
        return "0";
    }
}

std::string VersionString::ToString(const VersionString& versionString)
{
    std::stringstream stream;

    if(versionString.IsValid() == true)
    {
        stream << StringFromVersionValue(versionString.MajorVersion());
        stream << VERSION_PARTS_SEPARATOR;
        stream << StringFromVersionValue(versionString.MinorVersion());

        if(versionString.ServicePackVersion() != INVALID_SERVICE_PACK_VERSION)
        {
            stream << VERSION_PARTS_SEPARATOR;
            stream << StringFromVersionValue(versionString.ServicePackVersion());

            if(versionString.HotfixVersion() != INVALID_HOTFIX_VERSION)
            {
                stream << VERSION_PARTS_SEPARATOR;
                stream << StringFromVersionValue(versionString.HotfixVersion());
            }
        }
    }

    return stream.str();
}

VersionString VersionString::Invalid()
{
    return VersionString(INVALID_MAJOR_VERSION, INVALID_MINOR_VERSION, 
                         INVALID_SERVICE_PACK_VERSION, INVALID_HOTFIX_VERSION);
}

bool VersionString::IsValid() const
{
    return (MajorVersion() != INVALID_MAJOR_VERSION) &&
            (MinorVersion() != INVALID_MINOR_VERSION) &&
            (ServicePackVersion() != INVALID_SERVICE_PACK_VERSION) &&
            (HotfixVersion() != INVALID_HOTFIX_VERSION);
}

bool operator==(const VersionString& left, const VersionString& right)
{
    PRECONDITION_RETURN(left.IsValid() == false, false);
    PRECONDITION_RETURN(right.IsValid() == false, false);

    return (left.MajorVersion() == right.MajorVersion()) &&
            (left.MinorVersion() == right.MinorVersion()) &&
            (left.ServicePackVersion() == right.ServicePackVersion()) &&
            (left.HotfixVersion() == right.HotfixVersion());
}

bool operator!=(const VersionString& left, const VersionString& right)
{
    return operator==(left, right) == false;
}

bool operator<(const VersionString& left, const VersionString& right)
{
    PRECONDITION_RETURN(left.IsValid() == false, false);
    PRECONDITION_RETURN(right.IsValid() == false, false);

    bool result = false;

    if(left != right)
    {
        if(left.MajorVersion() < right.MajorVersion())
        {
            result = true;
        }
        else if(left.MinorVersion() < right.MinorVersion())
        {
            result = true;
        }
        else if(left.ServicePackVersion() < right.ServicePackVersion())
        {
            result = true;
        }
        else if(left.HotfixVersion() < right.HotfixVersion())
        {
            result = true;
        }
        else
        {
            result = false;
        }
    }

    return result;
}

}}
