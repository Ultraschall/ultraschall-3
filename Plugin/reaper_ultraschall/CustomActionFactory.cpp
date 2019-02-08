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

#include "CustomActionFactory.h"

namespace ultraschall { namespace reaper {

CustomActionFactory::CustomActionFactory() {}

CustomActionFactory::~CustomActionFactory() {}

CustomActionFactory& CustomActionFactory::Instance()
{
    static CustomActionFactory self;
    return self;
}

ServiceStatus CustomActionFactory::RegisterCustomAction(const UnicodeString& id, CREATE_CUSTOM_ACTION_FUNCTION pfn)
{
    PRECONDITION_RETURN(id.empty() == false, SERVICE_INVALID_ARGUMENT);
    PRECONDITION_RETURN(pfn != 0, SERVICE_INVALID_ARGUMENT);

    ServiceStatus status = SERVICE_FAILURE;

    const std::lock_guard<std::recursive_mutex> lock(functionsLock_);

    const FunctionDictionary::const_iterator i = functions_.find(id);
    if (functions_.end() == i)
    {
        functions_.insert(std::pair<UnicodeString, CREATE_CUSTOM_ACTION_FUNCTION>(id, pfn));
        status = SERVICE_SUCCESS;
    }
    else
    {
        status = SERVICE_FACTORY_NOT_FOUND;
    }

    return status;
}

void CustomActionFactory::UnregisterCustomAction(const UnicodeString& id)
{
    PRECONDITION(functions_.empty() == false);
    PRECONDITION(id.empty() == false);

    const std::lock_guard<std::recursive_mutex> lock(functionsLock_);

    const FunctionDictionary::const_iterator functionIterator = functions_.find(id);
    if (functions_.end() != functionIterator)
    {
        functions_.erase(functionIterator);
    }
}

void CustomActionFactory::UnregisterAllCustomActions()
{
    const std::lock_guard<std::recursive_mutex> lock(functionsLock_);

    while (functions_.empty() == false)
    {
        const FunctionDictionary::const_iterator functionIterator = functions_.begin();
        if (functions_.end() != functionIterator)
        {
            functions_.erase(functionIterator);
        }
    }
}

ServiceStatus CustomActionFactory::CreateCustomAction(const UnicodeString& id, ICustomAction*& pCustomAction) const
{
    PRECONDITION_RETURN(id.empty() == false, SERVICE_INVALID_ARGUMENT);

    ServiceStatus status = SERVICE_FACTORY_CREATE_FAILED;

    const std::lock_guard<std::recursive_mutex> lock(functionsLock_);

    pCustomAction                              = 0;
    const FunctionDictionary::const_iterator i = functions_.find(id);
    if (functions_.end() != i)
    {
        CREATE_CUSTOM_ACTION_FUNCTION pfn = i->second;
        if (pfn != 0)
        {
            pCustomAction = (*pfn)();
            if (pCustomAction != 0)
            {
                status = SERVICE_SUCCESS;
            }
        }
    }
    else
    {
        status = SERVICE_FACTORY_NOT_FOUND;
    }

    return status;
}

}} // namespace ultraschall::reaper
