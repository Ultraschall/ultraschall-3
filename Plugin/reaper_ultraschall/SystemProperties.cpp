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

#include "Framework.h"
#include "NotificationWindow.h"
#include "ReaperEntryPoints.h"
#include "ReaperVersionCheck.h"
#include "StringUtilities.h"
#include "SystemProperties.h"
#include "ThemeVersionCheck.h"
#include "VersionHandler.h"

namespace ultraschall { namespace reaper {

static const char* THEME_VERSION_KEY_NAME  = "theme";
static const char* PLUGIN_VERSION_KEY_NAME = "plugin";
static const char* VERSION_VALUE_NAME      = "20180114";

static const char* SAFETY_LEVEL_KEY_NAME                = "level";
static const char* STRICT_SAFETY_LEVEL_VALUE_NAME       = "strict";
static const char* RELAXED_SAFETY_LEVEL_VALUE_NAME      = "relaxed";
static const char* EXPERIMENTAL_SAFETY_LEVEL_VALUE_NAME = "experimental";

ULTRASCHALL_SAFETY_LEVEL SafetyLevel::Query()
{
    ULTRASCHALL_SAFETY_LEVEL safetyLevel = STRICT_SAFETY_LEVEL;

    if (SystemProperty<std::string>::Exists(SAFETY_SECTION_NAME, SAFETY_LEVEL_KEY_NAME) == true)
    {
        const std::string safetyModeValue = SystemProperty<std::string>::Get(SAFETY_SECTION_NAME, SAFETY_LEVEL_KEY_NAME);
        if (safetyModeValue == EXPERIMENTAL_SAFETY_LEVEL_VALUE_NAME)
        {
            safetyLevel = EXPERIMENTAL_SAFETY_LEVEL;
        }
        else if (safetyModeValue == RELAXED_SAFETY_LEVEL_VALUE_NAME)
        {
            safetyLevel = RELAXED_SAFETY_LEVEL;
        }
    }

    return safetyLevel;
}

static const char* SAFETY_MODE_KEY_NAME            = "mode";
static const char* BASIC_SAFETY_MODE_VALUE_NAME    = "basic";
static const char* ADVANCED_SAFETY_MODE_VALUE_NAME = "advanced";

ULTRASCHALL_SAFETY_MODE SafetyMode::Query()
{
    ULTRASCHALL_SAFETY_MODE safetyMode = BASIC_SAFETY_MODE;

    if (SystemProperty<std::string>::Exists(SAFETY_SECTION_NAME, SAFETY_MODE_KEY_NAME) == true)
    {
        const std::string safetyModeValue = SystemProperty<std::string>::Get(SAFETY_SECTION_NAME, SAFETY_MODE_KEY_NAME);
        if (safetyModeValue == BASIC_SAFETY_MODE_VALUE_NAME)
        {
            safetyMode = BASIC_SAFETY_MODE;
        }
        else if (safetyModeValue == ADVANCED_SAFETY_MODE_VALUE_NAME)
        {
            safetyMode = ADVANCED_SAFETY_MODE;
        }
    }

    return safetyMode;
}

bool QuerySetPluginVersion()
{
    bool result = false;

    if (SystemProperty<std::string>::Exists(VERSIONS_SECTION_NAME, THEME_VERSION_KEY_NAME) == true)
    {
        const std::string themeVersion = SystemProperty<std::string>::Get(VERSIONS_SECTION_NAME, THEME_VERSION_KEY_NAME);
        if (themeVersion == VERSION_VALUE_NAME)
        {
            SystemProperty<std::string>::Set(VERSIONS_SECTION_NAME, PLUGIN_VERSION_KEY_NAME, VERSION_VALUE_NAME, true);
            // quick sanity check
            result = SystemProperty<std::string>::Exists(VERSIONS_SECTION_NAME, PLUGIN_VERSION_KEY_NAME);
        }
        else
        {
            if (SafetyLevel::IsExperimental() == false)
            {
                std::ostringstream str;
                str << "There is a configuration mismatch between the ULTRASCHALL THEME (" << themeVersion << ") and PLUGIN (" << VERSION_VALUE_NAME
                    << ").\n\nULTRASCHALL will NOT work properly until you fix this. \n\nPlease proceed by installing the new theme or check the installation "
                       "guide on http://ultraschall.fm/install/";
                NotificationWindow::Show(str.str());

                result = false;
            }
            else
            {
                result = true;
            }
        }
    }
    else
    {
        if (SafetyLevel::IsExperimental() == false)
        {
            const std::string str = "The ULTRASCHALL THEME is missing.\n\nULTRASCHALL will NOT work properly until you fix this.\n\nPlease proceed by "
                                    "installing the theme or check the installation guide on http://ultraschall.fm/install/";
            NotificationWindow::Show(str);

            result = false;
        }
        else
        {
            result = true;
        }
    }

    return result;
}

template<> std::string SystemProperty<std::string>::Get(const std::string& section, const std::string& key)
{
    return RawValue(section, key);
}

template<> bool SystemProperty<bool>::Get(const std::string& section, const std::string& key)
{
    bool value = false;

    const std::string& rawValue = RawValue(section, key);
    if (rawValue.empty() == false)
    {
        if ((framework::StringLowercase(rawValue) == "true") || (framework::StringToInt(rawValue) != 0))
        {
            value = true;
        }
    }

    return value;
}

template<> int SystemProperty<int>::Get(const std::string& section, const std::string& key)
{
    int value = 0;

    const std::string rawValue = RawValue(section, key);
    if (rawValue.empty() == false)
    {
        value = framework::StringToInt(rawValue);
    }

    return value;
}

void UpdateBillOfMaterials()
{
    static const char* FOUND_ITEMS_KEY_NAME = "found_items";
    static const char* ITEM_KEY_NAME_PREFIX = "item_";

    if (SystemProperty<int>::Exists(BOM_SECTION_NAME, FOUND_ITEMS_KEY_NAME) == true)
    {
        const int foundItems = SystemProperty<int>::Get(BOM_SECTION_NAME, FOUND_ITEMS_KEY_NAME);
        if (foundItems > 0)
        {
            for (int i = 1; i <= foundItems; i++)
            {
                SystemProperty<std::string>::Delete(BOM_SECTION_NAME, ITEM_KEY_NAME_PREFIX + std::to_string(i), true);
            }
        }
        else
        {
            for (int i = 1; i <= 23; i++)
            {
                if (SystemProperty<std::string>::Exists(BOM_SECTION_NAME, ITEM_KEY_NAME_PREFIX + std::to_string(i)) == true)
                {
                    SystemProperty<std::string>::Delete(BOM_SECTION_NAME, ITEM_KEY_NAME_PREFIX + std::to_string(i), true);
                }
            }
        }

        SystemProperty<int>::Delete(BOM_SECTION_NAME, FOUND_ITEMS_KEY_NAME, true);
    }
    else
    {
        for (unsigned int i = 1; i <= 23; i++)
        {
            if (SystemProperty<std::string>::Exists(BOM_SECTION_NAME, ITEM_KEY_NAME_PREFIX + std::to_string(i)) == true)
            {
                SystemProperty<std::string>::Delete(BOM_SECTION_NAME, ITEM_KEY_NAME_PREFIX + std::to_string(i), true);
            }
        }
    }

    std::vector<std::string> bom;
    std::string              itemVersion = VersionHandler::PluginVersion();
    if (itemVersion.empty() == false)
    {
        bom.push_back("Ultraschall REAPER Extension " + itemVersion);
    }

    itemVersion = QueryThemeVersion();
    if (itemVersion.empty() == false)
    {
        bom.push_back("Ultraschall REAPER Theme " + itemVersion);
    }

#ifdef ULTRASCHALL_PLATFORM_WIN32
#else  // #ifdef ULTRASCHALL_PLATFORM_WIN32
    itemVersion = VersionHandler::HubVersion();
    if (itemVersion.empty() == false)
    {
        bom.push_back(itemVersion);
    }
#endif // #ifdef ULTRASCHALL_PLATFORM_WIN32

    itemVersion = VersionHandler::SoundboardVersion();
    if (itemVersion.empty() == false)
    {
        bom.push_back("Ultraschall Soundboard " + itemVersion);
    }

    itemVersion = VersionHandler::StudioLinkVersion();
    if (itemVersion.empty() == false)
    {
        bom.push_back("StudioLink Plug-in " + itemVersion);
    }

    itemVersion = VersionHandler::StudioLinkOnAirVersion();
    if (itemVersion.empty() == false)
    {
        bom.push_back("StudioLink OnAir Plug-in " + itemVersion);
    }

    itemVersion = VersionHandler::SWSVersion();
    if (itemVersion.empty() == false)
    {
        bom.push_back("SWS REAPER Extension " + itemVersion);
    }

    itemVersion = QueryRawReaperVersion();
    if (itemVersion.empty() == false)
    {
        bom.push_back("REAPER " + itemVersion);
    }

    if (bom.empty() == false)
    {
        SystemProperty<int>::Set(BOM_SECTION_NAME, FOUND_ITEMS_KEY_NAME, std::to_string(bom.size()), true);

        for (size_t i = 0; i < bom.size(); i++)
        {
            SystemProperty<std::string>::Set(BOM_SECTION_NAME, ITEM_KEY_NAME_PREFIX + std::to_string(i + 1), bom[i], true);
        }
    }
}

}} // namespace ultraschall::reaper
