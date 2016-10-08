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

#ifndef __ULTRASCHALL_REAPER_CUSTOM_ACTION_FACTORY_H_INCL__
#define __ULTRASCHALL_REAPER_CUSTOM_ACTION_FACTORY_H_INCL__

#include <mutex>
#include <map>

#include <ServiceStatus.h>

namespace ultraschall { namespace reaper {

class ICustomAction;

class CustomActionFactory
{
public:
   static CustomActionFactory& Instance();

   typedef ServiceStatus (*CREATE_CUSTOM_ACTION_FUNCTION)(ICustomAction*&);
   ServiceStatus RegisterCustomAction(const std::string& id, CREATE_CUSTOM_ACTION_FUNCTION pfn);
   void UnregisterCustomAction(const std::string& id);
   void UnregisterAllCustomActions();

   ServiceStatus CreateCustomAction(const std::string& id, ICustomAction*& pCustomAction) const;

protected:
   virtual ~CustomActionFactory();

private:
   CustomActionFactory();

   CustomActionFactory(const CustomActionFactory&);
   CustomActionFactory& operator=(const CustomActionFactory&);

   std::map<std::string, CREATE_CUSTOM_ACTION_FUNCTION> functions_;
   mutable std::recursive_mutex functionsLock_;
};

}}

#endif // #ifndef __ULTRASCHALL_REAPER_CUSTOM_ACTION_FACTORY_H_INCL__
