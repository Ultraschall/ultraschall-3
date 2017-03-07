////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 Ultraschall (http://ultraschall.fm)
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

#include <sstream>

#include <Framework.h>

#include "SystemProperties.h"
#include "ReaperEntryPoints.h"
#include "NotificationWindow.h"

namespace ultraschall
{
namespace reaper
{

static const char *VERSIONS_SECTION_NAME = "ultraschall_versions";
static const char *THEME_VERSION_KEY_NAME = "theme";
static const char *PLUGIN_VERSION_KEY_NAME = "plugin";
static const char *VERSION_VALUE_NAME = "20170306";

bool QuerySetPluginVersion()
{
   bool result = false;

   if (reaper_api::HasExtState(VERSIONS_SECTION_NAME, THEME_VERSION_KEY_NAME) == true)
   {
      const std::string themeVersion = reaper_api::GetExtState(VERSIONS_SECTION_NAME, THEME_VERSION_KEY_NAME);
      if (themeVersion == VERSION_VALUE_NAME)
      {
         reaper_api::SetExtState(VERSIONS_SECTION_NAME, PLUGIN_VERSION_KEY_NAME, VERSION_VALUE_NAME, true);
         // quick sanity check
         result = reaper_api::HasExtState(VERSIONS_SECTION_NAME, PLUGIN_VERSION_KEY_NAME);
      }
      else
      {
         std::ostringstream str;
         str << "There is a configuration mismatch between the ULTRASCHALL THEME ("
             << themeVersion
             << ") and PLUGIN ("
             << VERSION_VALUE_NAME
             << ").\n\nULTRASCHALL will NOT work properly until you fix this. \n\nPlease proceed by installing the new theme or check the installation guide on http://ultraschall.fm/install/";
         NotificationWindow::Show(str.str());

         result = false;
      }
   }
   else
   {
      const std::string str = "The ULTRASCHALL THEME is missing.\n\nULTRASCHALL wil NOT work properly until you fix this.\n\nPlease proceed by installing the theme or check the installation guide on http://ultraschall.fm/install/";
      NotificationWindow::Show(str);

      result = false;
   }

   return result;
}

static const char *GLOBAL_SECTION_NAME = "ultraschall";

bool HasSystemProperty(const std::string &key)
{
   PRECONDITION_RETURN(key.empty() == false, false);

   return reaper_api::HasExtState(GLOBAL_SECTION_NAME, key.c_str());
}

void SetSystemProperty(const std::string &key, const std::string &value, const bool save)
{
   PRECONDITION(key.empty() == false);
   PRECONDITION(value.empty() == false);

   reaper_api::SetExtState(GLOBAL_SECTION_NAME, key.c_str(), value.c_str(), save);
}

std::string GetSystemProperty(const std::string &key)
{
   PRECONDITION_RETURN(key.empty() == false, std::string());

   return reaper_api::GetExtState(GLOBAL_SECTION_NAME, key.c_str());
}

void DeleteSystemProperty(const std::string &key, const bool save)
{
   PRECONDITION(key.empty() == false);

   reaper_api::DeleteExtState(GLOBAL_SECTION_NAME, key.c_str(), save);
}
}
}
