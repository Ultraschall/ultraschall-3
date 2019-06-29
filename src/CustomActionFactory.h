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

#ifndef __ULTRASCHALL_REAPER_CUSTOM_ACTION_FACTORY_H_INCL__
#define __ULTRASCHALL_REAPER_CUSTOM_ACTION_FACTORY_H_INCL__

#include "Common.h"

namespace ultraschall { namespace reaper {

class ICustomAction;

class CustomActionFactory
{
public:
    static CustomActionFactory& Instance();

    typedef ICustomAction* (*CREATE_CUSTOM_ACTION_FUNCTION)();

    ServiceStatus RegisterCustomAction(const UnicodeString& id, CREATE_CUSTOM_ACTION_FUNCTION pfn);

    void UnregisterCustomAction(const UnicodeString& id);
    void UnregisterAllCustomActions();

    ServiceStatus CreateCustomAction(const UnicodeString& id, ICustomAction*& pCustomAction) const;

protected:
    virtual ~CustomActionFactory();

private:
    CustomActionFactory();

    CustomActionFactory(const CustomActionFactory&);
    CustomActionFactory& operator=(const CustomActionFactory&);

    typedef std::map<UnicodeString, CREATE_CUSTOM_ACTION_FUNCTION> FunctionDictionary;
    FunctionDictionary                                           functions_;
    mutable std::recursive_mutex                                 functionsLock_;
};

template<class C> class DeclareCustomAction
{
public:
    typedef C custom_action_type;

    DeclareCustomAction()
    {
        CustomActionFactory& factory = CustomActionFactory::Instance();
        factory.RegisterCustomAction(custom_action_type::UniqueId(), custom_action_type::CreateCustomAction);
    }

    virtual ~DeclareCustomAction()
    {
        CustomActionFactory& factory = CustomActionFactory::Instance();
        factory.UnregisterCustomAction(custom_action_type::UniqueId());
    }
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_CUSTOM_ACTION_FACTORY_H_INCL__
