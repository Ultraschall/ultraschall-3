////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2014-2015 Ultraschall (http://ultraschall.fm)
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

#ifndef WIN32
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#endif // #ifndef WIN32

#include "HubVersionCheck.h"
#include "FileManager.h"

namespace ultraschall { namespace reaper {
   
std::string QueryHubVersion()
{
   std::string version;
   
#ifndef WIN32
   if(FileManager::FileExists("/Library/Audio/Plug-Ins/HAL/AudioHub.driver/Contents/Info.plist") == true)
   {
      version = "AudioHub ";
      
      NSString* filePath = @"/Library/Audio/Plug-Ins/HAL/AudioHub.driver/Contents/Info.plist";
      NSDictionary* plist = [[NSDictionary alloc] initWithContentsOfFile: filePath];

      NSString* value = [plist objectForKey: @"CFBundleShortVersionString"];
      version += [value UTF8String];
      
      value = [plist objectForKey: @"CFBundleVersion"];
      version += ".";
      version += [value UTF8String];
   }
   else if(FileManager::FileExists("/Library/Audio/Plug-Ins/HAL/UltraschallHub.driver/Contents/Info.plist") == true)
   {
      version = "UltraschallHub ";

      NSString* filePath = @"/Library/Audio/Plug-Ins/HAL/UltraschallHub.driver/Contents/Info.plist";
      NSDictionary* plist = [[NSDictionary alloc] initWithContentsOfFile: filePath];
      
      NSString* value = [plist objectForKey: @"CFBundleShortVersionString"];
      version += [value UTF8String];
      
      value = [plist objectForKey: @"CFBundleVersion"];
      version += ".";
      version += [value UTF8String];
   }
#endif // #ifndef WIN32   

   return version;
}
   
}}
