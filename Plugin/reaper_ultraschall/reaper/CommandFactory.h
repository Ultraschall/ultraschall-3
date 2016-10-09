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

#ifndef __ULTRASCHALL_REAPER_COMMAND_FACTORY_H_INCL__
#define __ULTRASCHALL_REAPER_COMMAND_FACTORY_H_INCL__

#include <mutex>
#include <map>

#include <ServiceStatus.h>

#include "ICommand.h"

namespace ultraschall { namespace reaper {

class CommandFactory
{
public:
   static CommandFactory& Instance();

   typedef ServiceStatus (*CREATE_COMMAND_FUNCTION)(ICommand*&);

   ServiceStatus RegisterCommand(const int32_t id, CREATE_COMMAND_FUNCTION pfn);
   void UnregisterCommand(const int32_t id);
   void UnregisterAllCommands();

   ServiceStatus CreateCommand(const int32_t id, ICommand*& pCommand) const;

protected:
   virtual ~CommandFactory();

private:
   CommandFactory();

   CommandFactory(const CommandFactory&);
   CommandFactory& operator=(const CommandFactory&);

   std::map<int32_t, CREATE_COMMAND_FUNCTION> factoryFunctions_;
   mutable std::recursive_mutex factoryFunctionsLock_;
};

}}

#endif // #ifndef __ULTRASCHALL_REAPER_COMMAND_FACTORY_H_INCL__
