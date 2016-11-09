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

#include "CommandManager.h"

namespace framework = ultraschall::framework;

namespace ultraschall {
namespace reaper {

CommandManager::CommandManager()
{
}

CommandManager::~CommandManager()
{
   UnregisterAllCommands();
}

CommandManager& CommandManager::Instance()
{
   static CommandManager self;
   return self;
}

ServiceStatus CommandManager::RegisterCommand(const int32_t id, ICommand* pCommand)
{
   PRECONDITION_RETURN(ICommand::ValidateCommandId(id) != false, SERVICE_INVALID_ARGUMENT);
   PRECONDITION_RETURN(pCommand != 0, SERVICE_INVALID_ARGUMENT);

   ServiceStatus status = SERVICE_FAILURE;

   std::lock_guard<std::recursive_mutex> lock(commandsLock_);

   std::map<int32_t, ICommand*>::iterator commandIterator = commands_.find(id);
   if(commands_.end() == commandIterator)
   {
      const bool inserted = commands_.insert(std::map<int32_t, ICommand*>::value_type(id, pCommand)).second;
      if(true == inserted)
      {
         pCommand->AddRef();
         status = SERVICE_SUCCESS;
      }
   }
   else
   {
      status = SERVICE_MANAGER_ALREADY_REGISTERED;
   }

   return status;
}

void CommandManager::UnregisterCommand(const int32_t id)
{
   PRECONDITION(ICommand::ValidateCommandId(id) != false);
   PRECONDITION(commands_.empty() == false);

   const std::lock_guard<std::recursive_mutex> lock(commandsLock_);

   const std::map<int32_t, ICommand*>::const_iterator commandIterator = commands_.find(id);
   if(commands_.end() != commandIterator)
   {
      ICommand* pCommand = commandIterator->second;
      commands_.erase(commandIterator);
      framework::SafeRelease(pCommand);
   }
}

void CommandManager::UnregisterAllCommands()
{
   const std::lock_guard<std::recursive_mutex> lock(commandsLock_);

   while(commands_.empty() == false)
   {
      const std::map<int32_t, ICommand*>::const_iterator commandIterator = commands_.begin();
      ICommand* pCommand = commandIterator->second;
      commands_.erase(commandIterator);
      framework::SafeRelease(pCommand);
   }
}

ServiceStatus CommandManager::LookupCommand(const int32_t id, ICommand*& pCommand) const
{
   PRECONDITION_RETURN(ICommand::ValidateCommandId(id) != false, SERVICE_INVALID_ARGUMENT);
   PRECONDITION_RETURN(commands_.empty() == false, SERVICE_MANAGER_NOT_FOUND);

   ServiceStatus status = SERVICE_FAILURE;

   const std::lock_guard<std::recursive_mutex> lock(commandsLock_);

   pCommand = 0;
   const std::map<int32_t, ICommand*>::const_iterator i = commands_.find(id);
   if(i != commands_.end())
   {
      pCommand = i->second;
      if(pCommand != 0)
      {
         pCommand->AddRef();
         status = SERVICE_SUCCESS;
      }
      else
      {
         status = SERVICE_MANAGER_ACQUIRE_FAILED;
      }
   }
   else
   {
      status = SERVICE_MANAGER_NOT_FOUND;
   }

   return status;
}

}
}
