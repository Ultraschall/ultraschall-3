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

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

#include "Platform.h"
#include "StringUtilities.h"

#include "wx/filename.h"

namespace ultraschall { namespace reaper {

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

}} // namespace ultraschall::reaper
