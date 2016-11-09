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

#ifndef __ULTRASCHALL_REAPER_PROJECT_H_INCL__
#define __ULTRASCHALL_REAPER_PROJECT_H_INCL__

#include <string>
#include <mutex>
#include <vector>

#include <ChapterMarker.h>
#include <EditMarker.h>
#include <ShownoteMarker.h>

namespace framework = ultraschall::framework;

namespace ultraschall {
namespace reaper {

class Project
{
public:
   Project();
   Project(void* externalReference);
   virtual ~Project();

   Project(const Project& rhs);
   Project& operator=(const Project& rhs);

   static bool Validate(const Project& project);

   std::string FullPathName() const;
   std::string FolderName() const;
   std::string FileName() const;
   std::string Name() const;

private:
   void* externalReference_;

   std::vector<framework::ChapterMarker> chapterMarkers_;
   mutable std::recursive_mutex chapterMarkersLock_;

   std::vector<framework::EditMarker> editMarkers_;
   mutable std::recursive_mutex editMarkersLock_;

   std::vector<framework::ShownoteMarker> shownoteMarkers_;
   mutable std::recursive_mutex shownoteMarkersLock_;
};

}
}

#endif // #ifndef __ULTRASCHALL_REAPER_PROJECT_H_INCL__

