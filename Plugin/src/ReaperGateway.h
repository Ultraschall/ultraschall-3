
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

#ifndef __ULTRASCHALL_REAPER_GATEWAY_H_INCL__
#define __ULTRASCHALL_REAPER_GATEWAY_H_INCL__

#include "Common.h"
#include "Marker.h"

namespace ultraschall { namespace reaper {

typedef void* ProjectReference;

class ReaperGateway
{
public:
    static const size_t MAX_REAPER_STRING_BUFFER_SIZE = 4096;
    static const double INVALID_POSITION;

    static uint32_t EditMarkerColor();

    static UnicodeString ApplicationVersion();
    static int32_t       RegisterCustomAction(const UnicodeString& name, void* infoStruct);
    static void          LockUIRefresh(const bool lock);

    static UnicodeString ExportPathName();
    static UnicodeString ProjectPathName();
    static UnicodeString ProjectFileName();
    static UnicodeString ProjectFolderName();
    static UnicodeString ProjectName();

    static UnicodeString TimestampToString(const double timestamp);
    static double        StringToTimestamp(const UnicodeString& input);

    static ProjectReference CurrentProject();
    static UnicodeString    ProjectPath(ProjectReference projectReference);
    static UnicodeString    ProjectNotes(ProjectReference projectReference);

    static MarkerArray AllMarkers(ProjectReference projectReference);

    static size_t CountMarkers(ProjectReference projectReference);
    static bool   ClearMarkers(ProjectReference projectReference);

    static bool InsertMarker(ProjectReference projectReference, const UnicodeString& name, const double position);
    static bool InsertMarker(ProjectReference projectReference, const Marker& marker);
    static bool UndoMarker(ProjectReference projectReference, const double position);

    static int    PlayState(ProjectReference projectReference);
    static double CursorPosition(ProjectReference projectReference);
    static double PlayPosition(ProjectReference projectReference);
    static double MinPosition(ProjectReference projectReference);
    static double MaxPosition(ProjectReference projectReference);

    static bool          HasValue(const UnicodeString& section, const UnicodeString& key);
    static UnicodeString GetValue(const UnicodeString& section, const UnicodeString& key);
    static void          SetValue(const UnicodeString& section, const UnicodeString& key, const UnicodeString& value);
    static void          SaveValue(const UnicodeString& section, const UnicodeString& key, const UnicodeString& value);
    static void          ClearValue(const UnicodeString& section, const UnicodeString& key);
    static void          DeleteValue(const UnicodeString& section, const UnicodeString& key);
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_GATEWAY_H_INCL__
