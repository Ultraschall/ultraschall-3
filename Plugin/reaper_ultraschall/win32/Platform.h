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

#ifndef __ULTRASCHALL_REAPER_PLATFORM_H_INCL__
#define __ULTRASCHALL_REAPER_PLATFORM_H_INCL__

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#else // #ifdef _WIN32
#ifdef _APPLE_
#ifdef min
#undef min
#endif // #ifdef min
#ifdef max
#undef max
#endif // #ifdef max
#else  // #ifdef _APPLE_
// TODO linux
#endif // #ifdef _APPLE_
#endif // #ifdef _WIN32

#include "Common.h"

namespace ultraschall { namespace reaper {

class Platform
{
public:
    static const std::string THEME_PATH;
    static const std::string SOUNDBOARD_PATH;
    static const std::string SWS_PATH;
    static const std::string PLUGIN_PATH;
    static const std::string STUDIO_LINK_PATH;
    static const std::string STUDIO_LINK_ONAIR_PATH;

    static std::string ProgramFilesDirectory();
    static std::string UserDataDirectory();

    static char PathSeparator();

    static bool FileExists(const std::string& path);
    static std::string ReadFileVersion(const std::string& path);
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_PLATFORM_H_INCL__
