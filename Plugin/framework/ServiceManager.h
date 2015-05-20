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

#ifndef __ULTRASCHALL_FRAMEWORK_SERVICE_MANAGER_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_SERVICE_MANAGER_H_INCL__

#include <string>
#include <mutex>
#include <map>

#include <ServiceFactory.h>

namespace ultraschall { namespace framework {

template<typename ServiceCallbackType> class ServiceManager
{
public:
   typedef ServiceCallbackType service_callback_type;
   typedef IService<service_callback_type> service_type;
   
   static ServiceManager& Instance();

   const ServiceStatus RegisterService(const std::string& name);
   void ReleaseService(const std::string& name);
   void ReleaseAllServices();

   const ServiceStatus AcquireService(const std::string& name, service_type*& pService) const;

protected:
   virtual ~ServiceManager();

private:
   ServiceManager();

   ServiceManager(const ServiceManager&);
   ServiceManager& operator=(const ServiceManager&);

   ServiceFactory<service_callback_type> factory_;
   std::map<std::string, service_type*> services_;
   mutable std::recursive_mutex lock_;
};

template<typename ServiceCallbackType> ServiceManager<ServiceCallbackType>::ServiceManager()
{
}

template<typename ServiceCallbackType> ServiceManager<ServiceCallbackType>::~ServiceManager()
{
   ReleaseAllServices();
}

template<typename ServiceCallbackType> ServiceManager<ServiceCallbackType>& ServiceManager<ServiceCallbackType>::Instance()
{
   static ServiceManager self;
   return self;
}

template<typename ServiceCallbackType> void ServiceManager<ServiceCallbackType>::ReleaseService(const std::string& name)
{
   const std::lock_guard<std::recursive_mutex> lock(lock_);
   
   const typename std::map<std::string, service_type*>::const_iterator i = services_.find(name);
   if(i != services_.end())
   {
      service_type* pService = i->second;
      services_.erase(i);
      SafeRelease(pService);
   }
}

template<typename ServiceCallbackType> void ServiceManager<ServiceCallbackType>::ReleaseAllServices()
{
   const std::lock_guard<std::recursive_mutex> lock(lock_);
   
   while(services_.empty() == false)
   {
      const typename std::map<std::string, service_type*>::const_iterator i = services_.begin();
      if(i != services_.end())
      {
         service_type* pService = i->second;
         services_.erase(i);
         SafeRelease(pService);
      }
   }
}

template<typename ServiceCallbackType> const ServiceStatus ServiceManager<ServiceCallbackType>::AcquireService(const std::string& name, service_type*& pService) const
{
   PRECONDITION_RETURN(name.empty() == false, SERVICE_INVALID_ARGUMENT);
   
   ServiceStatus status = SERVICE_FAILURE;
   
   const std::lock_guard<std::recursive_mutex> lock(lock_);
   
   return status;
}
   
}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_SERVICE_MANAGER_H_INCL__
