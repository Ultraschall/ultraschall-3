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

#include "CustomActionManager.h"
#include "ICustomAction.h"

namespace framework = ultraschall::framework;

namespace ultraschall {
    namespace reaper {

        CustomActionManager::CustomActionManager()
        {
        }

        CustomActionManager::~CustomActionManager()
        {
            UnregisterAllCustomActions();
        }

        CustomActionManager& CustomActionManager::Instance()
        {
            static CustomActionManager self;
            return self;
        }

        ServiceStatus CustomActionManager::RegisterCustomAction(const std::string& name, int32_t id, ICustomAction* pCustomAction)
        {
            PRECONDITION_RETURN(customActions_.size() == customActionIds_.size(), SERVICE_FAILURE);
            PRECONDITION_RETURN(id != INVALID_CUSTOM_ACTION_ID, SERVICE_INVALID_ARGUMENT);
            PRECONDITION_RETURN(pCustomAction != 0, SERVICE_INVALID_ARGUMENT);

            ServiceStatus status = SERVICE_FAILURE;

            std::lock_guard<std::recursive_mutex> lock(customActionsLock_);

            std::map<int32_t, ICustomAction*>::iterator actionIterator = customActions_.find(id);
            if(customActions_.end() == actionIterator)
            {
                std::map<std::string, int32_t>::iterator idIterator = customActionIds_.find(name);
                if(customActionIds_.end() == idIterator)
                {
                    bool inserted = customActionIds_.insert(std::map<std::string, int32_t>::value_type(name, id)).second;
                    if(true == inserted)
                    {
                        pCustomAction->AddRef();
                        inserted = customActions_.insert(std::map<int32_t, ICustomAction*>::value_type(id, pCustomAction)).second;
                        if(true == inserted)
                        {
                            status = SERVICE_SUCCESS;
                        }
                    }
                }
            }
            else
            {
                status = SERVICE_MANAGER_ALREADY_REGISTERED;
            }

            return status;
        }

        void CustomActionManager::UnregisterCustomAction(const int32_t id)
        {
            PRECONDITION(customActions_.empty() == false);
            PRECONDITION(customActionIds_.empty() == false);
            PRECONDITION(id != INVALID_CUSTOM_ACTION_ID);

            const std::lock_guard<std::recursive_mutex> lock(customActionsLock_);

            const std::map<int32_t, ICustomAction*>::const_iterator actionIterator = customActions_.find(id);
            if(customActions_.end() != actionIterator)
            {
                ICustomAction* pCustomAction = actionIterator->second;
                customActions_.erase(actionIterator);
                framework::SafeRelease(pCustomAction);
            }

            std::map<std::string, int32_t>::iterator idIterator = customActionIds_.begin();
            while(customActionIds_.end() != idIterator)
            {
                const int32_t actionId = idIterator->second;
                if(id == actionId)
                {
                    customActionIds_.erase(idIterator);
                    break;
                }

                idIterator++;
            }
        }

        void CustomActionManager::UnregisterCustomAction(const std::string& name)
        {
            PRECONDITION(customActions_.empty() == false);
            PRECONDITION(customActionIds_.empty() == false);
            PRECONDITION(name.empty() == false);

            const std::lock_guard<std::recursive_mutex> lock(customActionsLock_);

            const std::map<std::string, int32_t>::const_iterator idIterator = customActionIds_.find(name);
            if(customActionIds_.end() != idIterator)
            {
                const int32_t id = idIterator->second;
                const std::map<int32_t, ICustomAction*>::const_iterator actionIterator = customActions_.find(id);
                if(customActions_.end() != actionIterator)
                {
                    ICustomAction* pCustomAction = actionIterator->second;
                    customActions_.erase(actionIterator);
                    framework::SafeRelease(pCustomAction);
                }

                customActionIds_.erase(idIterator);
            }
        }

        void CustomActionManager::UnregisterAllCustomActions()
        {
            const std::lock_guard<std::recursive_mutex> lock(customActionsLock_);

            while(customActionIds_.empty() == false)
            {
                const std::map<std::string, int32_t>::const_iterator idIterator = customActionIds_.begin();
                customActionIds_.erase(idIterator);
            }

            while(customActions_.empty() == false)
            {
                const std::map<int32_t, ICustomAction*>::const_iterator actionIterator = customActions_.begin();
                ICustomAction* pCustomAction = actionIterator->second;
                customActions_.erase(actionIterator);
                framework::SafeRelease(pCustomAction);
            }
        }

        ServiceStatus CustomActionManager::LookupCustomAction(const int32_t id, ICustomAction*& pCustomAction) const
        {
            PRECONDITION_RETURN(customActions_.size() == customActionIds_.size(), SERVICE_FAILURE);
            PRECONDITION_RETURN(customActions_.empty() == false, SERVICE_MANAGER_NOT_FOUND);
            PRECONDITION_RETURN(id != 0, SERVICE_INVALID_ARGUMENT);

            ServiceStatus status = SERVICE_FAILURE;

            const std::lock_guard<std::recursive_mutex> lock(customActionsLock_);

            pCustomAction = 0;
            const std::map<int32_t, ICustomAction*>::const_iterator i = customActions_.find(id);
            if(i != customActions_.end())
            {
                pCustomAction = i->second;
                if(pCustomAction != 0)
                {
                    pCustomAction->AddRef();
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

        ServiceStatus CustomActionManager::LookupCustomAction(const std::string& name, ICustomAction*& pCustomAction) const
        {
            PRECONDITION_RETURN(customActions_.size() == customActionIds_.size(), SERVICE_FAILURE);
            PRECONDITION_RETURN(customActions_.empty() == false, SERVICE_MANAGER_NOT_FOUND);
            PRECONDITION_RETURN(name.empty() == false, SERVICE_INVALID_ARGUMENT);

            ServiceStatus status = SERVICE_FAILURE;

            const std::lock_guard<std::recursive_mutex> lock(customActionsLock_);

            pCustomAction = 0;
            const std::map<std::string, int32_t>::const_iterator idIterator = customActionIds_.find(name);
            if(idIterator != customActionIds_.end())
            {
                const int32_t id = idIterator->second;
                status = LookupCustomAction(id, pCustomAction);
            }
            else
            {
                status = SERVICE_MANAGER_NOT_FOUND;
            }

            return status;
        }

    }
}
