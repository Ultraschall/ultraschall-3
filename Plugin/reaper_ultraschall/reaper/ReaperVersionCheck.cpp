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
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>
#include "ReaperVersionCheck.h"
#include "FileManager.h"

namespace ultraschall { namespace reaper {

const std::string QueryReaperVersion()
{
   std::string version;
   
   if(ReaperPlatformCheck() == true)
   {
      NSString* filePath = @"/Applications/REAPER64.app/Contents/Info.plist";
      NSDictionary* plist = [[NSDictionary alloc] initWithContentsOfFile: filePath];
      NSString* value = [plist objectForKey: @"CFBundleVersion"];
      version = [value UTF8String];
   }
   
   return version;
}
   
const bool ReaperVersionCheck()
{
   bool result = false;
   
   std::string version = QueryReaperVersion();
   if((version.size() >= 3) && (version[0] == '5') && (version[1] == '.'))
   {
      const int minorVersion = atoi(&version[2]);
      if(minorVersion >= 1)
      {
         result = true;
      }
   }
   
   return result;
}
 
const bool ReaperPlatformCheck()
{
   return FileManager::FileExists("/Applications/REAPER64.app/Contents/Info.plist");
}

}}
