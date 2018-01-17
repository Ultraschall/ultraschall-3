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
#include <sstream>

#include "SaveChapterMarkersToProjectAction.h"
#include "Application.h"
#include "ProjectManager.h"
#include "FileManager.h"
#include "NotificationWindow.h"
#include "TimeUtilities.h"

namespace ultraschall {
   namespace reaper {
      
      static DeclareCustomAction<SaveChapterMarkersToProjectAction> action;
      
      ServiceStatus SaveChapterMarkersToProjectAction::Execute()
      {
         ServiceStatus status = SERVICE_FAILURE;
         
         const ProjectManager& projectManager = ProjectManager::Instance();
         Project currentProject = projectManager.CurrentProject();
         const std::string projectFolder = currentProject.FolderName();
         if(projectFolder.empty() == false)
         {
            const std::string projectName = currentProject.Name();
            if((projectName.empty() == false) && (ConfigureAssets() == true))
            {
               std::vector<std::string> errorMessages;
               if(ValidateChapterMarkers(errorMessages) == true)
               {
                  const std::string fullPath = FileManager::AppendPath(projectFolder, projectName + ".chapters.txt");
                  std::ofstream os(fullPath, std::ios::out);
                  if(os.is_open() == true)
                  {
                     for(size_t i = 0; i < chapters_.size(); i++)
                     {
                        const std::string timestamp = framework::SecondsToString(chapters_[i].Position());
                        const std::string item = timestamp + " " + chapters_[i].Name();
                        
                        os << item << std::endl;
                     }
                  }
                  else
                  {
                     NotificationWindow::Show("Failed to export chapter markers.", true);
                  }
                  
                  os.close();
                  
                  status = SERVICE_SUCCESS;
                  NotificationWindow::Show("The chapter markers have been saved successfully.");
               }
               else
               {
                  if(errorMessages.empty() == false)
                  {
                     std::ostringstream os;
                     os << "Ultraschall failed to validate chapter markers.";
                     os << "\r\n\r\n";
                     
                     for(size_t l = 0; l < errorMessages.size(); l++)
                     {
                        os << errorMessages[l];
                     }
                     
                     os << "\r\n\r\n";
                     
                     NotificationWindow::Show(os.str(), true);
                  }
               }
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
         
         return status;
      }
      
      bool SaveChapterMarkersToProjectAction::ConfigureAssets()
      {
         bool result = false;
         std::vector<std::string> messages;
         size_t invalidAssetCount = 0;
         
         ProjectManager& projectManager = ProjectManager::Instance();
         Project currentProject = projectManager.CurrentProject();
         if(Project::Validate(currentProject) == true)
         {
            chapters_ = currentProject.QueryAllMarkers();
            if(chapters_.empty() == true)
            {
               const std::string message = "No chapters have been set.";
               messages.push_back(message);
               invalidAssetCount++;
            }
            
            if(invalidAssetCount >= 1)
            {
               std::stringstream os;
               os << "Your project does not meet the minimum requirements for the export to continue.";
               os << "\r\n\r\n";
               os << "Specify at least one ID3v2 tag, a cover image or a chapter marker.";
               os << "\r\n\r\n";
               
               NotificationWindow::Show(os.str(), true);
               
               result = false;
            }
            else if(messages.size() > 0)
            {
               std::stringstream os;
               
               os << "Ultraschall has found the following non-critical issues and will continue after you close this message:\r\n\r\n";
               for(size_t i = 0; i < messages.size(); i++)
               {
                  os << (i + 1) << ") " << messages[i] << "\r\n";
               }
               
               os << "\r\n\r\n";
               
               NotificationWindow::Show(os.str(), false);
               
               result = true;
            }
            else
            {
               result = true;
            }
         }
         else
         {
            NotificationWindow::Show("The REAPER project must be saved before the export can continue", true);
            
            result = false;
         }
         
         return result;
      }
      
      void SaveChapterMarkersToProjectAction::ResetAssets()
      {
         chapters_.clear();
      }
      
      bool SaveChapterMarkersToProjectAction::ValidateChapterMarkers(std::vector<std::string>& errorMessages)
      {
         PRECONDITION_RETURN(chapters_.empty() == false, false);
         
         bool valid = true;
         errorMessages.clear();
         
         for(size_t i = 0; i < chapters_.size(); i++)
         {
            const Marker& current = chapters_[i];
            const std::string safeName = current.Name();
            const double safePosition = current.Position();
            
            ProjectManager& projectManager = ProjectManager::Instance();
            Project currentProject = projectManager.CurrentProject();
            if(currentProject.IsValidPosition(current.Position()) == false)
            {
               std::stringstream os;
               os << "Chapter marker '" << ((safeName.empty() == false) ? safeName : std::string("Unknown")) << "' is out of track range.";
               errorMessages.push_back(os.str());
               
               valid = false;
            }
            
            if(current.Name().empty() == true)
            {
               std::stringstream os;
               os << "Chapter marker at '" << framework::SecondsToString(safePosition) << "' has no name.";
               os << "\r\n";
               errorMessages.push_back(os.str());
               
               valid = false;
            }
         }
         
         return valid;
      }
      
   }}

