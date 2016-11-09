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

#include <StringUtilities.h>

#include "Project.h"
#include "ReaperEntryPoints.h"
#include "FileManager.h"

namespace ultraschall {
namespace reaper {

Project::Project() :
   externalReference_(0)
{
}

Project::Project(void* externalReference) :
   externalReference_(externalReference)
{

}

Project::~Project()
{
   externalReference_ = 0;
}

Project::Project(const Project& rhs)
{
   *this = rhs;
}

Project& Project::operator=(const Project& rhs)
{
   if(this != &rhs)
   {
      externalReference_ = rhs.externalReference_;
      chapterMarkers_ = rhs.chapterMarkers_;
      editMarkers_ = rhs.editMarkers_;
      shownoteMarkers_ = rhs.shownoteMarkers_;
   }

   return *this;
}

bool Project::Validate(const Project& project)
{
   return project.externalReference_ != 0;
}

std::string Project::FullPathName() const
{
   PRECONDITION_RETURN(externalReference_ != 0, std::string());

   std::string result;

   static const size_t MAX_REAPER_STRING_BUFFER_SIZE = 4096;
   char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
   int index = 0;
   ReaProject* externalReference = reaper_api::EnumProjects(index++, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
   while((externalReference != 0) && (result.empty() == true))
   {
      if(externalReference == externalReference_)
      {
         result = buffer;
      }

      externalReference = reaper_api::EnumProjects(index++, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
   }

   return result;
}

std::string Project::FolderName() const
{
   std::string result;

   const std::string fullPath = FullPathName();
   if(fullPath.empty() == false)
   {
      const char pathSeparator = FileManager::PathSeparator();
      const std::vector<std::string> pathComponents = framework::split(fullPath, pathSeparator);
      if(pathComponents.empty() == false)
      {
         for(size_t i = 0; i < pathComponents.size() - 1; i++)
         {
            result += pathComponents[i];
            if(i < pathComponents.size() - 2)
            {
               result += pathSeparator;
            }
         }
      }
   }

   return result;
}

std::string Project::FileName() const
{
   std::string result;

   const std::string fullPath = FullPathName();
   if(fullPath.empty() == false)
   {
      const char pathSeparator = FileManager::PathSeparator();
      const std::vector<std::string> pathComponents = framework::split(fullPath, pathSeparator);
      if(pathComponents.empty() == false)
      {
         result = pathComponents[pathComponents.size() - 1];
      }
   }

   return result;
}

std::string Project::Name() const
{
   PRECONDITION_RETURN(externalReference_ != 0, std::string());

   std::string result;

   const std::string file = FileName();
   if(file.empty() == false)
   {
      result = file.substr(0, file.find('.', 0));
   }

   return result;
}

}
}

