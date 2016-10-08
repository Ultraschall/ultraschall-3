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

#include <string>
#include <sstream>
#include <fstream>

#include <Framework.h>
#include <ResourceManager.h>
#include <StringUtilities.h>

#include "Application.h"
#include "FileManager.h"
#include "ReaperEntryPoints.h"

#ifndef ULTRASCHALL_PLATFORM_WIN32
#import <AppKit/AppKit.h>
#else
#include <windows.h>
#include <shlobj.h>
#endif // #ifndef ULTRASCHALL_PLATFORM_WIN32

namespace framework = ultraschall::framework;

namespace ultraschall { namespace reaper {

std::string FileManager::BrowseForFiles(const framework::ResourceId id)
{
    framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
    const std::string message = resourceManager.GetLocalizedString(id);
    return BrowseForFiles(message);
}

std::string FileManager::BrowseForFiles(const std::string& title)
{
    std::string path;

#ifdef ULTRASCHALL_PLATFORM_MACOS
    NSOpenPanel* fileDialog = [NSOpenPanel openPanel];
    if(nil != fileDialog)
    {
        fileDialog.canChooseFiles = YES;
        fileDialog.canChooseDirectories = NO;
        fileDialog.canCreateDirectories = NO;
        fileDialog.allowsMultipleSelection = NO;
        fileDialog.title = [NSString stringWithUTF8String : title.c_str()];

#if 0 // can't use recent APIs. REAPER builds with an OS version less than 10.6
        fileDialog.allowedFileTypes = [[NSArray alloc] initWithObjects:@"mp4chaps", @"txt", nil];
        fileDialog.allowsOtherFileTypes = NO;
        if([fileDialog runModal] == NSFileHandlingPanelOKButton)
#endif

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
            if([fileDialog runModalForTypes : [[NSArray alloc] initWithObjects:@"mp4chaps", @"txt", nil]] == NSFileHandlingPanelOKButton)
#pragma clang diagnostic pop
            {
                path = [[fileDialog URL] fileSystemRepresentation];
            }

        fileDialog = nil;
    }
#else
    IFileOpenDialog* pfod = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC, IID_PPV_ARGS(&pfod));
    if(SUCCEEDED(hr))
    {
        pfod->SetTitle(framework::MakeUtf16String(title).c_str());

        COMDLG_FILTERSPEC filters[3] = {0};
        filters[0].pszName = L"MP4 chapters";
        filters[0].pszSpec = L"*.chapters.txt";
        filters[1].pszName = L"MP4 chapters";
        filters[1].pszSpec = L"*.mp4chaps";
        filters[2].pszName = L"All files";
        filters[2].pszSpec = L"*.*";
        pfod->SetFileTypes(3, filters);

        FILEOPENDIALOGOPTIONS fos = FOS_STRICTFILETYPES | FOS_FILEMUSTEXIST;
        pfod->SetOptions(fos);

        hr = pfod->Show(reaper_api::GetMainHwnd());
        if(SUCCEEDED(hr))
        {
            IShellItem* psi = nullptr;
            hr = pfod->GetResult(&psi);
            if(SUCCEEDED(hr))
            {
                LPWSTR fileSystemPath = nullptr;
                hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &fileSystemPath);
                if(SUCCEEDED(hr) && (nullptr != fileSystemPath))
                {
                    path = framework::MakeUtf8String(fileSystemPath);
                    CoTaskMemFree(fileSystemPath);
                }

                framework::SafeRelease(psi);
            }

        }

        framework::SafeRelease(pfod);
    }
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS

    return path;
}

std::string FileManager::BrowseForFolder(const framework::ResourceId id, const std::string& folder)
{
    framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
    const std::string message = resourceManager.GetLocalizedString(id);
    return BrowseForFolder(message, folder);
}

std::string FileManager::BrowseForFolder(const std::string& title, const std::string& folder)
{
    std::string path;

#ifdef ULTRASCHALL_PLATFORM_MACOS   
    NSOpenPanel* fileDialog = [NSOpenPanel openPanel];
    if(nil != fileDialog)
    {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
        fileDialog.canCreateDirectories = YES;
        fileDialog.canChooseDirectories = YES;
        fileDialog.canChooseFiles = NO;
        fileDialog.allowsMultipleSelection = NO;
        fileDialog.prompt = @"Select";
            fileDialog.title = [NSString stringWithUTF8String : title.c_str()];

        NSString* initialPath = [NSString stringWithUTF8String : folder.c_str()];
        if([fileDialog runModalForDirectory : initialPath file : nil types : nil] == NSFileHandlingPanelOKButton)
#pragma clang diagnostic pop
        {
            path = [[fileDialog URL] fileSystemRepresentation];
        }

        fileDialog = nil;
}
#else
    IFileOpenDialog* pfod = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_INPROC, IID_PPV_ARGS(&pfod));
    if(SUCCEEDED(hr))
    {
        pfod->SetTitle(framework::MakeUtf16String(title).c_str());
        if(folder.empty() == false)
        {
            IShellItem* psi = nullptr;
            hr = SHCreateItemFromParsingName(framework::MakeUtf16String(folder).c_str(), nullptr, IID_PPV_ARGS(&psi));
            if(SUCCEEDED(hr))
            {
                pfod->SetFolder(psi);
                framework::SafeRelease(psi);
            }
        }

        if(SUCCEEDED(hr))
        {
            COMDLG_FILTERSPEC filters[2] = {0};
            filters[0].pszName = L"MP4 Chapters";
            filters[0].pszSpec = L"*.mp4chaps";
            filters[1].pszName = L"MP4 Chapters";
            filters[1].pszSpec = L"*.txt";
            pfod->SetFileTypes(2, filters);

            FILEOPENDIALOGOPTIONS fos = FOS_PICKFOLDERS | FOS_PATHMUSTEXIST;
            pfod->SetOptions(fos);

            hr = pfod->Show(reaper_api::GetMainHwnd());
            if(SUCCEEDED(hr))
            {
                IShellItem* psi = nullptr;
                hr = pfod->GetResult(&psi);
                if(SUCCEEDED(hr))
                {
                    LPWSTR fileSystemPath = nullptr;
                    hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &fileSystemPath);
                    if(SUCCEEDED(hr) && (nullptr != fileSystemPath))
                    {
                        path = framework::MakeUtf8String(fileSystemPath);
                        CoTaskMemFree(fileSystemPath);
                    }

                    framework::SafeRelease(psi);
                }

            }
        }

        framework::SafeRelease(pfod);
    }
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS

    return path;
}

