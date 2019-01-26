////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

#include "StringUtilities.h"
#include <codecvt>

#include "wx/wx.h"

namespace ultraschall { namespace reaper {

std::string StringLowercase(const std::string& str)
{
    std::string convertedString = str;
    if (convertedString.empty() == false)
    {
        std::transform(convertedString.begin(), convertedString.end(), convertedString.begin(), ::tolower);
    }

    return convertedString;
}

std::string StringUppercase(const std::string& str)
{
    std::string convertedString = str;
    if (convertedString.empty() == false)
    {
        std::transform(convertedString.begin(), convertedString.end(), convertedString.begin(), ::toupper);
    }

    return convertedString;
}

UnicodeString MakeUTF16BOM()
{
    UnicodeString result;

    UnicodeChar bom     = 0;
    ((uint8_t*)&bom)[0] = 0xff;
    ((uint8_t*)&bom)[1] = 0xfe;
    result += bom;

    return result;
}

#define UTF16_BOM MakeUTF16BOM()

UnicodeString MakeUnicodeString(const std::string& src)
{
    UnicodeString result;

    try
    {
#ifdef ULTRASCHALL_PLATFORM_WIN32
        result = AnsiStringToWideUnicodeString(src);
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> stringConverter;
        result = stringConverter.from_bytes(src);
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32
    }
    catch (std::range_error&)
    {
        result.clear();
    }

    return result;
}

UnicodeString MakeUnicodeString2(const std::string& src)
{
    UnicodeString result;

    try
    {
#ifdef ULTRASCHALL_PLATFORM_WIN32
        result = UnicodeStringToWideUnicodeString(src);
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> stringConverter;
        result = stringConverter.from_bytes(src);
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32
    }
    catch (std::range_error&)
    {
        result.clear();
    }

    return result;
}

UnicodeString MakeUTF16StringWithBOM(const std::string& src)
{
    return UTF16_BOM + MakeUnicodeString(src);
}

UnicodeString MakeUTF16StringWithBOM2(const std::string& src)
{
    return UTF16_BOM + MakeUnicodeString2(src);
}

std::string MakeUTF8String(const UnicodeString& src)
{
    std::string result;

    size_t offset = 0;
    if (src.size() > 1)
    {
        if (src[0] == (UnicodeChar)0xfffe)
        {
            offset = 1;
        }
    }

    try
    {
#ifdef ULTRASCHALL_PLATFORM_WIN32
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> stringConverter;
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> stringConverter;
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32
        result = stringConverter.to_bytes(&src[offset]);
    }
    catch (std::range_error&)
    {
        result.clear();
    }

    return result;
}

#ifdef ULTRASCHALL_PLATFORM_WIN32
#include <windows.h>
std::string AnsiStringToUnicodeString(const std::string& str)
{
    std::string unicodeString;

    if (str.empty() == false)
    {
        const int wideStringBufferLength = MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.length(), 0, 0);
        if (wideStringBufferLength > 0)
        {
            WCHAR* wideStringBuffer = (WCHAR*)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
            if (wideStringBuffer != 0)
            {
                int convertedBytes = MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.length(), wideStringBuffer, wideStringBufferLength);
                if (convertedBytes > 0)
                {
                    const int narrowStringBufferLength = WideCharToMultiByte(CP_UTF8, 0, wideStringBuffer, wideStringBufferLength, 0, 0, 0, 0);
                    if (narrowStringBufferLength > 0)
                    {
                        CHAR* narrowStringBuffer = (CHAR*)calloc(sizeof(CHAR), narrowStringBufferLength + 1);
                        if (narrowStringBuffer != 0)
                        {
                            convertedBytes
                                = WideCharToMultiByte(CP_UTF8, 0, wideStringBuffer, wideStringBufferLength, narrowStringBuffer, narrowStringBufferLength, 0, 0);
                            if (convertedBytes > 0)
                            {
                                unicodeString = narrowStringBuffer;
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
    }

    return unicodeString;
}

std::wstring UnicodeStringToWideUnicodeString(const std::string& unicodeString)
{
    PRECONDITION_RETURN(unicodeString.empty() == false, std::wstring());

    std::wstring wideUnicodeString;

    const int wideStringBufferLength = MultiByteToWideChar(CP_UTF8, 0, unicodeString.c_str(), (int)unicodeString.length(), 0, 0);
    if (wideStringBufferLength > 0)
    {
        WCHAR* wideStringBuffer = (WCHAR*)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
        if (wideStringBuffer != 0)
        {
            int convertedBytes = MultiByteToWideChar(CP_UTF8, 0, unicodeString.c_str(), (int)unicodeString.length(), wideStringBuffer, wideStringBufferLength);
            if (convertedBytes > 0)
            {
                wideUnicodeString = wideStringBuffer;
            }

            free(wideStringBuffer);
            wideStringBuffer = 0;
        }
    }

    return wideUnicodeString;
}

std::wstring AnsiStringToWideUnicodeString(const std::string& ansiString)
{
    PRECONDITION_RETURN(ansiString.empty() == false, std::wstring());

    std::wstring wideUnicodeString;

    const int wideStringBufferLength = MultiByteToWideChar(CP_ACP, 0, ansiString.c_str(), (int)ansiString.length(), 0, 0);
    if (wideStringBufferLength > 0)
    {
        WCHAR* wideStringBuffer = (WCHAR*)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
        if (wideStringBuffer != 0)
        {
            int convertedBytes = MultiByteToWideChar(CP_ACP, 0, ansiString.c_str(), (int)ansiString.length(), wideStringBuffer, wideStringBufferLength);
            if (convertedBytes > 0)
            {
                wideUnicodeString = wideStringBuffer;
            }

            free(wideStringBuffer);
            wideStringBuffer = 0;
        }
    }

    return wideUnicodeString;
}

std::string UnicodeStringToAnsiString(const std::string& str, int codepage)
{
    std::string ansiString;

    if (str.empty() == false)
    {
        const int wideStringBufferLength = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), 0, 0);
        if (wideStringBufferLength > 0)
        {
            WCHAR* wideStringBuffer = (WCHAR*)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
            if (wideStringBuffer != 0)
            {
                int convertedBytes = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), wideStringBuffer, wideStringBufferLength);
                if (convertedBytes > 0)
                {
                    const int narrowStringBufferLength = WideCharToMultiByte(codepage, 0, wideStringBuffer, wideStringBufferLength, 0, 0, 0, 0);
                    if (narrowStringBufferLength > 0)
                    {
                        CHAR* narrowStringBuffer = (CHAR*)calloc(sizeof(CHAR), narrowStringBufferLength + 1);
                        if (narrowStringBuffer != 0)
                        {
                            convertedBytes = WideCharToMultiByte(
                                codepage, 0, wideStringBuffer, wideStringBufferLength, narrowStringBuffer, narrowStringBufferLength, 0, 0);
                            if (convertedBytes > 0)
                            {
                                ansiString = narrowStringBuffer;
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
    }

    return ansiString;
}

UnicodeString2 MakeUTF16String2(const std::string& str)
{
    PRECONDITION_RETURN(str.empty() == false, UnicodeString2());

    UnicodeString2 result;

    int size = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), (int)str.size(), 0, 0);
    if (size > 0)
    {
        wchar_t* data = new wchar_t[size]();
        if (data != 0)
        {
            int numCharsConverted = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), (int)str.size(), data, size);
            if (numCharsConverted > 0)
            {
                result = UnicodeString2((uint8_t*)data, size * sizeof(wchar_t));
            }

            SafeDeleteArray(data);
        }
    }

    return result;
}

UnicodeString2 MakeUTF8String2(const std::string& str)
{
    PRECONDITION_RETURN(str.empty() == false, UnicodeString2());

    UnicodeString2 result;

    int size16 = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), (int)str.size(), 0, 0);
    if (size16 > 0)
    {
        wchar_t* data16 = new wchar_t[size16]();
        if (data16 != 0)
        {
            int numCharsConverted = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), (int)str.size(), data16, size16);
            if (numCharsConverted > 0)
            {
                int size8 = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, data16, size16, 0, 0, 0, 0);
                if (size8 > 0)
                {
                    char* data8 = new char[size8]();
                    if (data8 != 0)
                    {
                        numCharsConverted = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, data16, size16, data8, size8, 0, 0);
                        if (numCharsConverted > 0)
                        {
                            result = UnicodeString2((uint8_t*)data8, size8);
                        }

                        SafeDeleteArray(data8);
                    }
                }
            }

