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

#include "ProjectCallback.h"
#include "ProjectManager.h"

namespace ultraschall {
namespace reaper {

bool ProjectCallback::ProcessExtensionLine(Project& projectReference, const std::string& line, ProjectStateContext& readContext)
{
   bool processed = false;

   if(Project::Validate(projectReference) == true)
   {
      if(line.empty() == false)
      {
         if(line.find("<ULTRASCHALL_VERSION:") != std::string::npos)
         {
            std::pair<uint8_t, uint8_t> projectVersion = ParseVersion(line);
            if(projectVersion.first == 3)
            {
               static const int MAX_BUFFER_LENGTH = 4096;
               char nextLineBuffer[MAX_BUFFER_LENGTH] = { 0 };
               int readLength = readContext.GetLine(nextLineBuffer, MAX_BUFFER_LENGTH);
               if(readLength >= 0)
               {
                  const std::string buffer = nextLineBuffer;
                  if(buffer.find("<ULTRASCHALL_ANNOTATION_STATUS:") != std::string::npos)
                  {
                     const uint32_t markerStatus = ParseMarkerStatus(buffer);
                     if(markerStatus != Project::INVALID_MARKER_MASK)
                     {
                        const ProjectManager& projectManager = ProjectManager::Instance();
                        Project currentProject = projectManager.CurrentProject();
                        currentProject.UpdateMarkers(markerStatus);
                     }
                  }
               }
            }

            processed = true;
         }
      }
   }

   return processed;
}

void ProjectCallback::SaveExtensionConfig(const Project& projectReference, ProjectStateContext& writeContext)
{
   const uint32_t markerStatus = projectReference.MarkerStatus();
   if(markerStatus != Project::INVALID_MARKER_MASK)
   {
      writeContext.AddLine("<ULTRASCHALL_VERSION:3.0>");
      writeContext.AddLine("<ULTRASCHALL_ANNOTATION_STATUS:%d>", markerStatus);
   }
}

void ProjectCallback::BeginLoadProjectState(Project&)
{
}

std::pair<uint8_t, uint8_t> ProjectCallback::ParseVersion(const std::string& line)
{
   return std::pair<uint8_t, uint8_t>(3, 0);
}

uint32_t ProjectCallback::ParseMarkerStatus(const std::string& line)
{
   return Project::SHOW_EDIT_MARKERS | Project::SHOW_CHAPTER_MARKERS;
}

}
}