std::string FileManager::AppendPath(const std::string& prefix, const std::string& append)
{
#ifdef ULTRASCHALL_PLATFORM_MACOS 
    return prefix + '/' + append;
#else
    return prefix + '\\' + append;
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS
}

#ifdef ULTRASCHALL_PLATFORM_MACOS
std::string FileManager::UserHomeDirectory()
{
    std::string directory;

    NSString* userHomeDirectory = NSHomeDirectory();
    directory = [userHomeDirectory UTF8String];
    
    return directory;
}
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS

#ifdef ULTRASCHALL_PLATFORM_MACOS
std::string FileManager::UserApplicationSupportDirectory()
{
    std::string directory;

    NSURL* applicationSupportDirectory = [[[NSFileManager defaultManager] URLsForDirectory:NSApplicationSupportDirectory
        inDomains : NSUserDomainMask] firstObject];
    directory = [applicationSupportDirectory fileSystemRepresentation];
    
    return directory;
}
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS

#ifdef ULTRASCHALL_PLATFORM_MACOS
std::string FileManager::SystemApplicationSupportDirectory()
{
    std::string directory;

    NSURL* applicationSupportDirectory = [[[NSFileManager defaultManager] URLsForDirectory:NSApplicationSupportDirectory
        inDomains : NSSystemDomainMask] firstObject];
    directory = [applicationSupportDirectory fileSystemRepresentation];
    
    return directory;
}
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS

#ifdef ULTRASCHALL_PLATFORM_WIN32
std::string FileManager::ProgramFilesDirectory()
{
    std::string directory;

    PWSTR unicodeString = 0;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_ProgramFilesX64, 0, 0, &unicodeString);
    if(SUCCEEDED(hr))
    {
        directory = framework::MakeUtf8String(unicodeString);
        CoTaskMemFree(unicodeString);
    }

    return directory;
    }
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32

#ifdef ULTRASCHALL_PLATFORM_WIN32
std::string FileManager::RoamingAppDataDirectory()
{
    std::string directory;

    PWSTR unicodeString = 0;
    HRESULT hr = SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, 0, &unicodeString);
    if(SUCCEEDED(hr))
    {
        directory = framework::MakeUtf8String(unicodeString);
        CoTaskMemFree(unicodeString);
		unicodeString = 0;
    }

    return directory;
    }
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32

bool FileManager::FileExists(const std::string& path)
{
    bool fileExists = false;

#ifdef ULTRASCHALL_PLATFORM_MACOS
    NSFileManager* fileManager = [NSFileManager defaultManager];
    fileExists = [fileManager fileExistsAtPath : [NSString stringWithUTF8String : path.c_str()]] == YES;
#else
    HANDLE fileHandle = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    if(INVALID_HANDLE_VALUE != fileHandle)
    {
        fileExists = true;
        CloseHandle(fileHandle);
    }
#endif // #ifndef ULTRASCHALL_PLATFORM_WIN32

    return fileExists;
}

std::vector<std::string> FileManager::ReadFile(const std::string& filename)
{
    std::vector<std::string> lines;

    std::ifstream input(filename);

    std::string line;
    while(std::getline(input, line))
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

    if(path.empty() == false)
    {
        DWORD fileVersionInfoHandle = 0;
        const DWORD fileVersionInfoSize = GetFileVersionInfoSize(path.c_str(), &fileVersionInfoHandle);
        if(fileVersionInfoSize > 0)
        {
            uint8_t* fileVersionInfo = new uint8_t[fileVersionInfoSize];
            if(fileVersionInfo != 0)
            {
                if(GetFileVersionInfo(path.c_str(), fileVersionInfoHandle, fileVersionInfoSize, fileVersionInfo))
                {
                    uint8_t* versionDataPtr = 0;
                    uint32_t versionDataSize = 0;
                    if(VerQueryValue(fileVersionInfo, "\\", (void**)&versionDataPtr, &versionDataSize))
                    {
                        if(versionDataSize > 0)
                        {
                            const VS_FIXEDFILEINFO* fileInfo = reinterpret_cast<VS_FIXEDFILEINFO*>(versionDataPtr);
                            if(fileInfo->dwSignature == 0xfeef04bd)
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
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32

}}


