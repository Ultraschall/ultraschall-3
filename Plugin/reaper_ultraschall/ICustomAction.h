////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

#ifndef __ULTRASCHALL_REAPER_ICUSTOM_ACTION_H_INCL__
#define __ULTRASCHALL_REAPER_ICUSTOM_ACTION_H_INCL__

#include "Common.h"

#include "ProjectManager.h"

namespace ultraschall { namespace reaper {

class ICustomAction : public SharedObject
{
public:
    static bool ValidateCustomActionId(const int32_t id)
    {
        return id != INVALID_CUSTOM_ACTION_ID;
    }

    virtual ServiceStatus Execute() = 0;

    static bool RegisterProject()
    {
        bool registered = false;

        ProjectManager& projectManager          = ProjectManager::Instance();
        void*   currentProjectReference = projectManager.CurrentProjectReference();
        if (currentProjectReference != nullptr)
        {
            const Project& currentProject = projectManager.LookupProject(currentProjectReference);
            if (Project::Validate(currentProject) == false)
            {
                registered = projectManager.InsertProject(currentProjectReference);
            }
            else
            {
                registered = true;
            }
        }

        return registered;
    }

protected:
    ICustomAction() {}

    virtual ~ICustomAction() {}

private:
    ICustomAction(const ICustomAction&);
    ICustomAction& operator=(const ICustomAction&);

    static const int32_t INVALID_CUSTOM_ACTION_ID = -1;
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_ICUSTOM_ACTION_H_INCL__
