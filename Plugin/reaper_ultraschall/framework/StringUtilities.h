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

#ifndef __ULTRASCHALL_FRAMEWORK_STRING_UTILITIES_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_STRING_UTILITIES_H_INCL__

#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>

#include <Framework.h>

namespace ultraschall { namespace framework {
   
#define _MAKE_TEXT(str) #str
#define MAKE_TEXT(str) _MAKE_TEXT(str)

inline std::vector<std::string> split(const std::string& input, const char delimiter)
{
   std::vector<std::string> tokens;
   std::stringstream stream(input);
   std::string token;
   
   while (std::getline(stream, token, delimiter))
   {
      tokens.push_back(token);
   }
   
   return tokens;
}
   
// trim from start
static inline std::string &ltrim(std::string &s) {
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
   return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
   s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
   return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
   return ltrim(rtrim(s));
}

static inline void replace(std::string& str, const std::string& source, const std::string& target)
{
   size_t start_pos = 0;
   while((start_pos = str.find(source, start_pos)) != std::string::npos)
   {
      str.replace(start_pos, source.length(), target);
      start_pos += target.length();
   }
}
 
std::wstring MakeUTF16String(const std::string& src);

std::string MakeUTF8String(const std::wstring& src);

}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_STRING_UTILITIES_H_INCL__
