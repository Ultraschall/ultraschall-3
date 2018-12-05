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
#include "Framework.h"
#include "ProjectManager.h"
#include "ReaperEntryPoints.h"

namespace framework = ultraschall::framework;

namespace ultraschall {
namespace reaper {

const Project ProjectManager::INVALID_PROJECT;

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

const Project& ProjectManager::CurrentProject() const
{
   std::lock_guard<std::recursive_mutex> lock(projectReferencesLock_);

   ProjectHandle currentProjectReference = CurrentProjectReference();
   return LookupProject(currentProjectReference);
}

ProjectHandle ProjectManager::CurrentProjectReference() const
{
   std::lock_guard<std::recursive_mutex> lock(projectReferencesLock_);

   return reaper_api::EnumProjects(-1, 0, 0);
}

std::string ProjectManager::CurrentProjectName() const
{
   std::string result;

   std::lock_guard<std::recursive_mutex> lock(projectReferencesLock_);

   const Project& currentProject = CurrentProject();
   if(Project::Validate(currentProject) == true)
   {
      result = currentProject.Name();
   }

   return result;
}

bool ProjectManager::InsertProject(ProjectHandle projectReference)
{
   PRECONDITION_RETURN(projectReference != 0, false);

   std::lock_guard<std::recursive_mutex> lock(projectReferencesLock_);

   return projectReferences_.insert(ProjectReferenceDictionary::value_type(projectReference, Project(projectReference))).second;
}

const Project& ProjectManager::LookupProject(ProjectHandle projectReference) const
{
   PRECONDITION_RETURN(projectReference != 0, INVALID_PROJECT);

   std::lock_guard<std::recursive_mutex> lock(projectReferencesLock_);
   const ProjectReferenceDictionary::const_iterator projectReferenceIterator = projectReferences_.find(projectReference);
   if(projectReferenceIterator != projectReferences_.end())
   {
      return projectReferenceIterator->second;
   }

   return INVALID_PROJECT;
}

void ProjectManager::RemoveProject(ProjectHandle projectReference)
{
   PRECONDITION(projectReference != 0);

   std::lock_guard<std::recursive_mutex> lock(projectReferencesLock_);

   if(projectReferences_.empty() == false)
   {
      ProjectReferenceDictionary::const_iterator projectIterator = projectReferences_.find(projectReference);
      if(projectReferences_.end() != projectIterator)
      {
         projectReferences_.erase(projectReference);
      }
   }
}

void ProjectManager::RemoveAllProjects()
{
   while(projectReferences_.empty() == false)
   {
      ProjectReferenceDictionary::const_iterator projectIterator = projectReferences_.begin();
      if(projectReferences_.end() != projectIterator)
      {
         projectReferences_.erase(projectIterator);
      }
   }

}

}
}
