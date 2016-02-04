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

#include <vector>
#include <fstream>
#include "ReaperVersionCheck.h"
#include "ThemeVersionCheck.h"
#include "HubVersionCheck.h"
#include "SoundboardVersionCheck.h"
#include "AboutAction.h"
#include "MessageBox.h"
#include "About.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<AboutAction> action;

const char* AboutAction::UniqueId()
{
   return "ULTRASCHALL_ABOUT_ULTRASCHALL";
}

const ServiceStatus AboutAction::Execute()
{
#if 1
   std::string message1 = "\
http://ultraschall.fm\r\n\r\n\
Copyright (c) 2016 Ralf Stockmann, Daniel Lindenfelser, Katrin Leinweber, Andreas Pieper, Tim Pritlove, Heiko Panjas\r\n\r\n\
Ultraschall REAPER Extension 2.1\r\n";

   const std::string themeVersion = QueryThemeVersion();
   if(themeVersion.empty() == false)
   {
      message1 += "Ultraschall REAPER Theme " + themeVersion + "\r\n";
   }

   const std::string hubVersion = QueryHubVersion();
   if(hubVersion.empty() == false)
   {
      message1 += hubVersion + "\r\n";
   }

   const std::string soundboardVersion = QuerySoundboardVersion();
   if(soundboardVersion.empty() == false)
   {
      message1 += "Ultraschall Soundboard " + soundboardVersion + "\r\n";
   }

   std::string message2 = "\
SWS REAPER Extension 2.8.3\r\n\
REAPER ";

   message2 += QueryReaperVersion();
   message2 += "\r\n";

   MessageBox::Show("Ultraschall 2.1 \"Gropius\"", message1 + message2);
#else
   ShowAbout();
#endif
   return SERVICE_SUCCESS;
}

}}
