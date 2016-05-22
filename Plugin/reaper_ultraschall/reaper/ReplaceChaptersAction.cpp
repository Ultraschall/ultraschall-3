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

#include <TextFileReader.h>
#include <StringUtilities.h>

#include "ReplaceChaptersAction.h"
#include "Application.h"
#include "FileManager.h"
#include "NotificationWindow.h"

namespace ultraschall { namespace reaper {

static DeclareCustomAction<ReplaceChaptersAction> action;

const char* ReplaceChaptersAction::UniqueId()
{
   return "ULTRASCHALL_REPLACE_CHAPTERS";
}

const ServiceStatus ReplaceChaptersAction::Execute()
{
   ServiceStatus status = SERVICE_FAILURE;
   
   const std::string path = FileManager::BrowseForFiles(fileBrowserTitleId_);
   PRECONDITION_RETURN(path.empty() == false, SERVICE_FAILURE);

   const Application& application = Application::Instance();
   std::vector<framework::ChapterMarker> chapterMarkers;

   const std::vector<std::string> lines = framework::TextFileReader::ReadLines(path);
   for(const std::string& line : lines)
   {
      const std::vector<std::string> items = framework::split(line, ' ');
      if(items.size() > 1)
      {
         const double timestamp = application.StringToTimestamp(items[0]);
         std::string name = items[1];
         for(size_t i = 2; i < items.size(); i++)
         {
            name += " " + items[i];
         }

         chapterMarkers.push_back(framework::ChapterMarker(timestamp, name));
      }
   }

   application.DeleteAllChapterMarkers();
   
   size_t replacedChapterMarkers = 0;
   for(size_t i = 0; i < chapterMarkers.size(); i++)
   {
      const int32_t index = application.SetChapterMarker(chapterMarkers[i]);
      if(index > -1)
      {
         replacedChapterMarkers++;
      }
   }

   if(chapterMarkers.size() == replacedChapterMarkers)
   {
      NotificationWindow::Show(successMessageId_);
      status = SERVICE_SUCCESS;
   }
   else
   {
      NotificationWindow::Show(failureMessageId_);
   }
   
   return status;
}

}}

