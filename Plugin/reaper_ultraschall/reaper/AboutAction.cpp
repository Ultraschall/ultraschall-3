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
#include <vector>
#include <fstream>

#include "AboutAction.h"
#include "CustomActionFactory.h"
#include "ReaperVersionCheck.h"
#include "ThemeVersionCheck.h"
#include "VersionHandler.h"
#include "NotificationWindow.h"
#include "FileManager.h"

namespace ultraschall
{
namespace reaper
{

static DeclareCustomAction<AboutAction> action;

ServiceStatus AboutAction::Execute()
{
   const std::string pluginVersion = VersionHandler::PluginVersion();

   std::string message1 = "\
ULTRASCHALL Podcasting Extension for REAPER\r\n\r\n\
Copyright (c) 2017 ultraschall.fm\r\n\r\n\
Ultraschall REAPER Extension " +
                          pluginVersion + "\r\n";

   const std::string themeVersion = QueryThemeVersion();
   if (themeVersion.empty() == false)
   {
      message1 += "Ultraschall REAPER Theme " + themeVersion + "\r\n";
   }

#ifdef ULTRASCHALL_PLATFORM_MACOS
   const std::string hubVersion = VersionHandler::HubVersion();
   if (hubVersion.empty() == false)
   {
      message1 += hubVersion + "\r\n";
   }
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS

   const std::string soundboardVersion = VersionHandler::SoundboardVersion();
   if (soundboardVersion.empty() == false)
   {
      message1 += "Ultraschall Soundboard " + soundboardVersion + "\r\n";
   }

   const std::string studioLinkVersion = VersionHandler::StudioLinkVersion();
   if (studioLinkVersion.empty() == false)
   {
      message1 += "StudioLink Plug-in " + studioLinkVersion + "\r\n";
   }

   const std::string studioLinkOnAirVersion = VersionHandler::StudioLinkOnAirVersion();
   if (studioLinkOnAirVersion.empty() == false)
   {
      message1 += "StudioLink OnAir Plug-in " + studioLinkOnAirVersion + "\r\n";
   }

   const std::string lameVersion = VersionHandler::LAMEVersion();
   if (lameVersion.empty() == false)
   {
      message1 += "LAME MP3 Encoder " + lameVersion + "\r\n";
   }

   std::string message2 = "\
SWS REAPER Extension " + VersionHandler::SWSVersion() +
                          "\r\n\
REAPER ";

   message2 += QueryRawReaperVersion();
   message2 += "\r\n";

   NotificationWindow::Show("About Ultraschall 3.0.2 \"Miedinger\"...", message1 + message2);

   return SERVICE_SUCCESS;
}
}
}
