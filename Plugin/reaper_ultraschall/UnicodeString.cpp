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
#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif // #ifdef _WIN32
#include <codecvt>
#ifdef _WIN32
#undef _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
#endif // #ifdef _WIN32

#include <locale>

#include "Common.h"
#include "UnicodeString.h"

namespace ultraschall { namespace reaper {

#ifdef _WIN32
#include <windows.h>

UnicodeString HostStringToUnicodeString(const std::string& hostString, const UTF8_BOM_SPEC bomSpec)
{
    PRECONDITION_RETURN(hostString.empty() == false, UnicodeString());

    UnicodeString unicodeString;

    if(bomSpec == WITH_UTF8_BOM)
    {
        unicodeString += UTF8_BOM;
    }

    const int wideStringBufferLength = MultiByteToWideChar(0, 0, hostString.c_str(), (int)hostString.length(), 0, 0);
    if(wideStringBufferLength > 0)
    {
        WCHAR* wideStringBuffer = (WCHAR*)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
        if(wideStringBuffer != 0)
        {
            int convertedBytes = MultiByteToWideChar(0, 0, hostString.c_str(), (int)hostString.length(), wideStringBuffer, wideStringBufferLength);
            if(convertedBytes > 0)
            {
                const int narrowStringBufferLength = WideCharToMultiByte(65001, 0, wideStringBuffer, wideStringBufferLength, 0, 0, 0, 0);
                if(narrowStringBufferLength > 0)
                {
                    CHAR* narrowStringBuffer = (CHAR*)calloc(sizeof(CHAR), narrowStringBufferLength + 1);
                    if(narrowStringBuffer != 0)
                    {
                        convertedBytes
                            = WideCharToMultiByte(65001, 0, wideStringBuffer, wideStringBufferLength, narrowStringBuffer, narrowStringBufferLength, 0, 0);
                        if(convertedBytes > 0)
                        {
                            unicodeString += narrowStringBuffer;
                        }

                        free(narrowStringBuffer);
                        narrowStringBuffer = 0;
                    }
                }
            }

            free(wideStringBuffer);
            wideStringBuffer = 0;
        }
    }

    return unicodeString;
}

WideUnicodeString HostStringToWideUnicodeString(const std::string& hostString, const UTF16_BOM_SPEC bomSpec)
{
    PRECONDITION_RETURN(hostString.empty() == false, WideUnicodeString());

    WideUnicodeString wideUnicodeString;

    if(bomSpec == WITH_UTF16_BOM_LE)
    {
        wideUnicodeString = UTF16_BOM_LE;
    }
    else if(bomSpec == WITH_UTF16_BOM_BE)
    {
        wideUnicodeString = UTF16_BOM_BE;
        // TODO swap
    }

    const int wideStringBufferLength = MultiByteToWideChar(0, 0, hostString.c_str(), (int)hostString.length(), 0, 0);
    if(wideStringBufferLength > 0)
    {
        char16_t* wideStringBuffer = (char16_t*)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
        if(wideStringBuffer != 0)
        {
            int convertedBytes = MultiByteToWideChar(0, 0, hostString.c_str(), (int)hostString.length(), (LPWSTR)wideStringBuffer, wideStringBufferLength);
            if(convertedBytes > 0)
            {
                wideUnicodeString += wideStringBuffer;
            }

            free(wideStringBuffer);
            wideStringBuffer = 0;
        }
    }

    return wideUnicodeString;
}

std::string UnicodeStringToHostString(const UnicodeString& unicodeString)
{
    PRECONDITION_RETURN(unicodeString.empty() == false, std::string());

    std::string hostString;

    size_t      unicodeStringBufferLength = unicodeString.size();
    const char* unicodeStringBuffer       = unicodeString.data();
    if(unicodeString.size() >= 3)
    {
        if(strncmp(unicodeStringBuffer, UTF8_BOM, sizeof(char) * 3) == 0)
        {
            unicodeStringBufferLength -= sizeof(char) * 3;
            unicodeStringBuffer = &(unicodeStringBuffer[3]);
        }
    }

    const int wideStringBufferLength = MultiByteToWideChar(65001, 0, unicodeStringBuffer, (int)unicodeStringBufferLength, 0, 0);
    if(wideStringBufferLength > 0)
    {
        char16_t* wideStringBuffer = (char16_t*)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
        if(wideStringBuffer != 0)
        {
            int convertedBytes
                = MultiByteToWideChar(65001, 0, unicodeStringBuffer, (int)unicodeStringBufferLength, (LPWSTR)wideStringBuffer, wideStringBufferLength);
            if(convertedBytes > 0)
            {
                const int hostStringBufferLength = WideCharToMultiByte(0, 0, (LPWCH)wideStringBuffer, wideStringBufferLength, 0, 0, 0, 0);
                if(hostStringBufferLength > 0)
                {
                    CHAR* hostStringBuffer = (CHAR*)calloc(sizeof(CHAR), hostStringBufferLength + 1);
                    if(hostStringBuffer != 0)
                    {
                        convertedBytes
                            = WideCharToMultiByte(0, 0, (LPWCH)wideStringBuffer, wideStringBufferLength, hostStringBuffer, hostStringBufferLength, 0, 0);
                        if(convertedBytes > 0)
                        {
                            hostString = hostStringBuffer;
                        }

                        free(hostStringBuffer);
                        hostStringBuffer = 0;
                    }
                }
            }

            free(wideStringBuffer);
            wideStringBuffer = 0;
        }
    }

    return hostString;
}

std::string WideUnicodeStringToHostString(const WideUnicodeString& wideUnicodeString)
{
    PRECONDITION_RETURN(wideUnicodeString.empty() == false, std::string());

    std::string hostString;

    size_t          wideUnicodeStringBufferLength = wideUnicodeString.size();
    const char16_t* wideUnicodeStringBuffer       = wideUnicodeString.data();
    if(wideUnicodeString.size() >= 3)
    {
        if(memcmp(wideUnicodeStringBuffer, UTF16_BOM_LE, sizeof(char16_t)) == 0)
        {
            wideUnicodeStringBufferLength -= 1;
            wideUnicodeStringBuffer = &(wideUnicodeStringBuffer[1]);
        }
        else if(memcmp(wideUnicodeStringBuffer, UTF16_BOM_BE, sizeof(char16_t)) == 0)
        {
            wideUnicodeStringBufferLength -= 1;
            wideUnicodeStringBuffer = &(wideUnicodeStringBuffer[1]);
            // TODO swap
        }
    }

    const int hostStringBufferLength = WideCharToMultiByte(0, 0, (LPWCH)wideUnicodeStringBuffer, (int)wideUnicodeStringBufferLength, 0, 0, 0, 0);
    if(hostStringBufferLength > 0)
    {
        CHAR* hostStringBuffer = (CHAR*)calloc(sizeof(CHAR), hostStringBufferLength + 1);
        if(hostStringBuffer != 0)
        {
            const int convertedBytes
                = WideCharToMultiByte(0, 0, (LPWCH)wideUnicodeStringBuffer, (int)wideUnicodeStringBufferLength, hostStringBuffer, hostStringBufferLength, 0, 0);
            if(convertedBytes > 0)
            {
                hostString = hostStringBuffer;
            }

            free(hostStringBuffer);
            hostStringBuffer = 0;
        }
    }

    return hostString;
}

#else // #ifdef _WIN32

UnicodeString HostStringToUnicodeString(const std::string& hostString, const UTF8_BOM_SPEC bomSpec)
{
    UnicodeString unicodeString;

    if(bomSpec == WITH_UTF8_BOM)
    {
        unicodeString = UTF8_BOM;
    }
    return unicodeString + hostString;
}

WideUnicodeString HostStringToWideUnicodeString(const std::string& hostString, const UTF16_BOM_SPEC bomSpec)
{
    return UnicodeStringToWideUnicodeString(hostString, bomSpec);
}

std::string UnicodeStringToHostString(const UnicodeString& unicodeString)
{
    return unicodeString;
}

std::string WideUnicodeStringToHostString(const WideUnicodeString& wideUnicodeString)
{
    return WideUnicodeStringToUnicodeString(wideUnicodeString);
}

#endif // #ifdef _WIN32

WideUnicodeString UnicodeStringToWideUnicodeString(const UnicodeString& unicodeString, const UTF16_BOM_SPEC bomSpec)
{
    PRECONDITION_RETURN(unicodeString.empty() == false, WideUnicodeString());

    WideUnicodeString wideUnicodeString;

    UnicodeString unicodeData = unicodeString;
    if(unicodeData.size() >= 3)
    {
        if(unicodeData.substr(0, 3) == UTF8_BOM)
        {
            unicodeData = unicodeData.substr(3);
        }
    }

    if(bomSpec == WITH_UTF16_BOM_LE)
    {
        wideUnicodeString = UTF16_BOM_LE;
    }
    else if(bomSpec == WITH_UTF16_BOM_BE)
    {
        wideUnicodeString = UTF16_BOM_BE;
    }

#if _WIN32
    std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> converter;
    const char*                                                     p = reinterpret_cast<const char*>(unicodeData.data());
    wideUnicodeString += (char16_t*)converter.from_bytes(p, p + unicodeData.size()).data();
#else  // #if _WIN32
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    wideUnicodeString += converter.from_bytes(unicodeData);
#endif // #if _WIN32

    return wideUnicodeString;
}
UnicodeString WideUnicodeStringToUnicodeString(const WideUnicodeString& wideUnicodeString, const UTF8_BOM_SPEC bomSpec)
{
    PRECONDITION_RETURN(wideUnicodeString.empty() == false, UnicodeString());

    UnicodeString unicodeString;

    WideUnicodeString wideUnicodeData = wideUnicodeString;
    if(wideUnicodeData.size() >= 2)
    {
        if(wideUnicodeData.substr(0, 3) == UTF16_BOM_LE)
        {
            wideUnicodeData = wideUnicodeData.substr(3);
        }
        else if(wideUnicodeData.substr(0, 3) == UTF16_BOM_BE)
        {
            wideUnicodeData = wideUnicodeData.substr(3);
        }
    }

    if(bomSpec == WITH_UTF8_BOM)
    {
        unicodeString = UTF8_BOM;
    }

#if _WIN32
    std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;
    const int16_t*                                                  p = reinterpret_cast<const int16_t*>(wideUnicodeData.data());
    unicodeString += convert.to_bytes(p, p + wideUnicodeData.size());
#else  // #if _WIN32
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
    unicodeString += converter.to_bytes(wideUnicodeData);
#endif // #if _WIN32

    return unicodeString;
}

}} // namespace ultraschall::framework
