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

#include <codecvt>
#include <fstream>
#include <sstream>
#include <string>

#include "Application.h"
#include "FileManager.h"
#include "Framework.h"
#include "ReaperEntryPoints.h"
#include "StringUtilities.h"

#include "wx/wx.h"
#include "wx/filename.h"

#ifdef ULTRASCHALL_PLATFORM_WIN32
#include <shlobj.h>
#include <windows.h>
#else // #ifdef ULTRASCHALL_PLATFORM_WIN32
#import <AppKit/AppKit.h>
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32

namespace framework = ultraschall::framework;

namespace ultraschall { namespace reaper {

char FileManager::GetPathSeparator()
{
    return wxFileName::GetPathSeparator();
}

std::string FileManager::AppendPath(const std::string& prefix, const std::string& append)
{
    return prefix + GetPathSeparator() + append;
}

std::string FileManager::StripPath(const std::string& path)
{
    std::string shortName;

    if (path.empty() == false)
    {
        shortName = path;

        const std::string::size_type offset = path.rfind(FileManager::GetPathSeparator());
        if (offset != std::string::npos)
        {
            shortName = path.substr(offset + 1, path.size()); // skip separator
        }
    }

    return shortName;
}

std::vector<std::string> FileManager::SplitPath(const std::string& path)
{
    return framework::StringTokenize(path, GetPathSeparator());
}

#ifdef ULTRASCHALL_PLATFORM_WIN32
std::string FileManager::ProgramFilesDirectory()
{
    std::string directory;

    PWSTR   unicodeString = 0;
    HRESULT hr            = SHGetKnownFolderPath(FOLDERID_ProgramFilesX64, 0, 0, &unicodeString);
    if (SUCCEEDED(hr))
    {
        directory = framework::MakeUTF8String(unicodeString);
        CoTaskMemFree(unicodeString);
    }

    return directory;
}

std::string FileManager::RoamingAppDataDirectory()
{
    std::string directory;

    PWSTR   unicodeString = 0;
    HRESULT hr            = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, 0, &unicodeString);
    if (SUCCEEDED(hr))
    {
        directory = framework::MakeUTF8String(unicodeString);
        CoTaskMemFree(unicodeString);
        unicodeString = 0;
    }

    return directory;
}
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
std::string FileManager::UserHomeDirectory()
{
    std::string directory;

    NSString* userHomeDirectory = NSHomeDirectory();
    directory = [userHomeDirectory UTF8String];

    return directory;
}

std::string FileManager::UserApplicationSupportDirectory()
{
    std::string directory;

    NSURL* applicationSupportDirectory =
        [[[NSFileManager defaultManager] URLsForDirectory:NSApplicationSupportDirectory inDomains:NSUserDomainMask] firstObject];
    directory = [applicationSupportDirectory fileSystemRepresentation];

    return directory;
}

std::string FileManager::SystemApplicationSupportDirectory()
{
    std::string directory;

    NSURL* applicationSupportDirectory =
        [[[NSFileManager defaultManager] URLsForDirectory:NSApplicationSupportDirectory inDomains:NSSystemDomainMask] firstObject];
    directory = [applicationSupportDirectory fileSystemRepresentation];

    return directory;
}
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32

bool FileManager::FileExists(const std::string& path)
{
    bool fileExists = false;

#ifdef ULTRASCHALL_PLATFORM_WIN32
    std::string str        = path;
    HANDLE      fileHandle = CreateFile(str.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if (INVALID_HANDLE_VALUE != fileHandle)
    {
        fileExists = true;
        CloseHandle(fileHandle);
    }
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
    NSFileManager* fileManager = [NSFileManager defaultManager];
    fileExists = [fileManager fileExistsAtPath:[NSString stringWithUTF8String:path.c_str()]] == YES;
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32

    return fileExists;
}

size_t FileManager::FileExists(const std::vector<std::string>& paths)
{
    size_t offset = static_cast<size_t>(-1);

    for (size_t i = 0; (i < paths.size()) && (offset == -1); i++)
    {
        if (FileExists(paths[i]) == true)
        {
            offset = i;
        }
    }

    return offset;
}

std::vector<std::string> FileManager::ReadFile(const std::string& filename)
{
    std::vector<std::string> lines;

    std::ifstream input(filename);

    std::string line;
    while (std::getline(input, line))
    {
        lines.push_back(line);
    }

    input.close();

    return lines;
}

#ifdef ULTRASCHALL_PLATFORM_WIN32
std::string FileManager::ReadVersionFromFile(const std::string& path)
{
    std::string version;

    if (path.empty() == false)
    {
        DWORD       fileVersionInfoHandle = 0;
        const DWORD fileVersionInfoSize   = GetFileVersionInfoSize(path.c_str(), &fileVersionInfoHandle);
        if (fileVersionInfoSize > 0)
        {
            uint8_t* fileVersionInfo = new uint8_t[fileVersionInfoSize];
            if (fileVersionInfo != 0)
            {
                if (GetFileVersionInfo(path.c_str(), fileVersionInfoHandle, fileVersionInfoSize, fileVersionInfo))
                {
                    uint8_t* versionDataPtr  = 0;
                    uint32_t versionDataSize = 0;
                    if (VerQueryValue(fileVersionInfo, "\\", (void**)&versionDataPtr, &versionDataSize))
                    {
                        if (versionDataSize > 0)
                        {
                            const VS_FIXEDFILEINFO* fileInfo = reinterpret_cast<VS_FIXEDFILEINFO*>(versionDataPtr);
                            if (fileInfo->dwSignature == 0xfeef04bd)
                            {
                                std::stringstream str;
                                str << ((fileInfo->dwFileVersionMS >> 16) & 0xffff) << ".";
                                str << ((fileInfo->dwFileVersionMS >> 0) & 0xffff) << ".";
                                str << ((fileInfo->dwFileVersionLS >> 16) & 0xffff) << ".";
                                str << ((fileInfo->dwFileVersionLS >> 0) & 0xffff);
                                version = str.str();
                            }
                        }
                    }
                }

                framework::SafeDelete(fileVersionInfo);
            }
        }
    }

    return version;
}
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32
}}     // namespace ultraschall::reaper
