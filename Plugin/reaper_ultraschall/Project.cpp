////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

#include "Project.h"
#include "Application.h"
#include "FileManager.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

const double Project::INVALID_POSITION = -1;

Project::Project() : nativeReference_(0) {}

Project::Project(ProjectReference nativeReference) : nativeReference_(nativeReference)
{
    UpdateMarkers();
}

Project::~Project()
{
    nativeReference_ = 0;
}

Project::Project(const Project& rhs)
{
    *this = rhs;
}

Project& Project::operator=(const Project& rhs)
{
    if(this != &rhs)
    {
        nativeReference_ = rhs.nativeReference_;
    }

    return *this;
}

bool Project::Validate(const Project& project)
{
    return project.nativeReference_ != 0;
}

UnicodeString Project::FullPathName() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, UnicodeString());
    return ReaperGateway::ProjectPath(nativeReference_);
}

UnicodeString Project::FolderName() const
{
    UnicodeString result;

    const UnicodeString fullPath = FullPathName();
    if(fullPath.empty() == false)
    {
        const char               pathSeparator  = FileManager::PathSeparator();
        const UnicodeStringArray pathComponents = StringTokenize(fullPath, pathSeparator);
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

UnicodeString Project::FileName() const
{
    UnicodeString result;

    const UnicodeString fullPath = FullPathName();
    if(fullPath.empty() == false)
    {
        const char               pathSeparator  = FileManager::PathSeparator();
        const UnicodeStringArray pathComponents = StringTokenize(fullPath, pathSeparator);
        if(pathComponents.empty() == false)
        {
            result = pathComponents[pathComponents.size() - 1];
        }
    }

    return result;
}

UnicodeString Project::Name() const
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

UnicodeString Project::Notes() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, UnicodeString());

    return ReaperGateway::ProjectNotes(nativeReference_);
}

bool Project::InsertMarker(const Marker& marker)
{
    allMarkers_.push_back(marker);
    RefreshUI(MarkerStatus());
    return false;
}

bool Project::InsertMarker(const UnicodeString& name, const int /*color*/, const double position)
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

double Project::CurrentPosition() const
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

double Project::MinPosition() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, INVALID_POSITION);

    return ReaperGateway::MinPosition(nativeReference_);
}

double Project::MaxPosition() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, INVALID_POSITION);

    return ReaperGateway::MinPosition(nativeReference_);
}

bool Project::IsValidPosition(const double position)
{
    PRECONDITION_RETURN(nativeReference_ != 0, false);

    return (position >= 0) && (position <= MaxPosition());
}

bool Project::UndoMarker()
{
    PRECONDITION_RETURN(nativeReference_ != 0, false);

    return ReaperGateway::UndoMarker(nativeReference_, CurrentPosition());
}

MarkerArray Project::FilterMarkers(const int color) const
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

MarkerArray Project::AllMarkers() const
{
    PRECONDITION_RETURN(nativeReference_ != 0, MarkerArray());

    return ReaperGateway::AllMarkers(nativeReference_);
}

void Project::UpdateMarkers()
{
    PRECONDITION(nativeReference_ != 0);

    allMarkers_.clear();

    const size_t noMarkers = ReaperGateway::CountMarkers(nativeReference_);
    if(noMarkers > 0)
    {
        allMarkers_ = AllMarkers();
    }
}

void Project::RefreshUI(const uint32_t mask)
{
    PRECONDITION(nativeReference_ != 0);

    AutoPreventUIRefresh();
    ReaperGateway::ClearMarkers(nativeReference_);

    markerStatus_ = mask;
    std::for_each(allMarkers_.begin(), allMarkers_.end(), [&](const Marker& marker) {
        bool insert = false;

        if(markerStatus_ & SHOW_CHAPTER_MARKERS)
        {
            if(marker.Color() == CHAPTER_MARKER_COLOR)
            {
                insert = true;
            }
        }

        if(MarkerStatus() & SHOW_EDIT_MARKERS)
        {
            if(marker.Color() == EDIT_MARKER_COLOR)
            {
                insert = true;
            }
        }

        if(MarkerStatus() & SHOW_SHOWNOTE_MARKERS)
        {
            if(marker.Color() == SHOWNOTE_MARKER_COLOR)
            {
                insert = true;
            }
        }

        if(MarkerStatus() & SHOW_HISTORICAL_MARKERS)
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
}} // namespace ultraschall::reaper
