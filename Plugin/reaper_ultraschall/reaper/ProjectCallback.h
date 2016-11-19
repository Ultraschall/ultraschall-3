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

#ifndef __ULTRASCHALL_REAPER_PROJECT_CALLBACK_H_INCL__
#define __ULTRASCHALL_REAPER_PROJECT_CALLBACK_H_INCL__

#include <string>

#include "ReaperEntryPoints.h"
#include "Project.h"

namespace ultraschall {
namespace reaper {

class Project;

class ProjectCallback
{
public:
   static bool ProcessExtensionLine(ProjectHandle projectReference, const std::string& line, ProjectStateContext& readContext);

   static void SaveExtensionConfig(ProjectHandle projectReference, ProjectStateContext& writeContext);

   static void BeginLoadProjectState(ProjectHandle);

private:
   static std::pair<uint8_t, uint8_t> ParseVersion(const std::string& line);
   static uint32_t ParseMarkerStatus(const std::string& line);
};

}
}

#endif // #ifndef __ULTRASCHALL_REAPER_PROJECT_CALLBACK_H_INCL__

