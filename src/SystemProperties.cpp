////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
//
// The MIT License (MIT)
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

#include "SystemProperties.h"
#include "StringUtilities.h"
#include "UIMessageSupervisor.h"
#include "VersionHandler.h"

namespace ultraschall
{
namespace reaper
{

static const char* THEME_VERSION_KEY_NAME  = "theme";
static const char* PLUGIN_VERSION_KEY_NAME = "plugin";
static const char* VERSION_VALUE_NAME      = "20180114";

template <>
UnicodeString SystemProperty<UnicodeString>::Get(const UnicodeString &section, const UnicodeString &key)
{
    return RawValue(section, key);
}

template <>
bool SystemProperty<bool>::Get(const UnicodeString &section, const UnicodeString &key)
{
    bool value = false;

    const UnicodeString &rawValue = RawValue(section, key);
    if (rawValue.empty() == false)
    {
        if ((StringLowercase(rawValue) == "true") || (UnicodeStringToInt(rawValue) != 0))
        {
            value = true;
        }
    }

    return value;
}

template <>
int SystemProperty<int>::Get(const UnicodeString &section, const UnicodeString &key)
{
    int value = 0;

    const UnicodeString rawValue = RawValue(section, key);
    if (rawValue.empty() == false)
    {
        value = UnicodeStringToInt(rawValue);
    }

    return value;
}

bool QuerySetPluginVersion()
{
    bool                result = false;
    UIMessageSupervisor supervisor;

    if(SystemProperty<UnicodeString>::Exists(VERSIONS_SECTION_NAME, THEME_VERSION_KEY_NAME) == true)
    {
        const UnicodeString themeVersion = SystemProperty<UnicodeString>::Get(VERSIONS_SECTION_NAME, THEME_VERSION_KEY_NAME);
        if(themeVersion == VERSION_VALUE_NAME)
        {
            SystemProperty<UnicodeString>::Save(VERSIONS_SECTION_NAME, PLUGIN_VERSION_KEY_NAME, VERSION_VALUE_NAME);
            // quick sanity check
            result = SystemProperty<UnicodeString>::Exists(VERSIONS_SECTION_NAME, PLUGIN_VERSION_KEY_NAME);
        }
        else
        {
            UnicodeStringStream os;
            os << "There is a configuration mismatch between the ULTRASCHALL THEME (" << themeVersion
               << ") and ULTRASCHALL PLUGIN (" << VERSION_VALUE_NAME
               << ").\n\nULTRASCHALL will NOT work properly until you fix this. \n\nPlease proceed by installing the "
                  "new theme or check the installation "
                  "guide on http://ultraschall.fm/install/";
            supervisor.RegisterFatalError(os.str());
            result = false;
        }
    }
    else
    {
        UnicodeStringStream os;
        os << "The ULTRASCHALL THEME is missing.\n\nULTRASCHALL will NOT work properly until you fix this.\n\nPlease "
              "proceed by installing the theme or check the installation guide on http://ultraschall.fm/install/";
        supervisor.RegisterFatalError(os.str());
        result = false;
    }

    return result;
}

void UpdateBillOfMaterials()
{
    static const char* FOUND_ITEMS_KEY_NAME = "found_items";
    static const char* ITEM_KEY_NAME_PREFIX = "item_";

    if(SystemProperty<int>::Exists(BOM_SECTION_NAME, FOUND_ITEMS_KEY_NAME) == true)
    {
        const int foundItems = SystemProperty<int>::Get(BOM_SECTION_NAME, FOUND_ITEMS_KEY_NAME);
        if(foundItems > 0)
        {
            for(int i = 1; i <= foundItems; i++)
            {
                SystemProperty<UnicodeString>::Delete(BOM_SECTION_NAME, ITEM_KEY_NAME_PREFIX + std::to_string(i));
            }
        }
        else
        {
            for(int i = 1; i <= 23; i++)
            {
                if (SystemProperty<UnicodeString>::Exists(BOM_SECTION_NAME, ITEM_KEY_NAME_PREFIX + std::to_string(i)) == true)
                {
                    SystemProperty<UnicodeString>::Delete(BOM_SECTION_NAME, ITEM_KEY_NAME_PREFIX + std::to_string(i));
                }
            }
        }

        SystemProperty<int>::Delete(BOM_SECTION_NAME, FOUND_ITEMS_KEY_NAME);
    }
    else
    {
        for(unsigned int i = 1; i <= 23; i++)
        {
            if (SystemProperty<UnicodeString>::Exists(BOM_SECTION_NAME, ITEM_KEY_NAME_PREFIX + std::to_string(i)) == true)
            {
                SystemProperty<UnicodeString>::Delete(BOM_SECTION_NAME, ITEM_KEY_NAME_PREFIX + std::to_string(i));
            }
        }
    }

    UnicodeStringArray bom;
    UnicodeString      itemVersion = VersionHandler::PluginVersion();
    if(itemVersion.empty() == false)
    {
        bom.push_back("Ultraschall REAPER Extension " + itemVersion);
    }

    itemVersion = VersionHandler::ThemeVersion();
    if(itemVersion.empty() == false)
    {
        bom.push_back("Ultraschall REAPER Theme " + itemVersion);
    }

    itemVersion = VersionHandler::SoundboardVersion();
    if(itemVersion.empty() == false)
    {
        bom.push_back("Ultraschall Soundboard " + itemVersion);
    }

    itemVersion = VersionHandler::StudioLinkVersion();
    if(itemVersion.empty() == false)
    {
        bom.push_back("StudioLink Plug-in " + itemVersion);
    }

    itemVersion = VersionHandler::StudioLinkOnAirVersion();
    if(itemVersion.empty() == false)
    {
        bom.push_back("StudioLink OnAir Plug-in " + itemVersion);
    }

    itemVersion = VersionHandler::SWSVersion();
    if(itemVersion.empty() == false)
    {
        bom.push_back("SWS REAPER Extension " + itemVersion);
    }

    itemVersion = VersionHandler::ReaperVersion();
    if(itemVersion.empty() == false)
    {
        bom.push_back("REAPER " + itemVersion);
    }

    if(bom.empty() == false)
    {
        SystemProperty<int>::Save(BOM_SECTION_NAME, FOUND_ITEMS_KEY_NAME, std::to_string(bom.size()));

        for(size_t i = 0; i < bom.size(); i++)
        {
            SystemProperty<UnicodeString>::Save(BOM_SECTION_NAME, ITEM_KEY_NAME_PREFIX + std::to_string(i + 1), bom[i]);
        }
    }
}

} // namespace reaper
} // namespace ultraschall
