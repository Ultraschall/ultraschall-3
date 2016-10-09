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

#include "ProjectManager.h"
#include "ReaperEntryPoints.h"

namespace framework = ultraschall::framework;

namespace ultraschall {
namespace reaper {

ProjectManager::ProjectManager()
{
}

ProjectManager::~ProjectManager()
{
}

ProjectManager& ProjectManager::Instance()
{
   static ProjectManager self;
   return self;
}

Project ProjectManager::CurrentProject() const
{
   std::lock_guard<std::recursive_mutex> lock(projectsLock_);

   return Project(reaper_api::EnumProjects(-1, 0, 0));
}

std::string ProjectManager::CurrentProjectName() const
{
   std::string result;

   std::lock_guard<std::recursive_mutex> lock(projectsLock_);

   Project currentProject = CurrentProject();
   if(Project::Validate(currentProject) == true)
   {
      return currentProject.Name();
   }

   return result;
}

void ProjectManager::AddProject(const Project& project)
{
   PRECONDITION(Project::Validate(project) == true);

   std::lock_guard<std::recursive_mutex> lock(projectsLock_);

   const std::string projectPath = project.FullPathName();
   if(projectPath.empty() == false)
   {
      if(projects_.empty() == false)
      {
         std::map<std::string, Project>::const_iterator projectIterator = projects_.find(projectPath);
         if(projects_.end() != projectIterator)
         {
            projects_.erase(projectPath);
         }
      }

//      projects_.insert(std::pair<std::string, Project>(projectPath, project));
   }
}

void ProjectManager::RemoveProject(const Project& project)
{
   PRECONDITION(Project::Validate(project) == true);

   std::lock_guard<std::recursive_mutex> lock(projectsLock_);

   if(projects_.empty() == false)
   {
      const std::string projectPath = project.FullPathName();
      if(projectPath.empty() == false)
      {
         std::map<std::string, Project>::const_iterator projectIterator = projects_.find(projectPath);
         if(projects_.end() != projectIterator)
         {
            projects_.erase(projectPath);
         }
      }
   }
}

}
}
