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
#include <fstream>
#include <cstdlib>

#include <StringUtilities.h>

#include "Configuration.h"
#include "Application.h"
#include "FileManager.h"

namespace ultraschall { namespace reaper {
   
Configuration::Configuration()
{
   Read();
}
   
Configuration::~Configuration()
{
}
   
Configuration& Configuration::Instance()
{
   static Configuration self;
   return self;
}
   
void Configuration::Read()
{
   Reset();
   
   Application& application = Application::Instance();
   std::string path = application.GetProjectPathName();
   FileManager::AppendPath(path, application.GetProjectFileName());
   FileManager::AppendPath(path, ".ultraschallconfig");
   
   std::ifstream input(path);
   std::string entry;
   while(std::getline(input, entry))
   {
      const std::vector<std::string> items = framework::StringTokenize(entry, '=');
      if(items.size() > 1)
      {
         if(items[0] == "host-pin-code")
         {
            hostPinCode_ = items[1];
         }
         else if(items[0] == "guest-pin-code")
         {
            guestPinCode_ = items[1];
         }
      }
      else
      {
         projectMarkers_.push_back(entry);
      }
   }
   
   input.close();
}

void Configuration::Reset()
{
   hostPinCode_.clear();
   guestPinCode_.clear();
   projectMarkers_.clear();
}
   
}}

