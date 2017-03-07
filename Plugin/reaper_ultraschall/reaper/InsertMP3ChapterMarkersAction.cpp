////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 Ultraschall (http://ultraschall.fm)
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

#include <Framework.h>
#include <StringUtilities.h>

#include "InsertMP3ChapterMarkersAction.h"
#include "CustomActionFactory.h"
#include "FileManager.h"
#include "MP3Properties.h"
#include "NotificationWindow.h"

namespace ultraschall {
   namespace reaper {
      
static DeclareCustomAction<InsertMP3ChapterMarkersAction> action;

ServiceStatus InsertMP3ChapterMarkersAction::Execute()
{
   ProjectManager& projectManager = ProjectManager::Instance();
   Project currentProject = projectManager.CurrentProject();
   
   const std::string projectFolder = currentProject.FolderName();
   const std::string projectName = currentProject.Name();
   if((projectFolder.empty() == false) && (projectName.empty() == false))
   {
      std::string targetName = FileManager::AppendPath(projectFolder, projectName) + ".mp3";
      if(FileManager::FileExists(targetName) == false)
      {
         targetName = FileManager::BrowseForMP3Files("Select MP3 File...");
      }
         
      if(targetName.empty() == false)
      {
         int successfulActions = 0;

         const std::string projectNotes = currentProject.Notes();
         if(projectNotes.empty() == false)
         {
            if(InsertMP3Properties(targetName, projectNotes) == true)
            {
               successfulActions++;
            }
            else
            {
               NotificationWindow::Show("Failed to insert ID3V2 tags.", true);
            }
         }

         std::vector<std::string> imageNames;
         imageNames.push_back(FileManager::AppendPath(projectFolder, "cover") + ".jpg");
         imageNames.push_back(FileManager::AppendPath(projectFolder, "cover") + ".jpeg");
         imageNames.push_back(FileManager::AppendPath(projectFolder, "cover") + ".png");
         imageNames.push_back(FileManager::AppendPath(projectFolder, projectName) + ".jpg");
         imageNames.push_back(FileManager::AppendPath(projectFolder, projectName) + ".jpeg");
         imageNames.push_back(FileManager::AppendPath(projectFolder, projectName) + ".png");
         const size_t imageIndex = FileManager::FileExists(imageNames);
         if(imageIndex != -1)
         {
            if(InsertMP3CoverPicture(targetName, imageNames[imageIndex]) == true)
            {
               successfulActions++;
            }
            else
            {
               NotificationWindow::Show("Failed to insert cover art.", true);
            }
         }
            
         std::vector<Marker> tags = currentProject.QueryAllMarkers();
         if(tags.empty() == false)
         {
            if(InsertMP3Tags(targetName, tags) == true)
            {
               successfulActions++;
            }
            else
            {
               NotificationWindow::Show("Failed to export chapter markers.", true);
            }
         }

         if(successfulActions > 0)
         {
            NotificationWindow::Show("The MP3 file has been updated successfully.");
         }
      }
      else
      {
         NotificationWindow::Show("The export operation has been canceled.");
      }
   }
   else
   {
      NotificationWindow::Show("Please save the project and restart the export function.");
   }
   
   return SERVICE_SUCCESS;
}
      
}}


