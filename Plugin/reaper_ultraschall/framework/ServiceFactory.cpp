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

#include <ServiceFactory.h>

namespace ultraschall { namespace framework {
   
ServiceFactory::ServiceFactory()
{
}

ServiceFactory::~ServiceFactory()
{
   UnregisterAllServices();
}

ServiceStatus ServiceFactory::RegisterService(const std::string& name, const CREATE_SERVICE_FUNCTION pfn)
{
   PRECONDITION_RETURN(name.empty() == false, SERVICE_INVALID_ARGUMENT);
   PRECONDITION_RETURN(pfn != 0, SERVICE_INVALID_ARGUMENT);
   
   ServiceStatus status = SERVICE_FAILURE;
   
   const std::lock_guard<std::recursive_mutex> lock(functionsLock_);
   
   const typename std::map<std::string, CREATE_SERVICE_FUNCTION>::const_iterator i = functions_.find(name);
   if (functions_.end() == i)
   {
      functions_.insert(std::pair<std::string, CREATE_SERVICE_FUNCTION>(name, pfn));
      status = SERVICE_SUCCESS;
   }
   
   return status;
}

void ServiceFactory::UnregisterService(const std::string& name)
{
   PRECONDITION(functions_.empty() == false);
   PRECONDITION(name.empty() == false);
   
   const std::lock_guard<std::recursive_mutex> lock(functionsLock_);
   
   const typename std::map<std::string, CREATE_SERVICE_FUNCTION>::const_iterator i = functions_.find(name);
   if (functions_.end() != i)
   {
      functions_.erase(i);
   }
}

void ServiceFactory::UnregisterAllServices()
{
   PRECONDITION(functions_.empty() == false);
   
   const std::lock_guard<std::recursive_mutex> lock(functionsLock_);
   
   while(functions_.empty() == false)
   {
      const typename std::map<std::string, CREATE_SERVICE_FUNCTION>::const_iterator i = functions_.begin();
      if(functions_.end() != i)
      {
         functions_.erase(i);
      }
   }
}

ServiceStatus ServiceFactory::CreateService(const std::string& name, IService*& pService) const
{
   PRECONDITION_RETURN(name.empty() == false, SERVICE_INVALID_ARGUMENT);
   
   ServiceStatus status = SERVICE_FAILURE;
   
   const std::lock_guard<std::recursive_mutex> lock(functionsLock_);
   
   pService = 0;
   
   const typename std::map<std::string, CREATE_SERVICE_FUNCTION>::const_iterator i = functions_.find(name);
   if (functions_.end() != i)
   {
      const CREATE_SERVICE_FUNCTION pCreateFunction = i->second;
      if(pCreateFunction != 0)
      {
         status = (*pCreateFunction)(pService);
         if(ServiceSucceeded(status) && (0 == pService))
         {
            status = SERVICE_FACTORY_CREATE_FAILED;
         }
      }
      else
      {
         status = SERVICE_FACTORY_CREATE_FAILED;
      }
   }
   else
   {
      status = SERVICE_FACTORY_NOT_FOUND;
   }
   
   return status;
}
   
}}

