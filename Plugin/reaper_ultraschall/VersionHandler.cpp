////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) ultraschall.fm (http://ultraschall.fm)
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
#include "SWSVersionCheck.h"

#ifdef ULTRASCHALL_PLATFORM_WIN32
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>
#endif // #ifdef                   ULTRASCHALL_PLATFORM_WIN32

namespace ultraschall
{
namespace reaper
{

#ifdef ULTRASCHALL_PLATFORM_WIN32
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
std::string VersionHandler::HubVersion()
{
    std::string version;

    if (FileManager::FileExists("/Library/Audio/Plug-Ins/HAL/AudioHub.driver/Contents/Info.plist") == true) {
        version = "AudioHub ";

        NSString*     filePath = @"/Library/Audio/Plug-Ins/HAL/AudioHub.driver/Contents/Info.plist";
        NSDictionary* plist    = [[NSDictionary alloc] initWithContentsOfFile:filePath];

        NSString* value = [plist objectForKey:@"CFBundleShortVersionString"];
        version += [value UTF8String];

        value = [plist objectForKey:@"CFBundleVersion"];
        version += ".";
        version += [value UTF8String];
    }
    else if (FileManager::FileExists("/Library/Audio/Plug-Ins/HAL/UltraschallHub.driver/Contents/Info.plist") == true) {
        version = "UltraschallHub ";

        NSString*     filePath = @"/Library/Audio/Plug-Ins/HAL/UltraschallHub.driver/Contents/Info.plist";
        NSDictionary* plist    = [[NSDictionary alloc] initWithContentsOfFile:filePath];

        NSString* value = [plist objectForKey:@"CFBundleShortVersionString"];
        version += [value UTF8String];

        value = [plist objectForKey:@"CFBundleVersion"];
        version += ".";
        version += [value UTF8String];
    }

    return version;
}
#endif // #ifdef                   ULTRASCHALL_PLATFORM_WIN32

std::string VersionHandler::PluginVersion()
{
#ifdef ULTRASCHALL_PLATFORM_WIN32
   std::string pluginVersion;

   const std::string path = FindUltraschallPluginPath();
   if(path.empty() == false)
   {
      pluginVersion = FileManager::ReadVersionFromFile(path);
   }

   return pluginVersion;
#else
   return "3.1.1";
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32
}

std::string VersionHandler::SoundboardVersion()
{
   std::string version;

#ifdef ULTRASCHALL_PLATFORM_WIN32
   const std::string path = FileManager::ProgramFilesDirectory() + "\\Steinberg\\VstPlugins\\Soundboard64.dll";
   version                = FileManager::ReadVersionFromFile(path);
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
   NSURL* libraryDirectory =
       [[[NSFileManager defaultManager] URLsForDirectory:NSLibraryDirectory inDomains:NSUserDomainMask] firstObject];
   NSMutableString* filePath = [NSMutableString stringWithUTF8String:[libraryDirectory fileSystemRepresentation]];
   [filePath appendString:@"/Audio/Plug-Ins/Components/Soundboard.component/Contents/Info.plist"];
   if ([[NSFileManager defaultManager] fileExistsAtPath:filePath]) {
       NSDictionary* plist = [[NSDictionary alloc] initWithContentsOfFile:filePath];
       NSString*     value = [plist objectForKey:@"CFBundleShortVersionString"];
       version             = [value UTF8String];
   }
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32

   return version;
}

std::string VersionHandler::StudioLinkVersion()
{
   std::string version;

#ifdef ULTRASCHALL_PLATFORM_WIN32
   const std::string path = FileManager::ProgramFilesDirectory() + "\\Steinberg\\VstPlugins\\studio-link.dll";
   version                = FileManager::ReadVersionFromFile(path);
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
   NSURL* libraryDirectory =
       [[[NSFileManager defaultManager] URLsForDirectory:NSLibraryDirectory inDomains:NSUserDomainMask] firstObject];
   NSMutableString* filePath = [NSMutableString stringWithUTF8String:[libraryDirectory fileSystemRepresentation]];
   [filePath appendString:@"/Audio/Plug-Ins/Components/StudioLink.component/Contents/Info.plist"];
   if ([[NSFileManager defaultManager] fileExistsAtPath:filePath]) {
       NSDictionary* plist = [[NSDictionary alloc] initWithContentsOfFile:filePath];
       NSString*     value = [plist objectForKey:@"CFBundleShortVersionString"];
       version             = [value UTF8String];
   }
#endif // #ifdef                   ULTRASCHALL_PLATFORM_WIN32

   return version;
}

std::string VersionHandler::StudioLinkOnAirVersion()
{
   std::string version;

#ifdef ULTRASCHALL_PLATFORM_WIN32
   const std::string path = FileManager::ProgramFilesDirectory() + "\\Steinberg\\VstPlugins\\studio-link-onair.dll";
   version                = FileManager::ReadVersionFromFile(path);
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
   NSURL* libraryDirectory =
       [[[NSFileManager defaultManager] URLsForDirectory:NSLibraryDirectory inDomains:NSUserDomainMask] firstObject];
   NSMutableString* filePath = [NSMutableString stringWithUTF8String:[libraryDirectory fileSystemRepresentation]];
   [filePath appendString:@"/Audio/Plug-Ins/Components/StudioLinkOnAir.component/Contents/Info.plist"];
   if ([[NSFileManager defaultManager] fileExistsAtPath:filePath]) {
       NSDictionary* plist = [[NSDictionary alloc] initWithContentsOfFile:filePath];
       NSString*     value = [plist objectForKey:@"CFBundleShortVersionString"];
       version             = [value UTF8String];
   }
#endif // #ifdef                   ULTRASCHALL_PLATFORM_WIN32

   return version;
}

std::string VersionHandler::SWSVersion()
{
#ifdef ULTRASCHALL_PLATFORM_WIN32
   const std::string path = FileManager::ProgramFilesDirectory() + "\\REAPER (x64)\\Plugins\\reaper_sws64.dll";
   return FileManager::ReadVersionFromFile(path);
#else
   return "2.9.7";
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32
}

}
}
