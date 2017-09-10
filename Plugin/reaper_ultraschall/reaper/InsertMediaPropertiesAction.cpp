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

#include "InsertMediaPropertiesAction.h"
#include "CustomActionFactory.h"
#include "FileManager.h"
#include "MP3Properties.h"
#include "NotificationWindow.h"
#include "ITagWriter.h"

namespace ultraschall {
   namespace reaper {
      
static DeclareCustomAction<InsertMediaPropertiesAction> action;

ServiceStatus InsertMediaPropertiesAction::Execute()
{
   ProjectManager& projectManager = ProjectManager::Instance();
   Project currentProject = projectManager.CurrentProject();
   const std::string targetName = FindTargetFile(currentProject);
   if(targetName.empty() == false)
   {
      ITagWriter* pTagWriter = CreateTagWriter(targetName);
      if(pTagWriter != nullptr)
      {
         int successfulActions = 0;
         
         const std::string projectNotes = currentProject.Notes();
         if(projectNotes.empty() == false)
         {
            if(pTagWriter->InsertStandardProperties(targetName, projectNotes) == true)
            {
               successfulActions++;
            }
            else
            {
               NotificationWindow::Show("Failed to insert standard properties.", true);
            }
         }
         else
         {
            NotificationWindow::Show("Failed to read standard properties.", true);
         }
            
         const std::string coverImage = FindCoverImage(currentProject);
         if(coverImage.empty() == false)
         {
            if(pTagWriter->InsertCoverImage(targetName, coverImage) == true)
            {
               successfulActions++;
            }
            else
            {
               NotificationWindow::Show("Failed to insert cover image.", true);
            }
         }
         else
         {
            NotificationWindow::Show("Failed to read cover image.", true);
         }
         
         const std::vector<Marker> tags = currentProject.QueryAllMarkers();
         if(tags.empty() == false)
         {
            if(pTagWriter->InsertChapterMarkers(targetName, tags) == true)
            {
               successfulActions++;
            }
            else
            {
               NotificationWindow::Show("Failed to export chapter markers.", true);
            }
         }
         else
         {
            NotificationWindow::Show("Failed to read chapter markers.", true);
         }

         framework::SafeRelease(pTagWriter);
         
         if(successfulActions > 0)
         {
            NotificationWindow::Show("The MP3 file has been updated successfully.");
         }
      }
   }
   
   return SERVICE_SUCCESS;
}
     
std::string InsertMediaPropertiesAction::FindTargetFile(const Project& project)
{
   const std::string projectFolder = project.FolderName();
   const std::string projectName = project.Name();
   
   PRECONDITION_RETURN(projectFolder.empty() == false, std::string());
   PRECONDITION_RETURN(projectName.empty() == false, std::string());
   
   std::string targetName = FileManager::AppendPath(projectFolder, projectName) + ".mp3";
   if(FileManager::FileExists(targetName) == false)
   {
      targetName = FileManager::AppendPath(projectFolder, projectName) + ".mp4";
      if(FileManager::FileExists(targetName) == false)
      {
         targetName = FileManager::BrowseForMP3Files("Select Output File...");
      }
      else
      {
         targetName.clear();
      }
   }
   
   return targetName;
}

std::string InsertMediaPropertiesAction::FindCoverImage(const Project& project)
{
   const std::string projectFolder = project.FolderName();
   const std::string projectName = project.Name();
  
   PRECONDITION_RETURN(projectFolder.empty() == false, std::string());
   PRECONDITION_RETURN(projectName.empty() == false, std::string());

   std::string coverImage;
   
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
      coverImage = imageNames[imageIndex];
   }
   
   return coverImage;
}

ITagWriter* InsertMediaPropertiesAction::CreateTagWriter(const std::string& targetName)
{
   PRECONDITION_RETURN(targetName.empty() == false, nullptr);
   PRECONDITION_RETURN(targetName.length() > 4, nullptr);

   ITagWriter* pTagWriter = nullptr;
   
   const std::string cookedTargetName = NormalizeTargetName(targetName);
   const size_t extensionOffset = targetName.find(".");
   if(extensionOffset != std::string::npos)
   {
      const std::string fileExtension = targetName.substr(extensionOffset + 1, targetName.length() - extensionOffset);
      if(fileExtension.empty() == false)
      {
         if(fileExtension == "mp3")
         {
            pTagWriter = new MP3TagWriter();
         }
         else if(fileExtension == "mp4")
         {
            pTagWriter = new MP4TagWriter();
         }
      }
   }
      
   return pTagWriter;
}
      
std::string InsertMediaPropertiesAction::NormalizeTargetName(const std::string& targetName)
{
   std::string firstStage = targetName;
   std::string secondStage = framework::StringTrimRight(firstStage);
   return framework::StringLowercase(secondStage);
}
      
}}


