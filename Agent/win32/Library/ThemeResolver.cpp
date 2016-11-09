#include "stdafx.h"

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>
#include <cctype>

#include <msclr\marshal_cppstd.h>

#include <zlib.h>
#include <unzip.h>

#include "ThemeResolver.h"

namespace Ultraschall
{

static inline std::vector<std::string> split(const std::string& input, const char delimiter)
{
   std::vector<std::string> tokens;
   std::stringstream stream(input);
   std::string token;

   while(std::getline(stream, token, delimiter))
   {
      tokens.push_back(token);
   }

   return tokens;
}

// trim from start
static inline std::string &ltrim(std::string &s) {
   s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
   return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
   s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
   return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
   return ltrim(rtrim(s));
}

String^ ThemeResolver::ResolveVersion(String^ path)
{
   std::string result;

   std::string versionString;

   std::string themeControlFile = msclr::interop::marshal_as<std::string>(path);
   unzFile themeFile = unzOpen(themeControlFile.c_str());
   if(themeFile != 0)
   {
      bool decoded = false;
      int zipError = unzGoToFirstFile(themeFile);
      while((UNZ_OK == zipError) && (false == decoded))
      {
         unz_file_info fileInfo = { 0 };
         const size_t fileNameSize = 4096;
         char fileName[fileNameSize] = { 0 };
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
                     char* fileBuffer = (char*)calloc(fileBufferSize + 1, sizeof(char));
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

   if(versionString.empty() == false)
   {
      const std::vector<std::string> versionTokens = split(versionString, ':');
      if(versionTokens.size() == 2)
      {
         std::string version = versionTokens[1];
         if(version.empty() == false)
         {
            result = trim(version);
         }
      }
   }

   return gcnew String(result.c_str());
}

}
