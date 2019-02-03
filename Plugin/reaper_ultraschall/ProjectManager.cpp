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

#include "ProjectManager.h"

namespace ultraschall { namespace reaper {

const Project ProjectManager::INVALID_PROJECT;

ProjectManager::ProjectManager() {}

ProjectManager::~ProjectManager() {}

ProjectManager& ProjectManager::Instance()
{
    static ProjectManager self;
    return self;
}

const Project& ProjectManager::CurrentProject() const
{
    ProjectReference currentProjectReference = CurrentProjectReference();
    return LookupProject(currentProjectReference);
}

ProjectReference ProjectManager::CurrentProjectReference() const
{
    return ReaperGateway::CurrentProject();
}

UnicodeString ProjectManager::CurrentProjectName() const
{
    UnicodeString name;

    const Project& currentProject = CurrentProject();
    if(Project::Validate(currentProject) == true)
    {
        // TODO check whether reaper uses unicode or ansi
        name = H2U(currentProject.Name());
    }

    return name;
}

bool ProjectManager::InsertProject(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, false);

    return projectReferences_
        .insert(ProjectReferenceDictionary::value_type(projectReference, Project(projectReference)))
        .second;
}

const Project& ProjectManager::LookupProject(ProjectReference projectReference) const
{
    PRECONDITION_RETURN(projectReference != nullptr, INVALID_PROJECT);

    const ProjectReferenceDictionary::const_iterator projectReferenceIterator
        = projectReferences_.find(projectReference);
    if(projectReferenceIterator != projectReferences_.end())
    {
        return projectReferenceIterator->second;
    }

    return INVALID_PROJECT;
}

void ProjectManager::RemoveProject(ProjectReference projectReference)
{
    PRECONDITION(projectReference != nullptr);

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

}} // namespace ultraschall::reaper
