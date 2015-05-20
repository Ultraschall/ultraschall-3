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

#ifndef __ULTRASCHALL_FRAMEWORK_SHARED_OBJECT_MANAGER_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_SHARED_OBJECT_MANAGER__H_INCL__

#include <string>
#include <mutex>
#include <map>

#include <ServiceStatus.h>
#include <SharedObjectFactory.h>

namespace ultraschall { namespace framework {

template<typename SharedObjectType> class SharedObjectManager
{
public:
   static SharedObjectManager<SharedObjectType>& Instance();

   const ServiceStatus Acquire(const std::string& name, SharedObjectType*& pService) const;
   void Release(const std::string& name);
   void ReleaseAll();

protected:
   virtual ~SharedObjectManager();

private:
   SharedObjectManager();

   SharedObjectManager(const SharedObjectManager&);
   SharedObjectManager& operator=(const SharedObjectManager&);

   SharedObjectFactory<SharedObjectType> sharedObjectFactory_;

   std::map<std::string, SharedObjectType*> sharedObjectTypes_;
   mutable std::recursive_mutex sharedObjectTypesLock_;
};

template<typename SharedObjectType> SharedObjectManager<SharedObjectType>::SharedObjectManager()
{
}

template<typename SharedObjectType> SharedObjectManager<SharedObjectType>::~SharedObjectManager()
{
   ReleaseAll();
}

template<typename SharedObjectType> SharedObjectManager<SharedObjectType>& SharedObjectManager<SharedObjectType>::Instance()
{
   static SharedObjectManager<SharedObjectType> self;
   return self;
}

template<typename SharedObjectType> void SharedObjectManager<SharedObjectType>::Release(const std::string& name)
{
   const std::lock_guard<std::recursive_mutex> lock(sharedObjectTypesLock_);

   const std::map<std::string, SharedObjectType*>::const_iterator i = types_.find(name);
   if(i != types_.end())
   {
      SharedObjectType* ptr = i->second;
      types_.erase(i);
      framework::SafeRelease(ptr);
   }
}

template<typename SharedObjectType> void SharedObjectManager<SharedObjectType>::ReleaseAll()
{
   const std::lock_guard<std::recursive_mutex> lock(sharedObjectTypesLock_);

   while(types_.empty() == false)
   {
      const std::map<std::string, SharedObjectType*>::const_iterator i = types_.begin();
      if(i != types_.end())
      {
         SharedObjectType* ptr = i->second;
         types_.erase(i);
         framework::SafeRelease(ptr);
      }
   }
}

template<typename SharedObjectType> const ServiceStatus SharedObjectManager<SharedObjectType>::Acquire(const std::string& name, SharedObjectType*& pService) const
{
   PRECONDITION_RETURN(name.empty() == false, SERVICE_INVALID_ARGUMENT);

   ServiceStatus status = SERVICE_FAILURE;

   const std::lock_guard<std::recursive_mutex> lock(sharedObjectTypesLock_);

   return status;
}

}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_SharedObjectManager__H_INCL__
