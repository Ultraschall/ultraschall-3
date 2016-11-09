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

#ifndef __ULTRASCHALL_REAPER_VERSION_STRING_H_INCL__
#define __ULTRASCHALL_REAPER_VERSION_STRING_H_INCL__

#include <string>

namespace ultraschall { namespace reaper {

class VersionString
{
public:
    static const uint8_t INVALID_VERSION_VALUE = 0xff;

    static const uint8_t INVALID_MAJOR_VERSION = INVALID_VERSION_VALUE;
    static const uint8_t INVALID_MINOR_VERSION = INVALID_VERSION_VALUE;
    static const uint8_t INVALID_SERVICE_PACK_VERSION = INVALID_VERSION_VALUE;
    static const uint8_t INVALID_HOTFIX_VERSION = INVALID_VERSION_VALUE;

    static const uint8_t DEFAULT_SERVICE_PACK_VERSION = 0;
    static const uint8_t DEFAULT_HOTFIX_VERSION = 0;

    static const size_t MIN_VERSION_COMPONENTS_COUNT = 2;
    static const size_t MAX_VERSION_COMPONENTS_COUNT = 4;
    static const char VERSION_PARTS_SEPARATOR = '.';

    static VersionString FromString(const std::string& str, const bool setDefaults = true);
    static std::string ToString(const VersionString& versionString);

    static VersionString Invalid();

    bool IsValid() const;

    inline uint8_t MajorVersion() const;
    inline uint8_t MinorVersion() const;
    inline uint8_t ServicePackVersion() const;
    inline uint8_t HotfixVersion() const;

protected:
    inline void SetMajorVersion(const uint8_t majorVersion);
    inline void SetMinorVersion(const uint8_t minorVersion);
    inline void SetServicePackVersion(const uint8_t servicePackVersion);
    inline void SetHotfixVersion(const uint8_t hotfixVersion);

private:
    VersionString(const uint8_t majorVersion, const uint8_t minorVersion, 
                    const uint8_t servicePackVersion = DEFAULT_SERVICE_PACK_VERSION, 
                    const uint8_t hotfixVersion = DEFAULT_HOTFIX_VERSION);

    static std::string StringFromVersionValue(const uint8_t versionValue);
    static uint8_t VersionValueFromString(const std::string& str);

    uint8_t majorVersion_;
    uint8_t minorVersion_;
    uint8_t servicePackVersion_;
    uint8_t hotfixVersion_;
};

bool operator==(const VersionString& left, const VersionString& right);

bool operator!=(const VersionString& left, const VersionString& right);

bool operator<(const VersionString& left, const VersionString& right);

inline uint8_t VersionString::MajorVersion() const
{
    return majorVersion_;
}

inline uint8_t VersionString::MinorVersion() const
{
    return minorVersion_;
}

inline uint8_t VersionString::ServicePackVersion() const
{
    return servicePackVersion_;
}

inline uint8_t VersionString::HotfixVersion() const
{
    return hotfixVersion_;
}

inline void VersionString::SetMajorVersion(const uint8_t majorVersion)
{
    majorVersion_ = majorVersion;
}

inline void VersionString::SetMinorVersion(const uint8_t minorVersion)
{
    minorVersion_ = minorVersion;
}

inline void VersionString::SetServicePackVersion(const uint8_t servicePackVersion)
{
    servicePackVersion_ = servicePackVersion;
}

inline void VersionString::SetHotfixVersion(const uint8_t hotfixVersion)
{
    hotfixVersion_ = hotfixVersion;
}
}}

#endif // #ifndef __ULTRASCHALL_REAPER_VERSION_STRING_H_INCL__
