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

#include "ReplaceChaptersAction.h"
#include "Application.h"
#include "FileManager.h"

namespace ultraschall { namespace reaper {

static CustomAction<ReplaceChaptersAction> action;

const std::string ReplaceChaptersAction::UniqueId()
{
   static const std::string uniqueId("ULTRASCHALL_REPLACE_CHAPTERS");
   return uniqueId;
}

const std::string ReplaceChaptersAction::Name()
{
   static const std::string name("ULTRASCHALL Replace chapter markers");
   return name;
}

const ServiceStatus ReplaceChaptersAction::Execute()
{
   ServiceStatus status = SERVICE_FAILURE;
   
   std::string path = FileManager::BrowseForFiles("Kapitelmarken ersetzen...");
   PRECONDITION_RETURN(path.empty() == false, SERVICE_FAILURE);

   std::vector<ProjectMarker> projectMarkers;
   const Application& application = Application::Instance();

   std::ifstream input(path);
   std::string entry;
   while(std::getline(input, entry))
   {
      const std::vector<std::string> items = Application::SplitString(entry, ' ');
      if(items.size() > 1)
      {
         const double timestamp = application.StringToTimestamp(items[0]);
         std::string name = items[1];
         for(size_t i = 2; i < items.size(); i++)
         {
            name += " " + items[i];
         }

         projectMarkers.push_back(ProjectMarker(timestamp, name));
      }
   }

   application.DeleteAllProjectMarkers();
   
   for(size_t i = 0; i < projectMarkers.size(); i++)
   {
      int32_t index = application.SetProjectMarker(projectMarkers[i]);
      if(index > -1)
      {
         status = SERVICE_SUCCESS;
      }
   }

   input.close();
   
   return status;
}

}}

