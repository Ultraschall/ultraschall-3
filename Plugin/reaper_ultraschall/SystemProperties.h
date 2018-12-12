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

#ifndef __ULTRASCHALL_REAPER_SYSTEM_PROPERTIES_H_INCL__
#define __ULTRASCHALL_REAPER_SYSTEM_PROPERTIES_H_INCL__

#include <string>

namespace ultraschall { namespace reaper {

template<class T> class SystemProperty
{
public:
    typedef T value_type;

    static bool Exists(const std::string& section, const std::string& key)
    {
        PRECONDITION_RETURN(key.empty() == false, false);
        return reaper_api::HasExtState(section.c_str(), key.c_str());
    }

    static void
        Set(const std::string& section, const std::string& key, const std::string& value, const bool save = false)
    {
        PRECONDITION(key.empty() == false);
        PRECONDITION(value.empty() == false);
        reaper_api::SetExtState(section.c_str(), key.c_str(), value.c_str(), save);
    }

    static value_type Get(const std::string& section, const std::string& key);

    static void Delete(const std::string& section, const std::string& key, const bool save = false)
    {
        PRECONDITION(key.empty() == false);
        reaper_api::DeleteExtState(section.c_str(), key.c_str(), save);
    }

private:
    static std::string RawValue(const std::string& section, const std::string& key)
    {
        PRECONDITION_RETURN(key.empty() == false, std::string());
        return reaper_api::GetExtState(section.c_str(), key.c_str());
    }
};

static const char* VERSIONS_SECTION_NAME = "ultraschall_versions";
static const char* UPDATE_SECTION_NAME   = "ultraschall_update";
static const char* BOM_SECTION_NAME      = "ultraschall_bom";
bool               QuerySetPluginVersion();

static const char* SAFETY_LEVEL_SECTION_NAME = "ultraschall_safety";

typedef enum {
    STRICT_SAFETY_LEVEL       = 0,
    RELAXED_SAFETY_LEVEL      = 1,
    EXPERIMENTAL_SAFETY_LEVEL = 2
} ULTRASCHALL_SAFETY_LEVEL;

bool StrictSafetyLevel();
bool RelaxedSafetyLevel();
bool ExperimentalSafetyLevel();

void UpdateBillOfMaterials();

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_SYSTEM_PROPERTIES_H_INCL__