            SafeDeleteArray(data16);
        }
    }

    return result;
}

UnicodeStringSz2 MakeUTF16StringSz2(const std::string& str)
{
    PRECONDITION_RETURN(str.empty() == false, UnicodeStringSz2());

    UnicodeStringSz2 result;

    int size = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), (int)str.size(), 0, 0);
    if (size > 0)
    {
        wchar_t* data = new wchar_t[size]();
        if (data != 0)
        {
            int numCharsConverted = (size_t)MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), (int)str.size(), data, size);
            if (numCharsConverted > 0)
            {
                result = UnicodeStringSz2((uint8_t*)data, size * sizeof(wchar_t));
            }

            SafeDeleteArray(data);
        }
    }

    return result;
}

UnicodeStringSz2 MakeUTF8StringSz2(const std::string& str)
{
    PRECONDITION_RETURN(str.empty() == false, UnicodeStringSz2());

    UnicodeStringSz2 result;

    int size16 = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), (int)str.size(), 0, 0);
    if (size16 > 0)
    {
        wchar_t* data16 = new wchar_t[size16]();
        if (data16 != 0)
        {
            int numCharsConverted = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, str.c_str(), (int)str.size(), (LPWSTR)data16, size16);
            if (numCharsConverted > 0)
            {
                int size8 = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, data16, size16, 0, 0, 0, 0);
                if (size8 > 0)
                {
                    char* data8 = new char[size8]();
                    if (data8 != 0)
                    {
                        numCharsConverted = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, data16, size16, data8, size8, 0, 0);
                        if (numCharsConverted > 0)
                        {
                            result = UnicodeStringSz2((uint8_t*)data8, size8);
                        }

                        SafeDeleteArray(data8);
                    }
                }
            }

            SafeDeleteArray(data16);
        }
    }

    return result;
}
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
std::string AnsiStringToUnicodeString(const std::string& ansiString)
{
    return ansiString;
}

