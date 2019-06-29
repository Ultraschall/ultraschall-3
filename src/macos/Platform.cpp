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

#ifdef min
#undef min
#endif // #ifdef min
#ifdef max
#undef max
#endif // #ifdef max

#import <AppKit/AppKit.h>
#import <Foundation/Foundation.h>

#include "Platform.h"
#include "FileManager.h"
#include "StringUtilities.h"

namespace ultraschall
{
namespace reaper
{

const UnicodeString Platform::THEME_PATH = "/REAPER/ColorThemes/Ultraschall_3.1.ReaperThemeZip";
const UnicodeString Platform::SOUNDBOARD_PATH("/Audio/Plug-Ins/Components/Soundboard.component");
const UnicodeString Platform::SWS_PATH("/REAPER/UserPlugins/reaper_sws64.dylib");
const UnicodeString Platform::PLUGIN_PATH("/REAPER/UserPlugins/reaper_ultraschall.dylib");
const UnicodeString Platform::STUDIO_LINK_PATH("/Audio/Plug-Ins/Components/StudioLink.component");
const UnicodeString Platform::STUDIO_LINK_ONAIR_PATH("/Audio/Plug-Ins/Components/StudioLinkOnAir.component");

UnicodeString Platform::UserDataDirectory()
{
    UnicodeString directory;

    NSString* userHomeDirectory = NSHomeDirectory();
    directory                   = [userHomeDirectory UTF8String];

    return directory;
}

UnicodeString Platform::ProgramFilesDirectory()
{
    UnicodeString directory;

    NSURL* applicationSupportDirectory =
        [[[NSFileManager defaultManager] URLsForDirectory:NSApplicationSupportDirectory inDomains:NSSystemDomainMask] firstObject];
    directory = [applicationSupportDirectory fileSystemRepresentation];

    return directory;
}

UnicodeChar Platform::PathSeparator()
{
    return '/';
}

bool Platform::FileExists(const UnicodeString& path)
{
    PRECONDITION_RETURN(path.empty() == false, false);

    bool fileExists = false;

    NSFileManager* fileManager = [NSFileManager defaultManager];
    fileExists                 = [fileManager fileExistsAtPath:[NSString stringWithUTF8String:path.c_str()]] == YES;

    return fileExists;
}

UnicodeString Platform::AppendPath(const UnicodeString& prefix, const UnicodeString& appendix)
{
    return prefix + PathSeparator() + appendix;
}

UnicodeString Platform::ReadFileVersion(const UnicodeString& path)
{
    PRECONDITION_RETURN(path.empty() == false, UnicodeString());

    UnicodeString version;

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

UnicodeString FindUltraschallPluginDirectory()
{
    UnicodeString pluginDirectory;

    // TODO

    return pluginDirectory;
}

bool Platform::SWSVersionCheck()

{
    bool result = false;

    UnicodeString swsPlugin2_8UserPath = Platform::ProgramFilesDirectory() + SWS_PATH;
    if(Platform::FileExists(swsPlugin2_8UserPath) == false)
    {
        swsPlugin2_8UserPath = Platform::AppendPath(FindUltraschallPluginDirectory(), "reaper_sws64.dylib");
    }

    if(Platform::FileExists(swsPlugin2_8UserPath) == true)
    {
        reaper::BinaryStream *pStream = FileManager::ReadBinaryFile(swsPlugin2_8UserPath);
        if(pStream != 0)

        {
            static const uint64_t originalCrc = 355942019;  // SWS 2.10.0.1 from 02/2019
            const uint64_t        crc         = pStream->CRC32();
            if(originalCrc == crc)

            {
                result = true;
            }

            SafeRelease(pStream);
        }
    }

    return result;
}

} // namespace reaper
} // namespace ultraschall

