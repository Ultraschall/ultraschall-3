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

#include <TextFileReader.h>
#include <StringUtilities.h>
#include <ResourceManager.h>

#include "InsertChapterMarkersAction.h"
#include "CustomActionFactory.h"
#include "Marker.h"
#include "ProjectManager.h"
#include "FileManager.h"
#include "NotificationWindow.h"
#include "TimeUtilities.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<InsertChapterMarkersAction> action;

ServiceStatus InsertChapterMarkersAction::Execute()
{
   ServiceStatus status = SERVICE_FAILURE;
   
   const std::string path = FileManager::BrowseForFiles("Import chapter markers...");
   PRECONDITION_RETURN(path.empty() == false, SERVICE_FAILURE);

   const ProjectManager& projectManager = ProjectManager::Instance();
   Project currentProject = projectManager.CurrentProject();
   
   std::vector<Marker> tags;

   const std::vector<std::string> lines = framework::TextFileReader::ReadLines(path);
   for(const std::string& line : lines)
   {
      const std::vector<std::string> items = framework::StringTokenize(line, ' ');
      if(items.size() > 0)
      {
         const double position = framework::StringToSeconds(items[0]);
         std::string name;
         if(items.size() > 1)
         {
            name = items[1];
         }
         
         for(size_t i = 2; i < items.size(); i++)
         {
            name += " " + items[i];
         }
         
         tags.push_back(Marker(position, name, 0));
      }
   }
   
   size_t addedTags = 0;
   for(size_t i = 0; i < tags.size(); i++)
   {
      if(currentProject.InsertChapterMarker(tags[i].Name(), tags[i].Position()) == true)
      {
         addedTags++;
      }
   }

   if(tags.size() == addedTags)
   {
      NotificationWindow::Show("The chapter markers have been added successfully.");
      status = SERVICE_SUCCESS;
   }
   else
   {
      NotificationWindow::Show("The chapter markers could not be added.");
   }
   
   return status;
}

}}

