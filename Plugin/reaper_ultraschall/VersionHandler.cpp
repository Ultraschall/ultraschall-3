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

#include "VersionHandler.h"
#include "FileManager.h"
#include "Platform.h"
#include "ReaperEntryPoints.h"
#include "SWSVersionCheck.h"
#include "StringUtilities.h"

#include <unzip.h>
#include <zlib.h>

namespace ultraschall { namespace reaper {

std::string VersionHandler::ThemeVersion()
{
    std::string       versionString;
    const std::string themeControlFile = Platform::UserDataDirectory() + Platform::THEME_PATH;
    unzFile           themeFile        = unzOpen(themeControlFile.c_str());
    if (themeFile != nullptr)
    {
        bool decoded  = false;
        int  zipError = unzGoToFirstFile(themeFile);
        while ((UNZ_OK == zipError) && (false == decoded))
        {
            unz_file_info fileInfo               = {0};
            const size_t  fileNameSize           = 4096;
            char          fileName[fileNameSize] = {0};
            zipError                             = unzGetCurrentFileInfo(themeFile, &fileInfo, fileName, fileNameSize, nullptr, 0, nullptr, 0);
            if (UNZ_OK == zipError)
            {
                if (strcmp("Ultraschall_2/version.txt", fileName) == 0)
                {
                    zipError = unzOpenCurrentFile(themeFile);
                    if (UNZ_OK == zipError)
                    {
                        const size_t fileBufferSize = fileInfo.uncompressed_size;
                        if (fileBufferSize > 0)
                        {
                            char* fileBuffer = new char[fileBufferSize + 1]; 
                            if (fileBuffer != nullptr)
                            {
                                const int readResult = unzReadCurrentFile(themeFile, fileBuffer, unsigned int(fileBufferSize));
                                if (readResult > 0)
                                {
                                    versionString = fileBuffer;
                                    decoded       = true;
                                }

                                free(fileBuffer);
                                fileBuffer = 0;
                            }
                        }

                        unzCloseCurrentFile(themeFile);
                    }
                }
            }

            zipError = unzGoToNextFile(themeFile);
        }

        unzClose(themeFile);
        themeFile = 0;
    }

    std::string themeVersion;
    if (versionString.empty() == false)
    {
        const StringArray versionTokens = StringTokenize(versionString, ':');
        if (versionTokens.size() == 2)
        {
            std::string version = versionTokens[1];
            if (version.empty() == false)
            {
                themeVersion = StringTrim(version);
            }
        }
    }

    return themeVersion;
}

std::string VersionHandler::PluginVersion()
{
#ifdef _WIN32
    const std::string path = "\\REAPER\\UserPlugins\\reaper_ultraschall.dll";
    return Platform::ReadFileVersion(Platform::UserDataDirectory() + path);
#else // #ifdef _WIN32
#ifdef _APPLE_
    return "3.2.0";
#else  // #ifdef _APPLE_
// TODO: linux
#endif // #ifdef _APPLE_
#endif // #ifdef _WIN32
}

std::string VersionHandler::ReaperVersion()
{
    std::string version;

    const StringArray tokens                  = StringTokenize(reaper_api::GetAppVersion(), '/');
    const size_t      MIN_VERSION_TOKEN_COUNT = 1;
    if (tokens.size() >= MIN_VERSION_TOKEN_COUNT)
    {
        version = tokens.at(0);
    }

    return version;
}

std::string VersionHandler::SoundboardVersion()
{
#ifdef _WIN32
    const std::string path = "\\Steinberg\\VstPlugins\\Soundboard64.dll";
#else // #ifdef _WIN32
#ifdef _APPLE_
    const std::string path = "/Audio/Plug-Ins/Components/Soundboard.component";
#else  // #ifdef _APPLE_
// TODO: linux
#endif // #ifdef _APPLE_
#endif // #ifdef _WIN32
    return Platform::ReadFileVersion(Platform::ProgramFilesDirectory() + path);
}

std::string VersionHandler::StudioLinkVersion()
{
#ifdef _WIN32
    const std::string path = "\\Steinberg\\VstPlugins\\studio-link.dll";
#else // #ifdef _WIN32
#ifdef _APPLE_
    const std::string path = "/Audio/Plug-Ins/Components/StudioLink.component";
#else  // #ifdef _APPLE_
// TODO: linux
#endif // #ifdef _APPLE_
#endif // #ifdef _WIN32
    return Platform::ReadFileVersion(Platform::ProgramFilesDirectory() + path);
}

std::string VersionHandler::StudioLinkOnAirVersion()
{
#ifdef _WIN32
    const std::string path = "\\Steinberg\\VstPlugins\\studio-link-onair.dll";
#else // #ifdef _WIN32
#ifdef _APPLE_
    const std::string path = "/Audio/Plug-Ins/Components/StudioLinkOnAir.component";
#else  // #ifdef _APPLE_
// TODO: linux
#endif // #ifdef _APPLE_
#endif // #ifdef _WIN32
    return Platform::ReadFileVersion(Platform::ProgramFilesDirectory() + path);
}

std::string VersionHandler::SWSVersion()
{
#ifdef _WIN32
    const std::string path = "\\REAPER\\UserPlugins\\reaper_sws64.dll";
    return Platform::ReadFileVersion(Platform::UserDataDirectory() + path);
#else // #ifdef _WIN32
#ifdef _APPLE_
    return "2.9.7";
#else  // #ifdef _APPLE_
// TODO: linux
#endif // #ifdef _APPLE_
#endif // #ifdef _WIN32
}

}} // namespace ultraschall::reaper
