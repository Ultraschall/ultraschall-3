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

#ifndef __ULTRASCHALL_FRAMEWORK_SHARED_OBJECT_FACTORY_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_SHARED_OBJECT_FACTORY_H_INCL__

#include <string>
#include <mutex>
#include <map>

#include <Framework.h>
#include <ServiceStatus.h>

namespace ultraschall { namespace framework {

template<typename SharedObjectType> class SharedObjectFactory
{
public:
   SharedObjectFactory();
   virtual ~SharedObjectFactory();

   typedef const ServiceStatus(*CreateFunction)(SharedObjectType*&);

   const ServiceStatus Register(const std::string& name, const CreateFunction pfn);
   void Unregister(const std::string& name);
   void UnregisterAll();

   const ServiceStatus Create(const std::string& name, SharedObjectType*& pService) const;

private:
   SharedObjectFactory(const SharedObjectFactory&);
   SharedObjectFactory& operator=(const SharedObjectFactory&);

   std::map<std::string, CreateFunction> functions_;
   mutable std::recursive_mutex functionsLock_;
};

template<typename SharedObjectType> SharedObjectFactory<SharedObjectType>::SharedObjectFactory()
{
}

template<typename SharedObjectType> SharedObjectFactory<SharedObjectType>::~SharedObjectFactory()
{
   UnregisterAll();
}

template<typename SharedObjectType> const ServiceStatus SharedObjectFactory<SharedObjectType>::Register(const std::string& name, const CreateFunction pfn)
{
   PRECONDITION_RETURN(name.empty() == false, SERVICE_INVALID_ARGUMENT);
   PRECONDITION_RETURN(pfn != 0, SERVICE_INVALID_ARGUMENT);

   ServiceStatus status = SERVICE_FAILURE;

   const std::lock_guard<std::recursive_mutex> lock(functionsLock_);

   const std::map<std::string, CreateFunction>::const_iterator i = functions_.find(name);
   if(functions_.end() == i)
   {
      functions_.insert(std::pair<std::string, CreateFunction>(name, pfn));
      status = SERVICE_SUCCESS;
   }

   return status;
}

template<typename SharedObjectType> void SharedObjectFactory<SharedObjectType>::Unregister(const std::string& name)
{
   PRECONDITION(functions_.empty() == false);
   PRECONDITION(name.empty() == false);

   const std::lock_guard<std::recursive_mutex> lock(functionsLock_);

   const std::map<std::string, CreateFunction>::const_iterator i = functions_.find(name);
   if(functions_.end() != i)
   {
      functions_.erase(i);
   }
}

template<typename SharedObjectType> void SharedObjectFactory<SharedObjectType>::UnregisterAll()
{
   PRECONDITION(functions_.empty() == false);

   const std::lock_guard<std::recursive_mutex> lock(functionsLock_);

   while(functions_.empty() == false)
   {
      const std::map<std::string, CreateFunction>::const_iterator i = functions_.begin();
      if(functions_.end() != i)
      {
         functions_.erase(i);
      }
   }
}

template<typename SharedObjectType> const ServiceStatus SharedObjectFactory<SharedObjectType>::Create(const std::string& name, SharedObjectType*& ptr) const
{
   PRECONDITION_RETURN(name.empty() == false, SERVICE_INVALID_ARGUMENT);

   ServiceStatus status = SERVICE_FAILURE;

   const std::lock_guard<std::recursive_mutex> lock(functionsLock_);

   ptr = nullptr;
   const std::map<std::string, CreateFunction>::const_iterator i = functions_.find(name);
   if(functions_.end() != i)
   {
      const CreateFunction pCreateFunction = i->second;
      if(pCreateFunction != nullptr)
      {
         status = (*pCreateFunction)(ptr);
         if(ServiceSucceeded(status) && (nullptr == ptr))
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

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_SHARED_OBJECT_FACTORY_H_INCL__
