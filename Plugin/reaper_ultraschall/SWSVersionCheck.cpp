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

#include "SWSVersionCheck.h"
#include "ByteStream.h"
#include "FileManager.h"
#include "FileUtilities.h"
#include "Platform.h"
#include <zlib.h>

namespace ultraschall { namespace reaper {

#ifdef ULTRASCHALL_PLATFORM_WIN32
std::string FindUltraschallPluginDirectory()
{
    std::string pluginDirectory;

    // TODO linux
    // HMODULE moduleHandle = GetModuleHandle("reaper_ultraschall.dll");
    // if (moduleHandle != 0)
    //{
    //    CHAR        dllPath[_MAX_PATH] = {0};
    //    const DWORD charCount          = GetModuleFileName(moduleHandle, dllPath, _MAX_PATH);
    //    if (charCount > 0)
    //    {
    //        pluginDirectory = dllPath;
    //        if (pluginDirectory.empty() == false)
    //        {
    //            const size_t offset = pluginDirectory.rfind('\\');
    //            if (offset != std::string::npos)
    //            {
    //                pluginDirectory = pluginDirectory.substr(0, offset);
    //            }
    //            else
    //            {
    //                pluginDirectory.clear();
    //            }
    //        }
    //    }
    //}

    return pluginDirectory;
}

std::string FindUltraschallPluginPath()
{
    return FileManager::AppendPath(FindUltraschallPluginDirectory(), "reaper_ultraschall");
}

std::string FindSWSPluginPath()
{
    std::string swsPluginPath;

    const std::string swsPlugin2_8UserPath = Platform::ProgramFilesDirectory() + "\\REAPER (x64)\\Plugins\\reaper_sws64.dll";
    if (Platform::FileExists(swsPlugin2_8UserPath) == true)
    {
        swsPluginPath = swsPlugin2_8UserPath;
    }
    else
    {
        swsPluginPath = FileManager::AppendPath(FindUltraschallPluginDirectory(), "reaper_sws64.dll");
    }

    return swsPluginPath;
}
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32

bool SWSVersionCheck()
{
    bool result = false;

#ifdef ULTRASCHALL_PLATFORM_WIN32
    const std::string swsPlugin2_8UserPath = FindSWSPluginPath();
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
    const std::string swsPlugin2_8UserPath = FileManager::UserApplicationSupportDirectory() + "/REAPER/UserPlugins/reaper_sws_extension.dylib";
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32

    if (FileManager::FileExists(swsPlugin2_8UserPath) == true)
    {
        ByteStream* pStream = ReadBinaryFile(swsPlugin2_8UserPath);
        if (pStream != 0)
        {
#ifdef ULTRASCHALL_PLATFORM_WIN32
            static const uint64_t originalCrc = 2821342186;
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
            static const uint64_t originalCrc = 3206585461;
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32
            const uint64_t crc = pStream->CRC32();
            if (originalCrc == crc)
            {
                result = true;
            }

            SafeRelease(pStream);
        }
    }

    return result;
}

}} // namespace ultraschall::reaper
