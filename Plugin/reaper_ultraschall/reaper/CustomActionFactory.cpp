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

#include <Framework.h>

#include "CustomActionFactory.h"
#include "ICustomAction.h"

namespace ultraschall { namespace reaper {

CustomActionFactory::CustomActionFactory()
{
}

CustomActionFactory::~CustomActionFactory()
{
}

CustomActionFactory& CustomActionFactory::Instance()
{
   static CustomActionFactory self;
   return self;
}

ServiceStatus CustomActionFactory::RegisterCustomAction(const std::string& id, CREATE_CUSTOM_ACTION_FUNCTION pfn)
{
   PRECONDITION_RETURN(id.empty() == false, SERVICE_INVALID_ARGUMENT);
   PRECONDITION_RETURN(pfn != 0, SERVICE_INVALID_ARGUMENT);

   ServiceStatus status = SERVICE_FAILURE;

   const std::lock_guard<std::recursive_mutex> lock(functionsLock_);

   const std::map<std::string, CREATE_CUSTOM_ACTION_FUNCTION>::const_iterator i = functions_.find(id);
   if (functions_.end() == i)
   {
      functions_.insert(std::pair<std::string, CREATE_CUSTOM_ACTION_FUNCTION>(id, pfn));
      status = SERVICE_SUCCESS;
   }
   else
   {
      status = SERVICE_FACTORY_NOT_FOUND;
   }

   return status;
}

void CustomActionFactory::UnregisterCustomAction(const std::string& id)
{
   PRECONDITION(functions_.empty() == false);
   PRECONDITION(id.empty() == false);

   const std::lock_guard<std::recursive_mutex> lock(functionsLock_);

   const std::map<std::string, CREATE_CUSTOM_ACTION_FUNCTION>::const_iterator i = functions_.find(id);
   if (functions_.end() != i)
   {
      functions_.erase(i);
   }
}

void CustomActionFactory::UnregisterAllCustomActions()
{
   PRECONDITION(functions_.empty() == false);

   const std::lock_guard<std::recursive_mutex> lock(functionsLock_);

   while(functions_.empty() == false)
   {
      const std::map<std::string, CREATE_CUSTOM_ACTION_FUNCTION>::const_iterator i = functions_.begin();
      if(functions_.end() != i)
      {
         functions_.erase(i);
      }
   }
}

ServiceStatus CustomActionFactory::CreateCustomAction(const std::string& id, ICustomAction*& pCustomAction) const
{
   PRECONDITION_RETURN(id.empty() == false, SERVICE_INVALID_ARGUMENT);

   ServiceStatus status = SERVICE_FAILURE;
    
   const std::lock_guard<std::recursive_mutex> lock(functionsLock_);

   pCustomAction = 0;
   const std::map<std::string, CREATE_CUSTOM_ACTION_FUNCTION>::const_iterator i = functions_.find(id);
   if (functions_.end() != i)
   {
      CREATE_CUSTOM_ACTION_FUNCTION pfn = i->second;
      if(pfn != 0)
      {
         status = (*pfn)(pCustomAction);
         if(ServiceSucceeded(status) && (0 == pCustomAction))
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
