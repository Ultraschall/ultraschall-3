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

#include <string>
#include <vector>
#include <fstream>

#include "SaveChaptersAction.h"
#include "Application.h"
#include "FileManager.h"
#include "NotificationWindow.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<SaveChaptersAction> action;

const char* SaveChaptersAction::UniqueId()
{
   return "ULTRASCHALL_SAVE_CHAPTERS";
}

const ServiceStatus SaveChaptersAction::Execute()
{
   ServiceStatus status = SERVICE_FAILURE;
   
   const Application& application = Application::Instance();
   const std::vector<framework::ChapterMarker> chapterMarkers = application.ChapterMarkers();
   if(chapterMarkers.empty() == false)
   {
      const std::string projectFolder = application.GetProjectFolderName();
      if(projectFolder.empty() == false)
      {
         std::string targetPath = FileManager::BrowseForFolder(fileBrowserTitleId_, projectFolder);
         if(targetPath.empty() == false)
         {
            const std::string projectName = application.GetProjectName();
            if(projectName.empty() == false)
            {
               targetPath = FileManager::AppendPath(targetPath, projectName + ".chapters.txt");
               std::ofstream output(targetPath, std::ios::out);
               for(size_t i = 0; i < chapterMarkers.size(); i++)
               {
                  const std::string timestamp = application.TimestampToString(chapterMarkers[i].Position());
                  const std::string entry = timestamp + " " + chapterMarkers[i].Name();
                  output << entry << std::endl;
               }

               output.close();
               
               status = SERVICE_SUCCESS;
               NotificationWindow::Show(successMessageId_);
            }
            
            if(ServiceFailed(status))
            {
               NotificationWindow::Show(failureMessageId_);
            }
         }
         else
         {
            NotificationWindow::Show(saveOperationCanceledId_);
         }
      }
      else
      {
         NotificationWindow::Show(noProjectNameMessageId_);
      }
   }
   else
   {
      NotificationWindow::Show(notFoundMessageId_);
   }
   
   return status;
}

}}

