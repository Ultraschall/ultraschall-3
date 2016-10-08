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

#include "SaveChaptersToProjectAction.h"
#include "Application.h"
#include "FileManager.h"
#include "NotificationWindow.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<SaveChaptersToProjectAction> action;

SaveChaptersToProjectAction::SaveChaptersToProjectAction()
{
   framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
   ServiceStatus status = resourceManager.RegisterLocalizedString(actionNameId_);
   if(ServiceSucceeded(status))
   {
      resourceManager.SetLocalizedString(actionNameId_, "en-EN", "ULTRASCHALL: Save chapter markers to project folder");
      resourceManager.SetLocalizedString(actionNameId_, "de-DE", "ULTRASCHALL: Kapitelmarken im Projektverzeichnis speichern");
   }

   status = resourceManager.RegisterLocalizedString(successMessageId_);
   if(ServiceSucceeded(status))
   {
      resourceManager.SetLocalizedString(successMessageId_, "en-EN", "The chapter markers have been saved successfully.");
      resourceManager.SetLocalizedString(successMessageId_, "de-DE", "Die Kapitelmarken wurden erfolgreich gespeichert.");
   }

   status = resourceManager.RegisterLocalizedString(failureMessageId_);
   if(ServiceSucceeded(status))
   {
      resourceManager.SetLocalizedString(failureMessageId_, "en-EN", "The chapter markers could not be saved.");
      resourceManager.SetLocalizedString(failureMessageId_, "de-DE", "Die Kapitelmarken konnten nicht gespeichert werden.");
   }

   status = resourceManager.RegisterLocalizedString(notFoundMessageId_);
   if(ServiceSucceeded(status))
   {
      resourceManager.SetLocalizedString(notFoundMessageId_, "en-EN", "No chapter markers have been found.");
      resourceManager.SetLocalizedString(notFoundMessageId_, "de-DE", "Es wurden keine Kapitelmarken gefunden.");
   }

   status = resourceManager.RegisterLocalizedString(noProjectNameMessageId_);
   if(ServiceSucceeded(status))
   {
      resourceManager.SetLocalizedString(noProjectNameMessageId_, "en-EN", "The project has no name yet. Please save the project and try again.");
      resourceManager.SetLocalizedString(noProjectNameMessageId_, "de-DE", "Das Projekt hat noch keinen Namen und muss zuerst gespeichert werden");
   }
}

SaveChaptersToProjectAction::~SaveChaptersToProjectAction()
{
   framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
   resourceManager.UnregisterLocalizedString(actionNameId_);
   resourceManager.UnregisterLocalizedString(successMessageId_);
   resourceManager.UnregisterLocalizedString(failureMessageId_);
   resourceManager.UnregisterLocalizedString(notFoundMessageId_);
   resourceManager.UnregisterLocalizedString(noProjectNameMessageId_);
}

const char* SaveChaptersToProjectAction::UniqueId()
{
   return "ULTRASCHALL_SAVE_CHAPTERS_TO_PROJECT";
}

ServiceStatus SaveChaptersToProjectAction::CreateCustomAction(ICustomAction*& pCustomAction)
{
   pCustomAction = new SaveChaptersToProjectAction();
   PRECONDITION_RETURN(pCustomAction != 0, SERVICE_FAILURE);
   return SERVICE_SUCCESS;
}

const char* SaveChaptersToProjectAction::LocalizedName() const
{
   framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
   return resourceManager.GetLocalizedString(actionNameId_);
}

ServiceStatus SaveChaptersToProjectAction::Execute()
{
   ServiceStatus status = SERVICE_FAILURE;
   
   const Application& application = Application::Instance();
   const std::vector<framework::ChapterMarker> chapterMarkers = application.ChapterMarkers();
   if(chapterMarkers.empty() == false)
   {
      const std::string path = Path();
      if(path.empty() == false)
      {
         std::ofstream output(path, std::ios::out);
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

std::string SaveChaptersToProjectAction::Path()
{
   std::string path;

   const Application& application = Application::Instance();
   const std::string projectFolder = application.GetProjectFolderName();
   if(projectFolder.empty() == false)
   {
      const std::string projectName = application.GetProjectName();
      if(projectName.empty() == false)
      {
         path = FileManager::AppendPath(projectFolder, projectName + ".chapters.txt");
      }
   }

   return path;
}

}}

