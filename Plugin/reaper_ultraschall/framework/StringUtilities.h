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

#ifndef __ULTRASCHALL_FRAMEWORK_STRING_UTILITIES_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_STRING_UTILITIES_H_INCL__

#include <string>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>

#include <Framework.h>

namespace ultraschall
{
  namespace framework
  {

#define _MAKE_TEXT(str) #str
#define MAKE_TEXT(str) _MAKE_TEXT(str)

    inline std::vector<std::string> StringTokenize(const std::string &input, const char delimiter)
    {
      std::vector<std::string> tokens;
      std::stringstream stream(input);
      std::string token;

      while(std::getline(stream, token, delimiter))
      {
        tokens.push_back(token);
      }

      return tokens;
    }

    // trim from start
    static inline std::string &StringTrimLeft(std::string &s)
    {
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
      return s;
    }

    // trim from end
    static inline std::string &StringTrimRight(std::string &s)
    {
      s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
      return s;
    }

    // trim from both ends
    static inline std::string &StringTrim(std::string &s)
    {
      return StringTrimLeft(StringTrimRight(s));
    }

    static inline void StringReplace(std::string &str, const std::string &source, const std::string &target)
    {
      size_t start_pos = 0;
      while((start_pos = str.find(source, start_pos)) != std::string::npos)
      {
        str.replace(start_pos, source.length(), target);
        start_pos += target.length();
      }
    }

    static inline int StringToInt(const std::string& str)
    {
      int result = -1;

      if(str.empty() == false)
      {
        std::istringstream is(str);
        is >> result;
      }

      return result;
    }

    std::string StringLowercase(const std::string& str);
    std::string StringUppercase(const std::string& str);

#ifdef ULTRASCHALL_PLATFORM_MACOS
    typedef char16_t UnicodeChar;
    typedef std::u16string UnicodeString;
#else
    typedef wchar_t UnicodeChar;
    typedef std::wstring UnicodeString;
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS

    UnicodeString MakeUnicodeString(const std::string &src);

    UnicodeString MakeUTF16StringWithBOM(const std::string &src);

    std::string MakeUTF8String(const UnicodeString &src);

    std::wstring AnsiStringToWideUnicodeString(const std::string& ansiString);

    std::string UnicodeStringToAnsiString(const std::string& unicodeString, int codepage = 0);

    struct UnicodeString2
    {
      uint8_t* data_;
      size_t size_;

      static const size_t INVALID_STRING_SIZE = static_cast<size_t>(-1);

      UnicodeString2() : data_(nullptr), size_(INVALID_STRING_SIZE)
      {
      }

      UnicodeString2(const std::string& str) : data_(nullptr), size_(INVALID_STRING_SIZE)
      {
        data_ = new uint8_t[str.size()]();
        if(data_ != nullptr)
        {
          memmove(data_, str.c_str(), ((str.size() > 0) ? str.size() : 1) * sizeof(uint8_t));
          size_ = str.size();
        }
      }

      UnicodeString2(const uint8_t* data, const size_t size) : data_(nullptr), size_(INVALID_STRING_SIZE)
      {
        if((data != nullptr) && (size != INVALID_STRING_SIZE))
        {
          data_ = new uint8_t[size]();
          if(data_ != nullptr)
          {
            memmove(data_, data, size * sizeof(uint8_t));
            size_ = size;
          }
        }
      }

      ~UnicodeString2()
      {
        SafeDeleteArray(data_);
        size_ = INVALID_STRING_SIZE;
      }

      UnicodeString2(const UnicodeString2& rhs) : data_(nullptr), size_(INVALID_STRING_SIZE)
      {
        *this = rhs;
      }

      void operator=(const UnicodeString2& rhs)
      {
        PRECONDITION(rhs.data_ != nullptr);
        PRECONDITION(rhs.size_ != INVALID_STRING_SIZE);

        SafeDeleteArray(data_);
        size_ = INVALID_STRING_SIZE;

        data_ = new uint8_t[rhs.size_]();
        if(data_ != nullptr)
        {
          memmove(data_, rhs.data_, rhs.size_ * sizeof(uint8_t));
          size_ = rhs.size_;
        }
      }

      UnicodeString2 operator+(const UnicodeString2& rhs) const
      {
        UnicodeString2 result;

        if((rhs.data_ != nullptr) && (rhs.size_ != INVALID_STRING_SIZE))
        {
          if((data_ != nullptr) && (size_ != INVALID_STRING_SIZE))
          {
            uint8_t* combinedData = new uint8_t[size_ + rhs.size_]();
            if(combinedData != nullptr)
            {
              memmove(combinedData, data_, size_);
              memmove(&combinedData[size_], rhs.data_, rhs.size_);

              result = UnicodeString2(combinedData, size_ + rhs.size_);

              SafeDeleteArray(combinedData);
            }
          }
          else
          {
            result = rhs;
          }
        }
        else
        {
          result = *this;
        }

        return result;
      }

      inline const uint8_t* data() const
      {
        return data_;
      }

      inline size_t size() const
      {
        return size_;
      }
    };

    UnicodeString2 MakeUTF16String2(const std::string str);
    UnicodeString2 MakeUTF8String2(const std::string str);

  }
}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_STRING_UTILITIES_H_INCL__
