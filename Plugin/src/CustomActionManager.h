////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
//
// The MIT License (MIT)
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

#include "Common.h"
#include "CustomAction.h"
#include "ServiceStatus.h"

namespace ultraschall { namespace reaper {

class CustomActionManager
{
public:
    static CustomActionManager& Instance();

    ServiceStatus RegisterCustomAction(const UnicodeString& name, const int32_t id, ICustomAction* pCustomAction);

    void UnregisterCustomAction(const int32_t id);
    void UnregisterCustomAction(const UnicodeString& name);
    void UnregisterAllCustomActions();

    ServiceStatus LookupCustomAction(const int32_t id, ICustomAction*& pCustomAction) const;
    ServiceStatus LookupCustomAction(const UnicodeString& name, ICustomAction*& pCustomAction) const;

protected:
    virtual ~CustomActionManager();

private:
    CustomActionManager();

    CustomActionManager(const CustomActionManager&);
    CustomActionManager& operator=(const CustomActionManager&);

    typedef std::map<int32_t, ICustomAction*> CustomActionDictionary; 
    CustomActionDictionary                    customActions_;
    typedef std::map<UnicodeString, int32_t>    CustomActionIdDictionary;
    CustomActionIdDictionary customActionIds_;
    mutable std::recursive_mutex      customActionsLock_;
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_CUSTOM_ACTION_MANAGER_H_INCL__
