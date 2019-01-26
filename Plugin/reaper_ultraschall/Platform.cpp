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

#ifdef _WIN32
#include <shlobj.h>
#include <windows.h>
#else // #ifdef _WIN32
#ifdef _APPLE_
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#else  // #ifdef _APPLE_
// TODO linux
#endif // #ifdef _APPLE_
#endif // #ifdef _WIN32

#include "Platform.h"
#include "StringUtilities.h"

#include "wx/filename.h"

namespace ultraschall { namespace reaper {

#ifdef _WIN32

const std::string Platform::THEME_PATH("\\REAPER\\ColorThemes\\Ultraschall_3.1.ReaperThemeZip");
const std::string Platform::SOUNDBOARD_PATH("\\Steinberg\\VstPlugins\\Soundboard64.dll");
const std::string Platform::SWS_PATH("\\REAPER\\UserPlugins\\reaper_sws64.dll");
const std::string Platform::PLUGIN_PATH("\\REAPER\\UserPlugins\\reaper_ultraschall.dll");
const std::string Platform::STUDIO_LINK_PATH("\\Steinberg\\VstPlugins\\studio-link.dll");
const std::string Platform::STUDIO_LINK_ONAIR_PATH("\\Steinberg\\VstPlugins\\studio-link-onair.dll");

std::string Platform::ProgramFilesDirectory()
{
    std::string directory;

    PWSTR   unicodeString = nullptr;
    const HRESULT hr            = SHGetKnownFolderPath(FOLDERID_ProgramFilesX64, 0, nullptr, &unicodeString);
    if (SUCCEEDED(hr))
    {
        directory = MakeUTF8String(unicodeString);
        CoTaskMemFree(unicodeString);
    }

    return directory;
}

std::string Platform::UserDataDirectory()
{
    std::string directory;

    PWSTR   unicodeString = nullptr;
    const HRESULT hr            = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &unicodeString);
    if (SUCCEEDED(hr))
    {
        directory = MakeUTF8String(unicodeString);
        CoTaskMemFree(unicodeString);
        unicodeString = nullptr;
    }

    return directory;
}

char Platform::PathSeparator()
{
    return wxFileName::GetPathSeparator();
}

bool Platform::FileExists(const std::string& path)
{
    PRECONDITION_RETURN(path.empty() == false, false);

    bool fileExists = false;

    std::string str        = path;
    HANDLE      fileHandle = CreateFile(str.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (INVALID_HANDLE_VALUE != fileHandle)
    {
        fileExists = true;
        CloseHandle(fileHandle);
    }

    return fileExists;
}

std::string Platform::ReadFileVersion(const std::string& path)
{
    PRECONDITION_RETURN(path.empty() == false, std::string());

    std::string version;

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

            SafeDelete(fileVersionInfo);
        }
    }

    return version;
}

#else // #ifdef _WIN32

#ifdef _APPLE_

const std::string Platform::THEME_PATH("/REAPER/ColorThemes/Ultraschall_3.1.ReaperThemeZip");
const std::string Platform::SOUNDBOARD_PATH("/Audio/Plug-Ins/Components/Soundboard.component");
const std::string Platform::SWS_PATH("<unspecified>");
const std::string Platform::PLUGIN_PATH("<unspecified>");
const std::string Platform::STUDIO_LINK_PATH("/Audio/Plug-Ins/Components/StudioLink.component");
const std::string Platform::STUDIO_LINK_ONAIR_PATH("/Audio/Plug-Ins/Components/StudioLinkOnAir.component");

std::string Platform::UserDataDirectory()
{
    std::string directory;

    NSString* userHomeDirectory = NSHomeDirectory();
    directory                   = [userHomeDirectory UTF8String];

    return directory;
}

#if 0
std::string FileManager::UserApplicationSupportDirectory()
{
    std::string directory;

    NSURL* applicationSupportDirectory =
        [[[NSFileManager defaultManager] URLsForDirectory:NSApplicationSupportDirectory inDomains:NSUserDomainMask] firstObject];
    directory = [applicationSupportDirectory fileSystemRepresentation];

    return directory;
}
#endif

std::string Platform::ProgramFilesDirectory()
{
    std::string directory;

    NSURL* applicationSupportDirectory =
        [[[NSFileManager defaultManager] URLsForDirectory:NSApplicationSupportDirectory inDomains:NSSystemDomainMask] firstObject];
    directory = [applicationSupportDirectory fileSystemRepresentation];

    return directory;
}

bool FileExists(const std::string& path)
{
    PRECONDITION_RETURN(path.empty == false, false);

    bool fileExists = false;

    NSFileManager* fileManager = [NSFileManager defaultManager];
    fileExists                 = [fileManager fileExistsAtPath:[NSString stringWithUTF8String:path.c_str()]] == YES;
}

std::string Platform::ReadFileVersion(const std::string& path)
{
    PRECONDITION_RETURN(path.empty() == false, std::string());

    std::string version;

    NSURL*           libraryDirectory = [[[NSFileManager defaultManager] URLsForDirectory:NSLibraryDirectory inDomains:NSUserDomainMask] firstObject];
    NSMutableString* filePath         = [NSMutableString stringWithUTF8String:[libraryDirectory fileSystemRepresentation]];
    [filePath appendString:[NSString stringWithUTF8String:path.c_str()]];
    [filePath appendString:@"/Contents/Info.plist"];
    if ([[NSFileManager defaultManager] fileExistsAtPath:filePath])
    {
        NSDictionary* plist = [[NSDictionary alloc] initWithContentsOfFile:filePath];
        NSString*     value = [plist objectForKey:@"CFBundleShortVersionString"];
        version             = [value UTF8String];
    }

    return version;
}

#else // #ifdef _APPLE_

#endif // #ifdef _APPLE_

#endif // #ifdef _WIN32

}} // namespace ultraschall::reaper
