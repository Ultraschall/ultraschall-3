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

#include "ResourceManager.h"

#ifdef WIN32
#include <windows.h>
#include <shobjidl.h>
#else
#import <AppKit/AppKit.h>
#endif

namespace ultraschall { namespace framework {
    
ResourceManager::ResourceManager() :
    currentLanguage_("en-EN")
{
    localizedStrings_.insert(std::pair<std::string, std::map<ResourceId, std::string>>("en-EN", std::map<ResourceId, std::string>()));
    localizedStrings_.insert(std::pair<std::string, std::map<ResourceId, std::string>>("de-DE", std::map<ResourceId, std::string>()));
}

ResourceManager::~ResourceManager()
{
}

ResourceManager& ResourceManager::Instance()
{
    static ResourceManager self;
    return self;
}
   
void ResourceManager::SetLanguage(const std::string& id)
{
    currentLanguage_ = id;
}
   
void ResourceManager::SetOperatingSystemLanguage()
{
#ifndef WIN32
   currentLanguage_ = "en-EN";

   NSLocale *locale = [NSLocale currentLocale];
   NSString *country = [locale objectForKey:NSLocaleLanguageCode];
   if (country != nil)
   {
      std::string language = [country UTF8String];
      if(language.empty() == false)
      {
         if(language == "de")
         {
            currentLanguage_ = "de-DE";
         }
      }
   }
#endif // #ifdef WIN32
}
   
const char* ResourceManager::GetLocalizedString(const ResourceId& id) const
{
   static std::string stringNotFound("<<ResourceManager: The specified resource could not be found!>>");
   const char* result = stringNotFound.c_str();
   
   std::set<ResourceId>::const_iterator idIterator = ids_.find(id);
   if(ids_.end() != idIterator)
   {
      const std::map<std::string, std::map<ResourceId, std::string>>::const_iterator languageIterator = localizedStrings_.find(currentLanguage_);
      if(languageIterator != localizedStrings_.end())
      {
         const std::map<ResourceId, std::string>& currentLanguage = languageIterator->second;
         const std::map<ResourceId, std::string>::const_iterator stringIterator = currentLanguage.find(id);
         if(stringIterator != currentLanguage.end())
         {
            result = stringIterator->second.c_str();
         }
      }
   }

   return result;
}

ServiceStatus ResourceManager::RegisterLocalizedString(const ResourceId& id)
{
   ServiceStatus status = SERVICE_FAILURE;
   
   std::set<ResourceId>::const_iterator idIterator = ids_.find(id);
   if(ids_.end() == idIterator)
   {
      ids_.insert(id);
      status = SERVICE_SUCCESS;
   }
   else
   {
      status = SERVICE_MANAGER_ALREADY_REGISTERED;
   }
   
   return status;
}
   
ServiceStatus ResourceManager::SetLocalizedString(const ResourceId& id, const std::string& language, const std::string& str)
{
   ServiceStatus status = SERVICE_FAILURE;
   
   std::set<ResourceId>::const_iterator idIterator = ids_.find(id);
   if(ids_.end() != idIterator)
   {
      std::map<std::string, std::map<ResourceId, std::string>>::iterator languageIterator = localizedStrings_.find(language);
      if(languageIterator != localizedStrings_.end())
      {
         std::map<ResourceId, std::string>& currentLanguage = languageIterator->second;
         currentLanguage.insert(std::map<ResourceId, std::string>::value_type(id, str));
         status = SERVICE_SUCCESS;
      }
      else
      {
         status = SERVICE_MANAGER_NOT_FOUND;
      }
   }
   else
   {
      status = SERVICE_MANAGER_NOT_FOUND;
   }
   
   return status;
}

void ResourceManager::UnregisterLocalizedString(const ResourceId& id)
{
   for(std::map<std::string, std::map<ResourceId, std::string>>::iterator languageIterator = localizedStrings_.begin();
       localizedStrings_.end() != languageIterator; languageIterator++)
   {
      std::map<ResourceId, std::string>& currentLanguage = languageIterator->second;
      currentLanguage.erase(id);
   }
   
   ids_.erase(id);
}
   
}}

