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

#include <vector>
#include <fstream>

#include "SaveChaptersToProjectAction.h"
#include "Application.h"
#include "MessageBox.h"

namespace ultraschall { namespace reaper {

static CustomAction<SaveChaptersToProjectAction> action;

const std::string SaveChaptersToProjectAction::UniqueId()
{
   static const std::string uniqueId("ULTRASCHALL_SAVE_CHAPTERS_TO_PROJECT");
   return uniqueId;
}

const std::string SaveChaptersToProjectAction::Name()
{
   static const std::string name("ULTRASCHALL Save chapters markers to project folder");
   return name;
}

const ServiceStatus SaveChaptersToProjectAction::Execute()
{
   ServiceStatus status = SERVICE_FAILURE;
   
   const Application& application = Application::Instance();
   const std::vector<ProjectMarker> projectMarkers = application.ProjectMarkers();
   if(projectMarkers.empty() == false)
   {
      const std::string path = Path();
      if(path.empty() == false)
      {
         std::ofstream output(path, std::ios::out);
         for(size_t i = 0; i < projectMarkers.size(); i++)
         {
            const std::string timestamp = application.TimestampToString(projectMarkers[i].Position());
            const std::string entry = timestamp + " " + projectMarkers[i].Name();
            output << entry << std::endl;
         }

         output.close();
         
         status = SERVICE_SUCCESS;
      }
   }
   else
   {
      MessageBox::Show("Es sind keine Kapitelmarken definiert.");
   }
   
   return status;
}

const std::string SaveChaptersToProjectAction::Path()
{
   std::string path;

   const Application& application = Application::Instance();
   const std::string exportPath = application.ExportPath();
   if(exportPath.empty() == false)
   {
      const std::string projectPath = application.ProjectPath();
      if(projectPath.empty() == false)
      {
#ifdef WIN32
         const char PATH_DELIMITER_CHAR = '\\';
#else
         const char PATH_DELIMITER_CHAR = '/';
#endif
         const std::vector<std::string> pathComponents = Application::SplitString(projectPath, PATH_DELIMITER_CHAR);
         if(pathComponents.empty() == false)
         {
            const std::string projectFile = pathComponents[pathComponents.size() - 1];
            if(projectFile.empty() == false)
            {
               const std::string projectName = projectFile.substr(0, projectFile.find('.', 0));
               if(projectName.empty() == false)
               {
                  path = exportPath + PATH_DELIMITER_CHAR + projectName + ".mp4chaps";
               }
            }
         }
      }
   }

   return path;
}

}}

