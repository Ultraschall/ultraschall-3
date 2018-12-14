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

#ifndef __ULTRASCHALL_REAPER_PROJECT_MANAGER_H_INCL__
#define __ULTRASCHALL_REAPER_PROJECT_MANAGER_H_INCL__

#include <mutex>
#include <map>

#include "Project.h"

namespace ultraschall {
namespace reaper {

class ProjectManager
{
public:
   static const Project INVALID_PROJECT;

   static ProjectManager& Instance();

   const Project& CurrentProject() const;
   ProjectHandle CurrentProjectReference() const;
   std::string CurrentProjectName() const;

   bool InsertProject(ProjectHandle projectReference);
   const Project& LookupProject(ProjectHandle projectReference) const;
   void RemoveProject(ProjectHandle projectReference);
   void RemoveAllProjects();

protected:
   virtual ~ProjectManager();

private:
   ProjectManager();

   ProjectManager(const ProjectManager&);
   ProjectManager& operator=(const ProjectManager&);

   typedef std::map<void*, Project> ProjectReferenceDictionary;
   ProjectReferenceDictionary projectReferences_;
   mutable std::recursive_mutex projectReferencesLock_;
};

}
}

#endif // #ifndef __ULTRASCHALL_REAPER_PROJECT_MANAGER_H_INCL__
