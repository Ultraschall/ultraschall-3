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

#include "VersionHandler.h"
#include "FileManager.h"
#include "Platform.h"
#include "StringUtilities.h"
#include "ReaperGateway.h"

#include <unzip.h>
#include <zlib.h>
#include <cstring>

namespace ultraschall { namespace reaper {

UnicodeString VersionHandler::ThemeVersion()
{
    UnicodeString       versionString;
    const UnicodeString themeControlFile = Platform::UserDataDirectory() + Platform::THEME_PATH;
    unzFile             themeFile        = unzOpen(U2H(themeControlFile).c_str());
    if(themeFile != nullptr)
    {
        bool decoded  = false;
        int  zipError = unzGoToFirstFile(themeFile);
        while((UNZ_OK == zipError) && (false == decoded))
        {
            unz_file_info fileInfo               = {0};
            const size_t  fileNameSize           = 4096;
            char          fileName[fileNameSize] = {0};
            zipError = unzGetCurrentFileInfo(themeFile, &fileInfo, fileName, fileNameSize, nullptr, 0, nullptr, 0);
            if(UNZ_OK == zipError)
            {
                if(strcmp("Ultraschall_2/version.txt", fileName) == 0)
                {
                    zipError = unzOpenCurrentFile(themeFile);
                    if(UNZ_OK == zipError)
                    {
                        const size_t fileBufferSize = fileInfo.uncompressed_size;
                        if(fileBufferSize > 0)
                        {
                            char* fileBuffer = new char[fileBufferSize + 1];
                            if(fileBuffer != nullptr)
                            {
                                memset(fileBuffer, 0, fileBufferSize + 1);
                                const int readResult
                                    = unzReadCurrentFile(themeFile, fileBuffer, (unsigned int)fileBufferSize);
                                if(readResult > 0)
                                {
                                    versionString = H2U(fileBuffer);
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

    UnicodeString themeVersion;
    if(versionString.empty() == false)
    {
        const UnicodeStringArray versionTokens = UnicodeStringTokenize(versionString, ':');
        if(versionTokens.size() == 2)
        {
            UnicodeString version = versionTokens[1];
            if(version.empty() == false)
            {
                themeVersion = UnicodeStringTrim(version);
            }
        }
    }

    return themeVersion;
}

UnicodeString VersionHandler::PluginVersion()
{
#ifdef _WIN32
    return Platform::ReadFileVersion(Platform::UserDataDirectory() + Platform::PLUGIN_PATH);
#else  // #ifdef _WIN32
    return "3.2.0";
// TODO: linux
#endif // #ifdef _WIN32
}

UnicodeString VersionHandler::ReaperVersion()
{
    UnicodeString version;

    const UnicodeStringArray tokens                  = UnicodeStringTokenize(ReaperGateway::ApplicationVersion(), '/');
    const size_t             MIN_VERSION_TOKEN_COUNT = 1;
    if(tokens.size() >= MIN_VERSION_TOKEN_COUNT)
    {
        version = tokens.at(0);
    }

    return version;
}

UnicodeString VersionHandler::SoundboardVersion()
{
    return Platform::ReadFileVersion(Platform::ProgramFilesDirectory() + Platform::SOUNDBOARD_PATH);
}

UnicodeString VersionHandler::StudioLinkVersion()
{
    return Platform::ReadFileVersion(Platform::ProgramFilesDirectory() + Platform::STUDIO_LINK_PATH);
}

UnicodeString VersionHandler::StudioLinkOnAirVersion()
{
    return Platform::ReadFileVersion(Platform::ProgramFilesDirectory() + Platform::STUDIO_LINK_ONAIR_PATH);
}

UnicodeString VersionHandler::SWSVersion()
{
#ifdef _WIN32
    return Platform::ReadFileVersion(Platform::UserDataDirectory() + Platform::SWS_PATH);
#else // #ifdef _WIN32
    return "2.9.7";
#endif // #ifdef _WIN32
}

bool VersionHandler::ReaperVersionCheck()
{
    bool result = false;

    UnicodeString versionString = VersionHandler::ReaperVersion();
    if(versionString.empty() == false)
    {
        UnicodeStringArray tokens = UnicodeStringTokenize(versionString, '.');
        if(tokens.size() >= 2)
        {
            const int REQUIRED_REAPER_MAJOR_VERSION = 5;
            const int REQUIRED_REAPER_MINOR_VERSION = 70;
            const int majorVersion                  = UnicodeStringToInt(tokens[0]);
            const int minorVersion                  = UnicodeStringToInt(tokens[1]);

            if((REQUIRED_REAPER_MAJOR_VERSION == majorVersion) && (REQUIRED_REAPER_MINOR_VERSION <= minorVersion))
            {
                result = true;
            }
        }
    }

    return result;
}

bool VersionHandler::SWSVersionCheck()
{
    return Platform::SWSVersionCheck();
}

}} // namespace ultraschall::reaper
