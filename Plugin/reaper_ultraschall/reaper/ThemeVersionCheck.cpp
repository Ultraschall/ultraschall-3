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
#include <zlib.h>
#include <unzip.h>
#include <StringUtilities.h>
#include <TextFileReader.h>
#include "ThemeVersionCheck.h"
#include "FileManager.h"

namespace ultraschall { namespace reaper {
#if 0
const std::string QueryThemeVersion()
{
   std::string result;

   const std::string applicationSupportDirectory = FileManager::UserApplicationSupportDirectory();
   if(applicationSupportDirectory.empty() == false)
   {
      const std::string themeControlFile = applicationSupportDirectory +
                                           "/REAPER/ColorThemes/Ultraschall_2.ReaperTheme";
      const std::vector<std::string> lines = framework::TextFileReader::ReadLines(themeControlFile);
      for(size_t i = 0 ; i < lines.size(); i++)
      {
         const std::string& line = lines[i];
         if(line.empty() == false)
         {
            const std::vector<std::string> tokens = framework::split(line, '=');
            if(tokens.size() == 2)
            {
               if(tokens[0] == "ui_img")
               {
      const std::string themeVersionFile = applicationSupportDirectory +
                                                       "/REAPER/ColorThemes/" +
                                                       tokens[1] +
                                                       "/version.txt";
      const std::string themeVersionString = framework::TextFileReader::Read(themeVersionFile);
      if(themeVersionString.empty() == false)
      {
         const std::vector<std::string> versionTokens = framework::split(themeVersionString, ':');
         if(versionTokens.size() == 2)
         {
            std::string version = versionTokens[1];
            if(version.empty() == false)
            {
               result = framework::trim(version);
                        }
                     }
                  }
               }
            }
         }
      }
   }
   
   return result;
}
#else
const std::string QueryThemeVersion2()
{
   std::string result;
   
   std::string versionString;
   
   const std::string applicationSupportDirectory = FileManager::UserApplicationSupportDirectory();
   if(applicationSupportDirectory.empty() == false)
   {
      const std::string themeControlFile = applicationSupportDirectory +
                                           "/REAPER/ColorThemes/Ultraschall_2.1.ReaperThemeZip";
      
      unzFile themeFile = unzOpen(themeControlFile.c_str());
      if(themeFile != 0)
      {
         bool decoded = false;
         int zipError = unzGoToFirstFile(themeFile);
         while((UNZ_OK == zipError) && (false == decoded))
         {
            unz_file_info fileInfo = {0};
            const size_t fileNameSize = 4096;
            char fileName[fileNameSize] = {0};
            zipError = unzGetCurrentFileInfo(themeFile, &fileInfo, fileName, fileNameSize, 0, 0, 0, 0);
            if(UNZ_OK == zipError)
            {
               if(strcmp("Ultraschall_2/version.txt", fileName) == 0)
               {
                  zipError = unzOpenCurrentFile(themeFile);
                  if(UNZ_OK == zipError)
                  {
                     const size_t fileBufferSize = fileInfo.uncompressed_size;
                     if(fileBufferSize > 0)
                     {
                        char* fileBuffer = (char*)calloc(fileBufferSize, sizeof(char));
                        if(fileBuffer != 0)
                        {
                           const int readResult = unzReadCurrentFile(themeFile, fileBuffer, (unsigned int)fileBufferSize);
                           if(readResult > 0)
                           {
                              versionString = fileBuffer;
                              decoded = true;
                           }
                           
                           free(fileBuffer);
                           fileBuffer = 0;
                        }
                     }
                     
                     unzCloseCurrentFile(themeFile);
                  }
               }
            }
            
            zipError = unzGoToNextFile(themeFile);
         }
         
         unzClose(themeFile);
         themeFile = 0;
      }
   }
   
   if(versionString.empty() == false)
   {
      const std::vector<std::string> versionTokens = framework::split(versionString, ':');
      if(versionTokens.size() == 2)
      {
         std::string version = versionTokens[1];
         if(version.empty() == false)
         {
            result = framework::trim(version);
         }
      }
   }

   return result;
}
#endif
}}
