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

#include <TranscriptItem.h>
#include <StringUtilities.h>

#include "InsertTranscriptAction.h"
#include "Application.h"
#include "FileManager.h"
#include "MessageBox.h"

namespace ultraschall { namespace reaper {

static CustomAction<InsertTranscriptAction> action;

const char* InsertTranscriptAction::UniqueId()
{
   return "ULTRASCHALL_INSERT_TRANSCRIPT";
}

const ServiceStatus InsertTranscriptAction::Execute()
{
   ServiceStatus status = SERVICE_FAILURE;
   
   std::string path = FileManager::BrowseForFiles(fileBrowserTitleId_);
   PRECONDITION_RETURN(path.empty() == false, SERVICE_FAILURE);

   std::vector<framework::TranscriptItem> items;
   const Application& application = Application::Instance();

   std::ifstream input(path);
   std::string entry;
   while(std::getline(input, entry))
   {
      std::vector<std::string> tokens = framework::split(entry, ']');
      if(tokens.size() == 2)
      {
         std::string script = framework::trim(tokens[1]);
         tokens = framework::split(tokens[0], ' ');
         if(tokens.size() == 2)
         {
            std::string timestamp = tokens[0].substr(1);
            const double position = application.StringToTimestamp(timestamp);
            std::string speaker = tokens[1];
            
            items.push_back(framework::TranscriptItem(speaker, position, script));
         }
      }
   }

   size_t addedItemCount = 0;
   for(size_t i = 0; i < items.size(); i++)
   {
      if(application.InsertTransriptItem(items[i]))
      {
         addedItemCount++;
      }
   }

   input.close();
   
   if(items.size() == addedItemCount)
   {
      MessageBox::Show(successMessageId_);
      status = SERVICE_SUCCESS;
   }
   else
   {
      MessageBox::Show(failureMessageId_);
   }
   
   return status;
}

}}

