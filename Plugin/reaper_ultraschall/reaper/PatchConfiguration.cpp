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
#include <StringUtilities.h>
#include <TextFileReader.h>
#include <TextFileWriter.h>
#include "FileManager.h"
#include "PatchConfiguration.h"

namespace ultraschall { namespace reaper {

const std::vector<std::string> ReadConfiguration(const std::string file)
{
   std::vector<std::string> configuration;
   
   const std::string applicationSupperDirectory = FileManager::UserApplicationSupportDirectory();
   if(applicationSupperDirectory.empty() == false)
   {
      const std::string filePath = applicationSupperDirectory +
                                   "/REAPER/" +
                                   file;
      configuration = framework::TextFileReader::ReadLines(filePath);
   }

   return configuration;
}
 
const bool LineIsSection(const std::string& line)
{
   bool result = false;
   
   std::string cooked = line;
   cooked = framework::trim(cooked);
   if(cooked.length() > 2)
   {
      if((cooked[0] == '[') && (cooked[cooked.length() - 1] == ']'))
      {
         result = true;
      }
   }
   
   return result;
}
   
const std::string ReadConfigurationValue(const std::string& file, const std::string& section,
                                         const std::string& key)
{
   std::string result;

   if((file.empty() == false) && (section.empty() == false) && (key.empty() == false))
   {
      std::vector<std::string> lines = ReadConfiguration(file);
      if(lines.empty() == false)
      {
         std::string currentSection;
         
         for(size_t i = 0; i < lines.size(); i++)
         {
            if(LineIsSection(lines[i]) == true)
            {
               currentSection = lines[i];
            }
            else
            {
               std::vector<std::string> tokens = framework::split(lines[i], '=');
               if(tokens.size() == 2)
               {
                  if((tokens[0] == key) && (section == currentSection))
                  {
                     result = tokens[1];
                     break;
                  }
               }
            }
         }
      }
   }
   
   return result;
}

const void WriteConfigurationValue(const std::string& file, const std::string& section,
                                   const std::string& key, const std::string& value)
{
   if((file.empty() == false) && (section.empty() == false) && (key.empty() == false))
   {
      std::vector<std::string> lines = ReadConfiguration(file);
      if(lines.empty() == false)
      {
         std::string currentSection;
         
         for(size_t i = 0; i < lines.size(); i++)
         {
            if(LineIsSection(lines[i]) == true)
            {
               currentSection = lines[i];
            }
            else
            {
               std::vector<std::string> tokens = framework::split(lines[i], '=');
               if(tokens.size() == 2)
               {
                  if((tokens[0] == key) && (section == currentSection))
                  {
                     lines[i] = key + "=";
                     if(value.empty() == false)
                     {
                        lines[i] += value;
                     }
                  }
               }
            }
         }
      }
      
      framework::TextFileWriter::WriteLines(file, lines);
   }
}

void PatchVSTConfiguration()
{
   std::string vstConfiguration = ReadConfigurationValue("reaper.ini", "[REAPER]", "vstpath64");
   if(vstConfiguration.empty() == false)
   {
      const std::string userHomeDirectory = FileManager::UserHomeDirectory();
      if(userHomeDirectory.empty() == false)
      {
         framework::replace(vstConfiguration, "~", userHomeDirectory);
         WriteConfigurationValue("reaper.ini", "[REAPER]", "vstpath64", vstConfiguration);
      }
   }
}

void PatchSplashScreen()
{
   std::string splashScreen = ReadConfigurationValue("reaper.ini", "[REAPER]", "splashimage");
   if(splashScreen.empty() == false)
   {
      const std::string userHomeDirectory = FileManager::UserHomeDirectory();
      if(userHomeDirectory.empty() == false)
      {
         framework::replace(splashScreen, "~", userHomeDirectory);
         WriteConfigurationValue("reaper.ini", "[REAPER]", "vstpath64", splashScreen);
      }
   }
}
   
}}


