////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2014-2016 Ultraschall (http://ultraschall.fm)
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

#include <ServiceManager.h>

namespace ultraschall { namespace framework {
   
ServiceManager::ServiceManager()
{
}

ServiceManager::~ServiceManager()
{
   ReleaseAllServices();
}

ServiceManager& ServiceManager::Instance()
{
   static ServiceManager self;
   return self;
}

void ServiceManager::ReleaseService(const std::string& name)
{
   const std::lock_guard<std::recursive_mutex> lock(servicesLock_);
   
   const typename std::map<std::string, IService*>::const_iterator i = services_.find(name);
   if(i != services_.end())
   {
      IService* pService = i->second;
      services_.erase(i);
      SafeRelease(pService);
   }
}

void ServiceManager::ReleaseAllServices()
{
   const std::lock_guard<std::recursive_mutex> lock(servicesLock_);
   
   while(services_.empty() == false)
   {
      std::map<std::string, IService*>::const_iterator i = services_.begin();
      if(i != services_.end())
      {
         IService* pService = i->second;
         services_.erase(i);
         SafeRelease(pService);
      }
   }
}

ServiceStatus ServiceManager::AcquireService(const std::string& name, IService*& pService) const
{
   PRECONDITION_RETURN(name.empty() == false, SERVICE_INVALID_ARGUMENT);

   ServiceStatus status = SERVICE_FAILURE;
   pService = 0;

   const std::lock_guard<std::recursive_mutex> lock(servicesLock_);
   
   return status;
}
   
}}

