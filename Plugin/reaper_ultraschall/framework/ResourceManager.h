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

#ifndef __ULTRASCHALL_FRAMEWORK_RESOURCE_MANAGER_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_RESOURCE_MANAGER_H_INCL__

#include <string>
#include <map>
#include <set>

#include <Framework.h>
#include <ServiceStatus.h>
#include <ResourceId.h>

namespace ultraschall { namespace framework {

class ResourceManager
{
public:
   virtual ~ResourceManager();
   
   static ResourceManager& Instance();
    
   void SetLanguage(const std::string& id);
   void SetOperatingSystemLanguage();
   
   ServiceStatus RegisterLocalizedString(const ResourceId& id);
   ServiceStatus SetLocalizedString(const ResourceId& id, const std::string& language, const std::string& str);
   void UnregisterLocalizedString(const ResourceId& id);
   
   const char* GetLocalizedString(const ResourceId& id) const;
   
private:
   ResourceManager();
    
   ResourceManager(const ResourceManager&);
   ResourceManager& operator=(const ResourceManager&);
   
   std::set<ResourceId> ids_;
   
   std::string currentLanguage_;
   std::map<std::string, std::map<ResourceId, std::string>> localizedStrings_;
};
    
}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_RESOURCE_MANAGER_H_INCL__
