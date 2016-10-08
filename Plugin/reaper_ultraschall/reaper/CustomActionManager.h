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

#ifndef __ULTRASCHALL_REAPER_CUSTOM_ACTION_MANAGER_H_INCL__
#define __ULTRASCHALL_REAPER_CUSTOM_ACTION_MANAGER_H_INCL__

#include <mutex>
#include <map>

#include <ServiceStatus.h>

#include "ICustomAction.h"

namespace ultraschall { namespace reaper {

class CustomActionManager
{
public:
   static CustomActionManager& Instance();

   static const int32_t INVALID_CUSTOM_ACTION_ID = -1;
   
   ServiceStatus RegisterCustomAction(const std::string& name, const int32_t id, ICustomAction* pCustomAction);
   void UnregisterCustomAction(const int32_t id);
   void UnregisterCustomAction(const std::string& name);
   void UnregisterAllCustomActions();

   ServiceStatus LookupCustomAction(const int32_t id, ICustomAction*& pCustomAction) const;
   ServiceStatus LookupCustomAction(const std::string& name, ICustomAction*& pCustomAction) const;

protected:
   virtual ~CustomActionManager();

private:
   CustomActionManager();

   CustomActionManager(const CustomActionManager&);
   CustomActionManager& operator=(const CustomActionManager&);

   std::map<int32_t, ICustomAction*> customActions_;
   std::map<std::string, int32_t> customActionIds_;
   mutable std::recursive_mutex customActionsLock_;
};

}}

#endif // #ifndef __ULTRASCHALL_REAPER_CUSTOM_ACTION_MANAGER_H_INCL__