std::string UnicodeStringToAnsiString(const std::string& unicodeString, int)
{
    return unicodeString;
}

UnicodeString2 MakeUTF16String2(const std::string& str)
{
    PRECONDITION_RETURN(str.empty() == false, UnicodeString2());

    UnicodeString2 result;

    try
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> stringConverter;
        std::u16string buffer = stringConverter.from_bytes(str);
        if (buffer.empty() == false)
        {
            result = UnicodeString2(reinterpret_cast<const uint8_t*>(buffer.c_str()), buffer.size());
        }
    }
    catch (std::range_error&)
    {
        result.Clear();
    }

    return result;
}

UnicodeString2 MakeUTF8String2(const std::string& str)
{
    PRECONDITION_RETURN(str.empty() == false, UnicodeString2());

    return UnicodeString2(str);
}

UnicodeStringSz2 MakeUTF16StringSz2(const std::string& str)
{
    PRECONDITION_RETURN(str.empty() == false, UnicodeStringSz2());

    UnicodeStringSz2 result;

    try
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> stringConverter;
        std::u16string buffer = stringConverter.from_bytes(str);
        if (buffer.empty() == false)
        {
            result = UnicodeStringSz2(reinterpret_cast<const uint8_t*>(buffer.c_str()), buffer.size());
        }
    }
    catch (std::range_error&)
    {
        result.Clear();
    }

    return result;
}

UnicodeStringSz2 MakeUTF8StringSz2(const std::string& str)
{
    PRECONDITION_RETURN(str.empty() == false, UnicodeStringSz2());

    return UnicodeStringSz2(str);
}
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32

}} // namespace ultraschall::reaper
