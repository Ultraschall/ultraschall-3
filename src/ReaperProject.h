////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
//
// The MIT License (MIT)
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

#include "Common.h"
#include "Marker.h"
#include "ReaperGateway.h"

namespace ultraschall { namespace reaper {

class ReaperProject
{
public:
    ReaperProject();
    ReaperProject(ProjectReference nativeReference);
    virtual ~ReaperProject();

    ReaperProject(const ReaperProject& rhs);
    ReaperProject& operator=(const ReaperProject& rhs);

    static bool Validate(const ReaperProject& project);

    UnicodeString FullPathName() const;
    UnicodeString FolderName() const;
    UnicodeString FileName() const;
    UnicodeString Name() const;

    inline ProjectReference NativeReference() const;

    static const uint32_t INVALID_MARKER_MASK = 0xffffffff;

    static const uint32_t SHOW_CHAPTER_MARKERS    = 0x00000001;
    static const uint32_t SHOW_EDIT_MARKERS       = 0x00000002;
    static const uint32_t SHOW_SHOWNOTE_MARKERS   = 0x00000004;
    static const uint32_t SHOW_HISTORICAL_MARKERS = 0x00000008;
    static const uint32_t SHOW_ALL_MARKERS
        = SHOW_CHAPTER_MARKERS | SHOW_EDIT_MARKERS | SHOW_SHOWNOTE_MARKERS | SHOW_HISTORICAL_MARKERS;

    static const double INVALID_POSITION;
    double              CurrentPosition() const;
    double              MinPosition() const;
    double              MaxPosition() const;
    bool                IsValidPosition(const double position);

    static const int SHOWNOTE_MARKER_COLOR   = 0x0145a564;
    static const int EDIT_MARKER_COLOR       = 0x01ff0000;
    static const int CHAPTER_MARKER_COLOR    = 0x01808080;
    static const int HISTORICAL_MARKER_COLOR = 0x016666aa;

    inline bool InsertChapterMarker(const UnicodeString& name, const double position = INVALID_POSITION);
    inline bool InsertEditMarker(const double position = INVALID_POSITION);
    inline bool InsertShownoteMarker(const double position = INVALID_POSITION);
    inline bool InsertHistoricalMarker();
    bool        UndoMarker();

    void RefreshUI(const uint32_t mask);

    MarkerArray AllMarkers() const;
    void        UpdateMarkers();

    inline uint32_t MarkerStatus() const;

    inline MarkerArray ChapterMarkers() const;
    inline MarkerArray EditMarkers() const;
    inline MarkerArray ShownoteMarkers() const;

    UnicodeString Notes() const;

protected:
    inline bool SetMarkerStatus(const uint32_t mask);

private:
    ProjectReference nativeReference_ = nullptr;
    uint32_t         markerStatus_    = INVALID_MARKER_MASK;

    MarkerArray allMarkers_;

    bool        InsertMarker(const Marker& marker);
    bool        InsertMarker(const UnicodeString& name, const int color, const double position = INVALID_POSITION);
    MarkerArray FilterMarkers(const int color) const;
};

inline bool ReaperProject::SetMarkerStatus(const uint32_t mask)
{
    PRECONDITION_RETURN(mask != INVALID_MARKER_MASK, false);
    markerStatus_ = mask;
    return true;
}

inline uint32_t ReaperProject::MarkerStatus() const
{
    return markerStatus_;
}

inline ProjectReference ReaperProject::NativeReference() const
{
    return nativeReference_;
}

inline bool ReaperProject::InsertChapterMarker(const UnicodeString& name, const double position)
{
    return InsertMarker(name, CHAPTER_MARKER_COLOR, position);
}

inline bool ReaperProject::InsertEditMarker(const double position)
{
    return InsertMarker("<Edit here>", EDIT_MARKER_COLOR, position);
}

inline bool ReaperProject::InsertShownoteMarker(const double position)
{
    return InsertMarker("<Insert Shownote here>", SHOWNOTE_MARKER_COLOR, position);
}

inline bool ReaperProject::InsertHistoricalMarker()
{
    const double currentPosition = CurrentPosition();
    return InsertMarker(
        "<Adjust chapter here>", HISTORICAL_MARKER_COLOR, (currentPosition > 120) ? currentPosition - 120 : 0);
}

inline MarkerArray ReaperProject::ChapterMarkers() const
{
    // merge chapter and historical markers
    MarkerArray result            = FilterMarkers(CHAPTER_MARKER_COLOR);
    MarkerArray historicalMarkers = FilterMarkers(HISTORICAL_MARKER_COLOR);
    result.insert(std::end(result), std::begin(historicalMarkers), std::end(historicalMarkers));
    return result;
}

inline MarkerArray ReaperProject::EditMarkers() const
{
    return FilterMarkers(EDIT_MARKER_COLOR);
}

inline MarkerArray ReaperProject::ShownoteMarkers() const
{
    return FilterMarkers(SHOWNOTE_MARKER_COLOR);
}

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_PROJECT_H_INCL__
