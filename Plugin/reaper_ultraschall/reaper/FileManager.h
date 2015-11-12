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

#ifndef __ULTRASCHALL_REAPER_FILE_MANAGER_H_INCL__
#define __ULTRASCHALL_REAPER_FILE_MANAGER_H_INCL__

#include <string>
#include <vector>

#include <ResourceId.h>

namespace ultraschall { namespace reaper {

class FileManager
{
public:
   static const std::string BrowseForFiles(const framework::ResourceId id);
   static const std::string BrowseForFiles(const std::string& title);

   static const std::string BrowseForFolder(const framework::ResourceId id, const std::string& folder);
   static const std::string BrowseForFolder(const std::string& title, const std::string& folder);
   
   static const std::string AppendPath(const std::string& prefix, const std::string& append);
   
   static const std::string UserHomeDirectory();
   static const std::string UserApplicationSupportDirectory();
   static const std::string SystemApplicationSupportDirectory();
   
   static const bool FileExists(const std::string& path);
   static const std::vector<std::string> ReadFile(const std::string& filename);
};

}}

#endif // #ifndef __ULTRASCHALL_REAPER_FILE_MANAGER_H_INCL__
