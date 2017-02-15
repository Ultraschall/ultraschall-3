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

#include <sstream>
#include <vector>
#include <fstream>

#include "SaveChapterMarkersAction.h"
#include "CustomActionFactory.h"
#include "Marker.h"
#include "ProjectManager.h"
#include "FileManager.h"
#include "NotificationWindow.h"
#include "TimeUtilities.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<SaveChapterMarkersAction> action;

ServiceStatus SaveChapterMarkersAction::Execute()
{
   ServiceStatus status = SERVICE_FAILURE;

   const ProjectManager& projectManager = ProjectManager::Instance();
   Project currentProject = projectManager.CurrentProject();

   std::string targetPath;

   const std::vector<Marker> tags = currentProject.QueryAllMarkers();
   if(tags.empty() == false)
   {
      const std::string initialFolder = currentProject.FolderName();
      const std::string projectName = currentProject.Name();
      if((initialFolder.empty() == false) && (projectName.empty() == false))
      {
         std::string targetPath = FileManager::BrowseForFolder("Export chapter markers...", initialFolder);
         if(targetPath.empty() == false)
         {
            targetPath = FileManager::AppendPath(targetPath, projectName + ".chapters.txt");
            status = SERVICE_SUCCESS;
         }
         else
         {
            NotificationWindow::Show("The export operation has been canceled.");
            status = SERVICE_FAILURE;
         }
      }
      else
      {
         NotificationWindow::Show("The project must be saved before the chapter marker export can run.");
         status = SERVICE_FAILURE;
      }
   }
   else
   {
      NotificationWindow::Show("The project does not contain any chapter markers.");
      status = SERVICE_FAILURE;
   }

   if(SERVICE_SUCCESS == status)
   {
      std::ofstream os(targetPath, std::ios::out);
      if(os.is_open() == true)
      {
         for(size_t i = 0; i < tags.size(); i++)
         {
            const std::string timestamp = framework::SecondsToString(tags[i].Position());
            const std::string item = timestamp + " " + tags[i].Name();
            
            os << item << std::endl;
         }
         
         os.close();
         
         NotificationWindow::Show("The chapter markers have been saved successfully.");
         status = SERVICE_SUCCESS;
      }
      else
      {
         NotificationWindow::Show("Failed to export chapter markers.", true);
         status = SERVICE_FAILURE;
      }
   }
   
   return status;
}

}}

