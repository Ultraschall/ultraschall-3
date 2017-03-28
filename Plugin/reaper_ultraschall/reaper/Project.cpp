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
#include <algorithm>

#include <StringUtilities.h>

#include "Project.h"
#include "ReaperEntryPoints.h"
#include "FileManager.h"

namespace ultraschall
{
namespace reaper
{

const double Project::INVALID_POSITION = -1;

Project::Project() : projectReference_(0)
{
}

Project::Project(ProjectHandle projectReference) : projectReference_(projectReference)
{
   UpdateAllMarkers();
}

Project::~Project()
{
   projectReference_ = nullptr;
}

Project::Project(const Project &rhs)
{
   *this = rhs;
}

Project &Project::operator=(const Project &rhs)
{
   if (this != &rhs)
   {
      projectReference_ = rhs.projectReference_;
   }

   return *this;
}

bool Project::Validate(const Project &project)
{
   return project.projectReference_ != nullptr;
}

std::string Project::FullPathName() const
{
   PRECONDITION_RETURN(projectReference_ != 0, std::string());

   std::string result;

   static const size_t MAX_REAPER_STRING_BUFFER_SIZE = 4096;
   char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
   int index = 0;
   ReaProject *externalReference = reaper_api::EnumProjects(index++, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
   while ((externalReference != 0) && (result.empty() == true))
   {
      if (externalReference == projectReference_)
      {
         result = buffer;
      }

      externalReference = reaper_api::EnumProjects(index++, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
   }

   return framework::UnicodeStringToAnsiString(result);
}

std::string Project::FolderName() const
{
   std::string result;

   const std::string fullPath = FullPathName();
   if (fullPath.empty() == false)
   {
      const char pathSeparator = FileManager::PathSeparator();
      const std::vector<std::string> pathComponents = framework::StringTokenize(fullPath, pathSeparator);
      if (pathComponents.empty() == false)
      {
         for (size_t i = 0; i < pathComponents.size() - 1; i++)
         {
            result += pathComponents[i];
            if (i < pathComponents.size() - 2)
            {
               result += pathSeparator;
            }
         }
      }
   }

   return result;
}

std::string Project::FileName() const
{
   std::string result;

   const std::string fullPath = FullPathName();
   if (fullPath.empty() == false)
   {
      const char pathSeparator = FileManager::PathSeparator();
      const std::vector<std::string> pathComponents = framework::StringTokenize(fullPath, pathSeparator);
      if (pathComponents.empty() == false)
      {
         result = pathComponents[pathComponents.size() - 1];
      }
   }

   return result;
}

std::string Project::Name() const
{
   PRECONDITION_RETURN(projectReference_ != 0, std::string());

   std::string result;

   const std::string file = FileName();
   if (file.empty() == false)
   {
      result = file.substr(0, file.find('.', 0));
   }

   return result;
}

std::string Project::Notes() const
{
   ReaProject *projectReference = reinterpret_cast<ReaProject *>(projectReference_);

   static const size_t MAX_PROJECT_NOTES_SIZE = 4096;
   char projectNotes[MAX_PROJECT_NOTES_SIZE] = {0};
   reaper_api::GetSetProjectNotes(projectReference, false, projectNotes, (int)MAX_PROJECT_NOTES_SIZE);
   std::string notes = projectNotes;
   notes.erase(std::remove(notes.begin(), notes.end(), '\r'), notes.end());
   return framework::UnicodeStringToAnsiString(notes);
}

bool Project::InsertMarker(const Marker &marker)
{
   allMarkers_.push_back(marker);
   UpdateVisibleMarkers(MarkerStatus());
   return false;
}

bool Project::InsertMarker(const std::string &name, const int /*color*/, const double position)
{
   PRECONDITION_RETURN(projectReference_ != 0, false);
   PRECONDITION_RETURN(name.empty() == false, false);

   double actualPosition = position;
   if (actualPosition == INVALID_POSITION)
   {
      actualPosition = CurrentPosition();
   }

   const int index = reaper_api::AddProjectMarker2(projectReference_, false, actualPosition, 0, name.c_str(), -1, 0);
   return index != -1;
}

double Project::CurrentPosition() const
{
   PRECONDITION_RETURN(projectReference_ != 0, INVALID_POSITION);

   ReaProject *projectReference = reinterpret_cast<ReaProject *>(projectReference_);
   double position = INVALID_POSITION;
   const int playState = reaper_api::GetPlayStateEx(projectReference);
   if ((playState == 0) || (playState == 2))
   {
      position = reaper_api::GetCursorPositionEx(projectReference);
   }
   else
   {
      position = reaper_api::GetPlayPositionEx(projectReference);
   }

   return position;
}

bool Project::UndoMarker()
{
   PRECONDITION_RETURN(projectReference_ != 0, false);

   bool success = false;

   ReaProject *projectReference = reinterpret_cast<ReaProject *>(projectReference_);
   double currentPosition = CurrentPosition();

   int markerIndex = -1;
   reaper_api::GetLastMarkerAndCurRegion(projectReference, currentPosition, &markerIndex, 0);
   if (markerIndex != -1)
   {
      success = reaper_api::DeleteProjectMarkerByIndex(projectReference, markerIndex);
   }

   return success;
}

std::vector<Marker> Project::FilterMarkers(const int color) const
{
   std::vector<Marker> result;

   std::for_each(allMarkers_.begin(), allMarkers_.end(), [&](const Marker &marker) {
      if (marker.Color() == color)
      {
         result.push_back(marker);
      }
   });

   return result;
}

class AutoPreventUIRefresh
{
 public:
   AutoPreventUIRefresh()
   {
      reaper_api::PreventUIRefresh(1);
   }

   virtual ~AutoPreventUIRefresh()
   {
      reaper_api::PreventUIRefresh(-1);
   }
};

std::vector<Marker> Project::QueryAllMarkers() const
{
   PRECONDITION_RETURN(projectReference_ != nullptr, std::vector<Marker>());

   std::vector<Marker> allMarkers;

   bool isRegion = false;
   double position = 0;
   double duration = 0;
   const char *name = nullptr;
   int number = 0;
   int color = 0;

   int nextIndex = reaper_api::EnumProjectMarkers3(projectReference_, 0, &isRegion, &position, &duration, &name, &number, &color);
   while (nextIndex > 0)
   {
      const std::string markerName = name;
      if (("_Edit" != markerName) && (color != 0x01ff0000)) // remove edit markers
      {
         allMarkers.push_back(Marker(position, markerName, color));
      }

      nextIndex = reaper_api::EnumProjectMarkers3(projectReference_, nextIndex, &isRegion, &position, &duration, &name, &number, &color);
   }

   return allMarkers;
}

void Project::UpdateAllMarkers()
{
   PRECONDITION(projectReference_ != nullptr);

   DeleteAllMarkers();

   const size_t noMarkers = CountVisibleMarkers();
   if (noMarkers > 0)
   {
      bool isRegion = false;
      double position = 0;
      double duration = 0;
      const char *name = nullptr;
      int number = 0;
      int color = 0;

      int nextIndex = reaper_api::EnumProjectMarkers3(projectReference_, 0, &isRegion, &position, &duration, &name, &number, &color);
      while (nextIndex > 0)
      {
         allMarkers_.push_back(Marker(position, name, color));
         nextIndex = reaper_api::EnumProjectMarkers3(projectReference_, nextIndex, &isRegion, &position, &duration, &name, &number, &color);
      }
   }
}

void Project::DeleteAllMarkers()
{
   allMarkers_.clear();
}

size_t Project::CountVisibleMarkers() const
{
   PRECONDITION_RETURN(projectReference_ != 0, static_cast<size_t>(-1));

   ReaProject *projectReference = reinterpret_cast<ReaProject *>(projectReference_);
   int numProjectMarkers = 0;
   reaper_api::CountProjectMarkers(projectReference, &numProjectMarkers, 0);
   return static_cast<size_t>(numProjectMarkers);
}

void Project::DeleteVisibleMarkers()
{
   PRECONDITION(projectReference_ != 0);

   AutoPreventUIRefresh();

   ReaProject *projectReference = reinterpret_cast<ReaProject *>(projectReference_);
   const size_t numProjectMarkers = CountVisibleMarkers();
   for (size_t i = 0; i < numProjectMarkers; i++)
   {
      reaper_api::DeleteProjectMarkerByIndex(projectReference, static_cast<int>(i));
   }
}

void Project::UpdateVisibleMarkers(const uint32_t mask)
{
   AutoPreventUIRefresh();

   DeleteVisibleMarkers();

   markerStatus_ = mask;
   std::for_each(allMarkers_.begin(), allMarkers_.end(), [&](const Marker &marker) {
      bool insert = false;

      if (markerStatus_ & SHOW_CHAPTER_MARKERS)
      {
         if (marker.Color() == CHAPTER_MARKER_COLOR)
         {
            insert = true;
         }
      }

      if (MarkerStatus() & SHOW_EDIT_MARKERS)
      {
         if (marker.Color() == EDIT_MARKER_COLOR)
         {
            insert = true;
         }
      }

      if (MarkerStatus() & SHOW_SHOWNOTE_MARKERS)
      {
         if (marker.Color() == SHOWNOTE_MARKER_COLOR)
         {
            insert = true;
         }
      }

      if (MarkerStatus() & SHOW_HISTORICAL_MARKERS)
      {
         if (marker.Color() == HISTORICAL_MARKER_COLOR)
         {
            insert = true;
         }
      }

      if (true == insert)
      {
         ReaProject *projectReference = reinterpret_cast<ReaProject *>(projectReference_);
         reaper_api::AddProjectMarker2(projectReference, false, marker.Position(), 0, marker.Name().c_str(), -1, marker.Color());
      }
   });
}
}
}
