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

#include <vector>

#include "Marker.h"

namespace framework = ultraschall::framework;

namespace ultraschall {
namespace reaper {

class Project
{
public:
   Project();
   Project(void* projectReference);
   virtual ~Project();

   Project(const Project& rhs);
   Project& operator=(const Project& rhs);

   static bool Validate(const Project& project);

   std::string FullPathName() const;
   std::string FolderName() const;
   std::string FileName() const;
   std::string Name() const;

   inline void* ProjectReference() const;

   static const uint32_t INVALID_MARKER_MASK       = 0xffffffff;
   static const uint32_t SHOW_CHAPTER_MARKERS      = 0x00000001;
   static const uint32_t SHOW_EDIT_MARKERS         = 0x00000002;
   static const uint32_t SHOW_SHOWNOTE_MARKERS     = 0x00000004;
   static const uint32_t SHOW_HISTORICAL_MARKERS   = 0x00000008;
   static const uint32_t SHOW_ALL_MARKERS          = SHOW_CHAPTER_MARKERS | 
                                                     SHOW_EDIT_MARKERS | 
                                                     SHOW_SHOWNOTE_MARKERS |
                                                     SHOW_HISTORICAL_MARKERS;

   static const double INVALID_POSITION;
   double CurrentPosition() const;

   static const int SHOWNOTE_MARKER_COLOR = 0x0145a564;
   static const int EDIT_MARKER_COLOR = 0x01ff0000;
   static const int CHAPTER_MARKER_COLOR = 0x01808080;
   static const int HISTORICAL_MARKER_COLOR = 0x016666aa;

   inline bool InsertChapterMarker(const std::string& name, const double position = INVALID_POSITION);
   inline bool InsertEditMarker(const double position = INVALID_POSITION);
   inline bool InsertShownoteMarker(const double position = INVALID_POSITION);
   inline bool InsertHistoricalMarker();
   bool UndoMarker();

   void UpdateMarkers(const uint32_t mask);
   void DeleteAllMarkers();
   void DeleteVisibleMarkers();

   inline uint32_t MarkerStatus() const;

   inline std::vector<Marker> ChapterMarkers() const;
   inline std::vector<Marker> EditMarkers() const;
   inline std::vector<Marker> ShownoteMarkers() const;

private:
   void* projectReference_;
   uint32_t markerStatus_;

   std::vector<Marker> allMarkers_;

   bool InsertMarker(const Marker& marker);
   bool InsertMarker(const std::string& name, const int color, const double position = INVALID_POSITION);
   std::vector<Marker> FilterMarkers(const int color) const;
};

inline uint32_t Project::MarkerStatus() const
{
   return markerStatus_;
}

inline void* Project::ProjectReference() const
{
   return projectReference_;
}

inline bool Project::InsertChapterMarker(const std::string& name, const double position)
{
   return InsertMarker(name, CHAPTER_MARKER_COLOR, position);
}

inline bool Project::InsertEditMarker(const double position)
{
   return InsertMarker("<Edit here>", EDIT_MARKER_COLOR, position);
}

inline bool Project::InsertShownoteMarker(const double position)
{
   return InsertMarker("<Insert Shownote here>", SHOWNOTE_MARKER_COLOR, position);
}

inline bool Project::InsertHistoricalMarker()
{
   const double currentPosition = CurrentPosition();
   return InsertMarker("<Adjust chapter here>", HISTORICAL_MARKER_COLOR, (currentPosition > 120) ? currentPosition - 120 : 0);
}

inline std::vector<Marker> Project::ChapterMarkers() const
{
   // merge chapter and historical markers
   std::vector<Marker> result = FilterMarkers(CHAPTER_MARKER_COLOR);
   std::vector<Marker> historicalMarkers = FilterMarkers(HISTORICAL_MARKER_COLOR);
   result.insert(std::end(result), std::begin(historicalMarkers), std::end(historicalMarkers));
   return result;
}

inline std::vector<Marker> Project::EditMarkers() const
{
   return FilterMarkers(EDIT_MARKER_COLOR);
}

inline std::vector<Marker> Project::ShownoteMarkers() const
{
   return FilterMarkers(SHOWNOTE_MARKER_COLOR);
}

}
}

#endif // #ifndef __ULTRASCHALL_REAPER_PROJECT_H_INCL__

