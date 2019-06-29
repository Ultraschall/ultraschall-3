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

#ifndef __ULTRASCHALL_FRAMEWORK_UNICODE_STRING_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_UNICODE_STRING_H_INCL__

#include <map>
#include <string>
#include <sstream>
#include <vector>

namespace ultraschall { namespace reaper {

typedef char     UnicodeChar;
typedef char16_t WideUnicodeChar;

typedef std::string    UnicodeString;
typedef std::u16string WideUnicodeString;

typedef std::stringstream                                                                       UnicodeStringStream;
typedef std::basic_stringstream<char16_t, std::char_traits<char16_t>, std::allocator<char16_t>> WideUnicodeStringStream;

typedef std::vector<UnicodeString>             UnicodeStringArray;
typedef std::map<UnicodeString, UnicodeString> UnicodeStringDictionary;

typedef std::vector<WideUnicodeString>                 WideUnicodeStringArray;
typedef std::map<WideUnicodeString, WideUnicodeString> WideUnicodeStringDictionary;

typedef enum { UTF8, UTF16 } CHAR_ENCODING;

typedef enum { NO_UTF16_BOM = 0, WITH_UTF16_BOM_LE = 1, WITH_UTF16_BOM_BE = 2 } UTF16_BOM_SPEC;
static const char16_t* UTF16_BOM_LE = u"\xfffe"; // intel
static const char16_t* UTF16_BOM_BE = u"\xfeff";

WideUnicodeString UnicodeStringToWideUnicodeString(
    const UnicodeString& uncodeString, const UTF16_BOM_SPEC bomSpec = NO_UTF16_BOM);

typedef enum { NO_UTF8_BOM = 0, WITH_UTF8_BOM = 1 } UTF8_BOM_SPEC;
static const char* UTF8_BOM = "\xef\xbb\xbf";

UnicodeString WideUnicodeStringToUnicodeString(
    const WideUnicodeString& wideUnicodeString, const UTF8_BOM_SPEC bomSpec = NO_UTF8_BOM);

UnicodeString HostStringToUnicodeString(const std::string& hostString, const UTF8_BOM_SPEC bomSpec = NO_UTF8_BOM);

WideUnicodeString HostStringToWideUnicodeString(
    const std::string& hostString, const UTF16_BOM_SPEC bomSpec = NO_UTF16_BOM);

std::string UnicodeStringToHostString(const UnicodeString& unicodeString);
std::string WideUnicodeStringToHostString(const WideUnicodeString& wideUnicodeString);

#define H2U(a) HostStringToUnicodeString((a))
#define H2WU(a) HostStringToWideUnicodeString((a))

#define U2H(a) UnicodeStringToHostString((a))
#define WU2H(a) WideUnicodeStringToHostString((a))

#define U2WU(a) UnicodeStringToWideUnicodeString((a))
#define WU2U(a) WideUnicodeStringToUnicodeString((a))

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_UNICODE_STRING_H_INCL__
