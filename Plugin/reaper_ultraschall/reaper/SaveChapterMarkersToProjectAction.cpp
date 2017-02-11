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

#include <string>
#include <vector>
#include <fstream>

#include "SaveChapterMarkersToProjectAction.h"
#include "Application.h"
#include "ProjectManager.h"
#include "FileManager.h"
#include "NotificationWindow.h"

namespace ultraschall {
   namespace reaper {

static DeclareCustomAction<SaveChapterMarkersToProjectAction> action;

ServiceStatus SaveChapterMarkersToProjectAction::Execute()
{
   ServiceStatus status = SERVICE_FAILURE;
   
   const ProjectManager& projectManager = ProjectManager::Instance();
   Project currentProject = projectManager.CurrentProject();
   const std::vector<Marker> chapterMarkers = currentProject.ChapterMarkers();
   if(chapterMarkers.empty() == false)
   {
      const std::string projectFolder = currentProject.FolderName();
      if(projectFolder.empty() == false)
      {
         const std::string projectName = currentProject.Name();
         if(projectName.empty() == false)
         {
            const std::string fullPath = FileManager::AppendPath(projectFolder, projectName + ".chapters.txt");
            std::ofstream output(fullPath, std::ios::out);
            for(size_t i = 0; i < chapterMarkers.size(); i++)
            {
               // TODO
               //const std::string timestamp = application.TimestampToString(chapterMarkers[i].Position());
               //const std::string entry = timestamp + " " + chapterMarkers[i].Name();
               //output << entry << std::endl;
            }

            output.close();

            status = SERVICE_SUCCESS;
            NotificationWindow::Show("The chapter markers have been saved successfully.");
         }
         else
         {
            NotificationWindow::Show("The project has no name yet. Please save the project and try again.");
         }
      }
      else
      {
         NotificationWindow::Show("The project has no name yet. Please save the project and try again.");
      }
   }
   else
   {
      NotificationWindow::Show("No chapter markers have been found.");
   }
   
   return status;
}

}}

