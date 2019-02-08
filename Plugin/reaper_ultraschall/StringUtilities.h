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

#ifndef __ULTRASCHALL_REAPER_STRING_UTILITIES_H_INCL__
#define __ULTRASCHALL_REAPER_STRING_UTILITIES_H_INCL__

#include "Common.h"

namespace ultraschall { namespace reaper {

#define _MAKE_TEXT(str) #str
#define MAKE_TEXT(str) _MAKE_TEXT(str)

inline UnicodeStringArray StringTokenize(const UnicodeString& input, const char delimiter)
{
    UnicodeStringArray tokens;
    std::stringstream        stream(input);
    UnicodeString              token;

    while (std::getline(stream, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

// trim from start
static inline UnicodeString& StringTrimLeft(UnicodeString& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline UnicodeString& StringTrimRight(UnicodeString& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline UnicodeString& StringTrim(UnicodeString& s)
{
    return StringTrimLeft(StringTrimRight(s));
}

static inline void StringReplace(UnicodeString& str, const UnicodeString& source, const UnicodeString& target)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(source, start_pos)) != UnicodeString::npos)
    {
        str.replace(start_pos, source.length(), target);
        start_pos += target.length();
    }
}

static inline int StringToInt(const UnicodeString& str)
{
    int result = -1;

    if (str.empty() == false)
    {
        std::istringstream is(str);
        is >> result;
    }

    return result;
}

UnicodeString StringLowercase(const UnicodeString& str);
UnicodeString StringUppercase(const UnicodeString& str);

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_STRING_UTILITIES_H_INCL__
