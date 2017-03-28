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

#include "StringUtilities.h"
#include <codecvt>

namespace ultraschall
{
namespace framework
{

std::string StringLowercase(const std::string& str)
{
   std::string convertedString = str;
   if(convertedString.empty() == false)
   {
      std::transform(convertedString.begin(), convertedString.end(), convertedString.begin(), ::tolower);
   }
   
   return convertedString;
}

std::string StringUppercase(const std::string& str)
{
   std::string convertedString = str;
   if(convertedString.empty() == false)
   {
      std::transform(convertedString.begin(), convertedString.end(), convertedString.begin(), ::toupper);
   }
   
   return convertedString;
}
   
UnicodeString MakeUTF16BOM()
{
      UnicodeString result;

      UnicodeChar bom = 0;
      ((uint8_t *)&bom)[0] = 0xff;
      ((uint8_t *)&bom)[1] = 0xfe;
      result += bom;

      return result;
}

#define UTF16_BOM MakeUTF16BOM()

UnicodeString MakeUnicodeString(const std::string &src)
{
      UnicodeString result;

      try
      {
#ifdef ULTRASCHALL_PLATFORM_MACOS
            std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> stringConverter;
            result = stringConverter.from_bytes(src);
#else
            result = AnsiStringToWideUnicodeString(src);
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS
      }
      catch (std::range_error &)
      {
            result.clear();
      }

      return result;
}

UnicodeString MakeUnicodeStringWithBOM(const std::string &src)
{
      return UTF16_BOM + MakeUnicodeString(src);
}

std::string MakeUTF8String(const UnicodeString &src)
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
#ifdef ULTRASCHALL_PLATFORM_MACOS
            std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> stringConverter;
#else
            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> stringConverter;
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS
            result = stringConverter.to_bytes(&src[offset]);
      }
      catch (std::range_error &)
      {
            result.clear();
      }

      return result;
}

#ifdef ULTRASCHALL_PLATFORM_MACOS
std::string AnsiStringToUnicodeString(const std::string &ansiString)
{
      return ansiString;
}

std::string UnicodeStringToAnsiString(const std::string &unicodeString, int)
{
      return unicodeString;
}
#else // #ifdef ULTRASCHALL_PLATFORM_MACOS
#ifdef ULTRASCHALL_PLATFORM_WIN32
#include <windows.h>
std::string AnsiStringToUnicodeString(const std::string &str)
{
      std::string unicodeString;

      if (str.empty() == false)
      {
            const int wideStringBufferLength = MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.length(), 0, 0);
            if (wideStringBufferLength > 0)
            {
                  WCHAR *wideStringBuffer = (WCHAR *)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
                  if (wideStringBuffer != nullptr)
                  {
                        int convertedBytes = MultiByteToWideChar(CP_ACP, 0, str.c_str(), (int)str.length(), wideStringBuffer, wideStringBufferLength);
                        if (convertedBytes > 0)
                        {
                              const int narrowStringBufferLength = WideCharToMultiByte(CP_UTF8, 0, wideStringBuffer, wideStringBufferLength, 0, 0, 0, 0);
                              if (narrowStringBufferLength > 0)
                              {
                                    CHAR *narrowStringBuffer = (CHAR *)calloc(sizeof(CHAR), narrowStringBufferLength + 1);
                                    if (narrowStringBuffer != nullptr)
                                    {
                                          convertedBytes = WideCharToMultiByte(CP_UTF8, 0, wideStringBuffer, wideStringBufferLength, narrowStringBuffer, narrowStringBufferLength, 0, 0);
                                          if (convertedBytes > 0)
                                          {
                                                unicodeString = narrowStringBuffer;
                                          }

                                          free(narrowStringBuffer);
                                          narrowStringBuffer = nullptr;
                                    }
                              }
                        }

                        free(wideStringBuffer);
                        wideStringBuffer = nullptr;
                  }
            }
      }

      return unicodeString;
}

std::wstring AnsiStringToWideUnicodeString(const std::string &ansiString)
{
      std::wstring wideUnicodeString;

      if (ansiString.empty() == false)
      {
            const int wideStringBufferLength = MultiByteToWideChar(CP_ACP, 0, ansiString.c_str(), (int)ansiString.length(), 0, 0);
            if (wideStringBufferLength > 0)
            {
                  WCHAR *wideStringBuffer = (WCHAR *)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
                  if (wideStringBuffer != nullptr)
                  {
                        int convertedBytes = MultiByteToWideChar(CP_ACP, 0, ansiString.c_str(), (int)ansiString.length(), wideStringBuffer, wideStringBufferLength);
                        if (convertedBytes > 0)
                        {
                              wideUnicodeString = wideStringBuffer;
                        }

                        free(wideStringBuffer);
                        wideStringBuffer = nullptr;
                  }
            }
      }

      return wideUnicodeString;
}

std::string UnicodeStringToAnsiString(const std::string &str, int codepage)
{
      std::string ansiString;

      if (str.empty() == false)
      {
            const int wideStringBufferLength = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), 0, 0);
            if (wideStringBufferLength > 0)
            {
                  WCHAR *wideStringBuffer = (WCHAR *)calloc(sizeof(WCHAR), wideStringBufferLength + 1);
                  if (wideStringBuffer != nullptr)
                  {
                        int convertedBytes = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.length(), wideStringBuffer, wideStringBufferLength);
                        if (convertedBytes > 0)
                        {
                              const int narrowStringBufferLength = WideCharToMultiByte(codepage, 0, wideStringBuffer, wideStringBufferLength, 0, 0, 0, 0);
                              if (narrowStringBufferLength > 0)
                              {
                                    CHAR *narrowStringBuffer = (CHAR *)calloc(sizeof(CHAR), narrowStringBufferLength + 1);
                                    if (narrowStringBuffer != nullptr)
                                    {
                                          convertedBytes = WideCharToMultiByte(codepage, 0, wideStringBuffer, wideStringBufferLength, narrowStringBuffer, narrowStringBufferLength, 0, 0);
                                          if (convertedBytes > 0)
                                          {
                                                ansiString = narrowStringBuffer;
                                          }

                                          free(narrowStringBuffer);
                                          narrowStringBuffer = nullptr;
                                    }
                              }
                        }

                        free(wideStringBuffer);
                        wideStringBuffer = nullptr;
                  }
            }
      }

      return ansiString;
}
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS
}
}
