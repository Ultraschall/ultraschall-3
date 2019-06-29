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

#include "Common.h"
#include "Platform.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

const UnicodeString Platform::THEME_PATH("/REAPER/ColorThemes/Ultraschall_3.1.ReaperThemeZip");
const UnicodeString Platform::SOUNDBOARD_PATH("/Audio/Plug-Ins/Components/Soundboard.component");
const UnicodeString Platform::SWS_PATH("/REAPER/UserPlugins/reaper_sws64.dylib");
const UnicodeString Platform::PLUGIN_PATH("/REAPER/UserPlugins/reaper_ultraschall.dylib");
const UnicodeString Platform::STUDIO_LINK_PATH("/Audio/Plug-Ins/Components/StudioLink.component");
const UnicodeString Platform::STUDIO_LINK_ONAIR_PATH("/Audio/Plug-Ins/Components/StudioLinkOnAir.component");

UnicodeString Platform::UserDataDirectory()
{
    return UnicodeString();
}

UnicodeString Platform::ProgramFilesDirectory()
{
    return UnicodeString();
}

UnicodeChar Platform::PathSeparator()
{
    return '/';
}

bool Platform::FileExists(const UnicodeString& path)
{
    return false;
}

UnicodeString Platform::AppendPath(const UnicodeString& prefix, const UnicodeString& appendix)
{
    return prefix + PathSeparator() + appendix;
}

UnicodeString Platform::ReadFileVersion(const UnicodeString& path)
{
    return UnicodeString();
}

UnicodeString FindUltraschallPluginDirectory()
{
    return UnicodeString();
}

bool Platform::SWSVersionCheck()

{
    return false;
}

}}
