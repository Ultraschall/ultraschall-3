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

#include "ReaperProject.h"
#include "Application.h"
#include "FileManager.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

const double ReaperProject::INVALID_POSITION = -1;

ReaperProject::ReaperProject() {}

ReaperProject::ReaperProject(ProjectReference nativeReference) : nativeReference_(nativeReference)
{
    UpdateMarkers();
}

ReaperProject::~ReaperProject()
{
    nativeReference_ = 0;
}

ReaperProject::ReaperProject(const ReaperProject& rhs)
{
    *this = rhs;
}

ReaperProject& ReaperProject::operator=(const ReaperProject& rhs)
{
    if(this != &rhs)
    {
        nativeReference_ = rhs.nativeReference_;
    }

    return *this;
}

bool ReaperProject::Validate(const ReaperProject& project)
{
    return project.nativeReference_ != 0;
}

UnicodeString ReaperProject::FullPathName() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, UnicodeString());
    return ReaperGateway::ProjectPath(nativeReference_);
}

UnicodeString ReaperProject::FolderName() const
{
    UnicodeString result;

    const UnicodeString fullPath = FullPathName();
    if(fullPath.empty() == false)
    {
        const char               pathSeparator  = FileManager::PathSeparator();
        const UnicodeStringArray pathComponents = UnicodeStringTokenize(fullPath, pathSeparator);
        if(pathComponents.empty() == false)
        {
            for(size_t i = 0; i < pathComponents.size() - 1; i++)
            {
                result += pathComponents[i];
                if(i < pathComponents.size() - 2)
                {
                    result += pathSeparator;
                }
            }
        }
    }

    return result;
}

UnicodeString ReaperProject::FileName() const
{
    UnicodeString result;

    const UnicodeString fullPath = FullPathName();
    if(fullPath.empty() == false)
    {
        const char               pathSeparator  = FileManager::PathSeparator();
        const UnicodeStringArray pathComponents = UnicodeStringTokenize(fullPath, pathSeparator);
        if(pathComponents.empty() == false)
        {
            result = pathComponents[pathComponents.size() - 1];
        }
    }

    return result;
}

UnicodeString ReaperProject::Name() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, UnicodeString());

    UnicodeString result;

    const UnicodeString file = FileName();
    if(file.empty() == false)
    {
        result = file.substr(0, file.rfind('.'));
    }

    return result;
}

UnicodeString ReaperProject::Notes() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, UnicodeString());

    return ReaperGateway::ProjectNotes(nativeReference_);
}

bool ReaperProject::InsertMarker(const Marker& marker)
{
    allMarkers_.push_back(marker);
    RefreshUI(MarkerStatus());
    return false;
}

bool ReaperProject::InsertMarker(const UnicodeString& name, const int /*color*/, const double position)
{
    PRECONDITION_RETURN(nativeReference_ != 0, false);
    PRECONDITION_RETURN(name.empty() == false, false);

    double actualPosition = position;
    if(actualPosition == INVALID_POSITION)
    {
        actualPosition = CurrentPosition();
    }

    return ReaperGateway::InsertMarker(nativeReference_, name, actualPosition);
}

double ReaperProject::CurrentPosition() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, INVALID_POSITION);

    double    currentPosition = INVALID_POSITION;
    const int playState       = ReaperGateway::PlayState(nativeReference_);
    if((playState == 0) || (playState == 2))
    {
        currentPosition = ReaperGateway::CursorPosition(nativeReference_);
    }
    else
    {
        currentPosition = ReaperGateway::PlayPosition(nativeReference_);
    }

    return currentPosition;
}

double ReaperProject::MinPosition() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, INVALID_POSITION);

    return ReaperGateway::MinPosition(nativeReference_);
}

double ReaperProject::MaxPosition() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, INVALID_POSITION);

    return ReaperGateway::MaxPosition(nativeReference_);
}

bool ReaperProject::IsValidPosition(const double position)
{
    PRECONDITION_RETURN(nativeReference_ != 0, false);

    return (position >= 0) && (position <= MaxPosition());
}

bool ReaperProject::UndoMarker()
{
    PRECONDITION_RETURN(nativeReference_ != 0, false);

    return ReaperGateway::UndoMarker(nativeReference_, CurrentPosition());
}

MarkerArray ReaperProject::FilterMarkers(const int color) const
{
    MarkerArray result;

    std::for_each(allMarkers_.begin(), allMarkers_.end(), [&](const Marker& marker) {
        if(marker.Color() == color)
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
        ReaperGateway::LockUIRefresh(true);
    }

    virtual ~AutoPreventUIRefresh()
    {
        ReaperGateway::LockUIRefresh(false);
    }
};

MarkerArray ReaperProject::AllMarkers() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, MarkerArray());

    return ReaperGateway::AllMarkers(nativeReference_);
}

void ReaperProject::UpdateMarkers()
{
    PRECONDITION(nativeReference_ != 0);

    allMarkers_.clear();

    const size_t noMarkers = ReaperGateway::CountMarkers(nativeReference_);
    if(noMarkers > 0)
    {
        allMarkers_ = AllMarkers();
    }
}

void ReaperProject::RefreshUI(const uint32_t mask)
{
    PRECONDITION(nativeReference_ != 0);

    AutoPreventUIRefresh();
    ReaperGateway::ClearMarkers(nativeReference_);

    if(SetMarkerStatus(mask) == true)
    {
        std::for_each(allMarkers_.begin(), allMarkers_.end(), [&](const Marker& marker) {
            bool           insert       = false;
            const uint32_t markerStatus = MarkerStatus();
            if(markerStatus & SHOW_CHAPTER_MARKERS)
            {
                if(marker.Color() == CHAPTER_MARKER_COLOR)
                {
                    insert = true;
                }
            }

            if(markerStatus & SHOW_EDIT_MARKERS)
            {
                if(marker.Color() == EDIT_MARKER_COLOR)
                {
                    insert = true;
                }
            }

            if(markerStatus & SHOW_SHOWNOTE_MARKERS)
            {
                if(marker.Color() == SHOWNOTE_MARKER_COLOR)
                {
                    insert = true;
                }
            }

            if(markerStatus & SHOW_HISTORICAL_MARKERS)
            {
                if(marker.Color() == HISTORICAL_MARKER_COLOR)
                {
                    insert = true;
                }
            }

            if(true == insert)
            {
                ReaperGateway::InsertMarker(nativeReference_, marker);
            }
        });
    }
}
}} // namespace ultraschall::reaper
