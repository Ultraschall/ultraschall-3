////////////////////////////////////////////////////////////////////////////////
// 
// Copyright (c) 2016 Ultraschall (http://ultraschall.fm)
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

#include "CommandFactory.h"

namespace ultraschall { namespace reaper {

CommandFactory::CommandFactory()
{
}

CommandFactory::~CommandFactory()
{
}

CommandFactory& CommandFactory::Instance()
{
   static CommandFactory self;
   return self;
}

ServiceStatus CommandFactory::RegisterCommand(const int32_t id, CREATE_COMMAND_FUNCTION pfn)
{
   PRECONDITION_RETURN(ICommand::ValidateCommandId(id) != false, SERVICE_INVALID_ARGUMENT);
   PRECONDITION_RETURN(pfn != 0, SERVICE_INVALID_ARGUMENT);

   ServiceStatus status = SERVICE_FAILURE;

   const std::lock_guard<std::recursive_mutex> lock(factoryFunctionsLock_);

   const std::map<int32_t, CREATE_COMMAND_FUNCTION>::const_iterator functionIterator = factoryFunctions_.find(id);
   if (factoryFunctions_.end() == functionIterator)
   {
      factoryFunctions_.insert(std::pair<int32_t, CREATE_COMMAND_FUNCTION>(id, pfn));
      status = SERVICE_SUCCESS;
   }
   else
   {
      status = SERVICE_FACTORY_NOT_FOUND;
   }

   return status;
}

void CommandFactory::UnregisterCommand(const int32_t id)
{
   PRECONDITION(factoryFunctions_.empty() == false);
   PRECONDITION(ICommand::ValidateCommandId(id) != false);

   const std::lock_guard<std::recursive_mutex> lock(factoryFunctionsLock_);

   const std::map<int32_t, CREATE_COMMAND_FUNCTION>::const_iterator functionIterator = factoryFunctions_.find(id);
   if (factoryFunctions_.end() != functionIterator)
   {
      factoryFunctions_.erase(functionIterator);
   }
}

void CommandFactory::UnregisterAllCommands()
{
   const std::lock_guard<std::recursive_mutex> lock(factoryFunctionsLock_);

   while(factoryFunctions_.empty() == false)
   {
      const std::map<int32_t, CREATE_COMMAND_FUNCTION>::const_iterator functionIterator = factoryFunctions_.begin();
      if(factoryFunctions_.end() != functionIterator)
      {
         factoryFunctions_.erase(functionIterator);
      }
   }
}

ServiceStatus CommandFactory::CreateCommand(const int32_t id, ICommand*& pCommand) const
{
   PRECONDITION_RETURN(ICommand::ValidateCommandId(id) != false, SERVICE_INVALID_ARGUMENT);

   ServiceStatus status = SERVICE_FAILURE;
    
   const std::lock_guard<std::recursive_mutex> lock(factoryFunctionsLock_);

   pCommand = 0;
   const std::map<int32_t, CREATE_COMMAND_FUNCTION>::const_iterator functionIterator = factoryFunctions_.find(id);
   if (factoryFunctions_.end() != functionIterator)
   {
      CREATE_COMMAND_FUNCTION pfn = functionIterator->second;
      if(pfn != 0)
      {
         status = (*pfn)(pCommand);
         if(ServiceSucceeded(status) && (0 == pCommand))
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
