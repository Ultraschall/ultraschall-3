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

#include <fstream>

#include <Framework.h>
#include <ResourceManager.h>

#include "Application.h"
#include "FileManager.h"

#import <AppKit/AppKit.h>

namespace framework = ultraschall::framework;

namespace ultraschall { namespace reaper {

const std::string FileManager::BrowseForFiles(const framework::ResourceId id)
{
   framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
   const std::string message = resourceManager.GetLocalizedString(id);
   return BrowseForFiles(message);
}
   
const std::string FileManager::BrowseForFiles(const std::string& title)
{
   std::string path;

   NSOpenPanel* fileDialog = [NSOpenPanel openPanel];
   if(nil != fileDialog)
   {
      fileDialog.canChooseFiles = YES;
      fileDialog.canChooseDirectories = NO;
      fileDialog.canCreateDirectories = NO;
      fileDialog.allowsMultipleSelection = NO;
      fileDialog.title = [NSString stringWithUTF8String: title.c_str()];

#if 0 // can't use recent APIs. REAPER builds with an OS version less than 10.6
      fileDialog.allowedFileTypes = [[NSArray alloc] initWithObjects: @"mp4chaps", @"txt", nil];
      fileDialog.allowsOtherFileTypes = NO;
      if([fileDialog runModal] == NSFileHandlingPanelOKButton)
#endif
   
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
      if([fileDialog runModalForTypes:[[NSArray alloc] initWithObjects:@"mp4chaps", @"txt", nil]] == NSFileHandlingPanelOKButton)
#pragma clang diagnostic pop
      {
         path = [[fileDialog URL] fileSystemRepresentation];
      }
      
      fileDialog = nil;
   }
   
   return path;
}

const std::string FileManager::BrowseForFolder(const framework::ResourceId id, const std::string& folder)
{
   framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
   const std::string message = resourceManager.GetLocalizedString(id);
   return BrowseForFolder(message, folder);
}
   
const std::string FileManager::BrowseForFolder(const std::string& title, const std::string& folder)
{
   std::string path;
   
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
      fileDialog.title = [NSString stringWithUTF8String: title.c_str()];
      
      NSString* initialPath = [NSString stringWithUTF8String: folder.c_str()];
      if([fileDialog runModalForDirectory:initialPath file:nil types:nil] == NSFileHandlingPanelOKButton)
#pragma clang diagnostic pop
      {
         path = [[fileDialog URL] fileSystemRepresentation];
      }
      
      fileDialog = nil;
   }
   
   return path;
}
   
const std::string FileManager::AppendPath(const std::string& prefix, const std::string& append)
{
   return prefix + '/' + append;
}
 
const std::string FileManager::UserApplicationSupportDirectory()
{
   NSURL* applicationSupportDirectory = [[[NSFileManager defaultManager] URLsForDirectory:NSApplicationSupportDirectory
                                                                         inDomains:NSUserDomainMask] firstObject];
   const std::string directory = [applicationSupportDirectory fileSystemRepresentation];
   return directory;
}

const std::string FileManager::SystemApplicationSupportDirectory()
{
   NSURL* applicationSupportDirectory = [[[NSFileManager defaultManager] URLsForDirectory:NSApplicationSupportDirectory
                                                                                inDomains:NSSystemDomainMask] firstObject];
   const std::string directory = [applicationSupportDirectory fileSystemRepresentation];
   return directory;
}
   

const bool FileManager::FileExists(const std::string& path)
{
   NSFileManager* fileManager = [NSFileManager defaultManager];
   const bool fileExists = [fileManager fileExistsAtPath: [NSString stringWithUTF8String: path.c_str()]] == YES;
   return fileExists;
}
   
const std::vector<std::string> FileManager::ReadFile(const std::string& filename)
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

}}

