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

#include "SaveChaptersAction.h"
#include "Application.h"
#include "FileManager.h"
#include "MessageBox.h"

namespace ultraschall { namespace reaper {

static CustomAction<SaveChaptersAction> action;

const std::string SaveChaptersAction::UniqueId()
{
   static const std::string uniqueId("ULTRASCHALL_SAVE_CHAPTERS");
   return uniqueId;
}

const std::string SaveChaptersAction::Name()
{
   static const std::string name("ULTRASCHALL Save chapters markers");
   return name;
}

const ServiceStatus SaveChaptersAction::Execute()
{
   ServiceStatus status = SERVICE_FAILURE;
   
   const Application& application = Application::Instance();
   const std::vector<ProjectMarker> projectMarkers = application.ProjectMarkers();
   if(projectMarkers.empty() == false)
   {
      const std::string projectFolder = application.ProjectFolder();
      if(projectFolder.empty() == false)
      {
         std::string exportPath = FileManager::BrowseForFolder("Kapitelmarken speichern...", projectFolder);
         
         
//         std::string projectName = projectFile.substr(0, projectFile.find('.', 0));
//         if(projectName.empty() == false)
//         {
//            projectName = FileManager::AppendPath(projectFile, ".mp4chaps");
//            std::string exportPath = FileManager::BrowseForFolder("Kapitelmarken speichern...", projectName);
//            
//            if(exportPath.empty() == false)
//            {
//               exportPath = FileManager::AppendPath(exportPath, (projectName + ".mp4chaps"));
//               std::ofstream output(exportPath, std::ios::out);
//               for(size_t i = 0; i < projectMarkers.size(); i++)
//               {
//                  const std::string timestamp = application.TimestampToString(projectMarkers[i].Position());
//                  const std::string entry = timestamp + " " + projectMarkers[i].Name();
//                  output << entry << std::endl;
//               }
//               
//               output.close();
//               
//               status = SERVICE_SUCCESS;
//            }
//         }
      }
      else
      {
         MessageBox::Show("Es ist kein Projekt geöffnet.");
      }
   }
   else
   {
      MessageBox::Show("Es sind keine Kapitelmarken definiert.");
   }
   
   return status;
}

}}

