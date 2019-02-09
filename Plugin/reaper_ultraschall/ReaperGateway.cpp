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

#include "ReaperGateway.h"
#include "FileManager.h"
#include "ReaperEntryPoints.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

const double ReaperGateway::INVALID_POSITION = -1;

uint32_t ReaperGateway::EditMarkerColor()
{
#ifdef _WIN32
    return 0x01ff0000;
#else  // #ifdef _WIN32
    return 0x010000ff;
#endif // #ifdef _WIN32
}

UnicodeString ReaperGateway::ApplicationVersion()
{
    return H2U(reaper_api::GetAppVersion());
}

int32_t ReaperGateway::RegisterCustomAction(const UnicodeString& name, void* infoStruct)
{
    PRECONDITION_RETURN(name.empty() == false, -1);

    return reaper_api::plugin_register(U2H(name).c_str(), infoStruct);
}

void ReaperGateway::LockUIRefresh(const bool lock)
{
    reaper_api::PreventUIRefresh((lock == true) ? 1 : -1);
}

UnicodeString ReaperGateway::ExportPathName()
{
    UnicodeString result;

    char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
    reaper_api::GetProjectPath(buffer, MAX_REAPER_STRING_BUFFER_SIZE);
    if(strlen(buffer) > 0)
    {
        result = buffer;
    }

    return result;
}

ProjectReference ReaperGateway::CurrentProject()
{
    return reinterpret_cast<ProjectReference>(reaper_api::EnumProjects(-1, 0, 0));
}

UnicodeString ReaperGateway::ProjectPathName()
{
    UnicodeString result;

    char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
    reaper_api::EnumProjects(-1, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
    if(strlen(buffer) > 0)
    {
        result = buffer;
    }

    return result;
}

UnicodeString ReaperGateway::ProjectFileName()
{
    UnicodeString result;

    const UnicodeString projectPath = ProjectPathName();
    if(projectPath.empty() == false)
    {
        const UnicodeStringArray pathComponents = FileManager::SplitPath(projectPath);
        if(pathComponents.empty() == false)
        {
            result = pathComponents[pathComponents.size() - 1];
        }
    }

    return result;
}

UnicodeString ReaperGateway::ProjectFolderName()
{
    UnicodeString result;

    const UnicodeString projectPath = ProjectPathName();
    if(projectPath.empty() == false)
    {
        const UnicodeStringArray pathComponents = FileManager::SplitPath(projectPath);
        if(pathComponents.empty() == false)
        {
            for(size_t i = 0; i < pathComponents.size() - 1; i++)
            {
                result += pathComponents[i];
                if(i < pathComponents.size() - 2)
                {
                    result += FileManager::PathSeparator();
                }
            }
        }
    }

    return result;
}

UnicodeString ReaperGateway::ProjectName()
{
    UnicodeString result;

    const UnicodeString projectFile = ProjectFileName();
    if(projectFile.empty() == false)
    {
        result = projectFile.substr(0, projectFile.find('.', 0));
    }

    return result;
}

struct Timestamp
{
    int hours;
    int minutes;
    int seconds;
    int milliSeconds;

    Timestamp() : hours(0), minutes(0), seconds(0), milliSeconds(0) {}

    static Timestamp FromString(const UnicodeString& str)
    {
        UnicodeStringArray items = UnicodeStringTokenize(str, ':');
        std::reverse(items.begin(), items.end());

        Timestamp timestamp;

        UnicodeStringArray buffer = UnicodeStringTokenize(items[0], '.');
        for(size_t i = 0; i < buffer.size(); ++i)
        {
            switch(i)
            {
                case 0:
                    timestamp.seconds = std::atoi(buffer[0].c_str());
                    break;

                case 1:
                    timestamp.milliSeconds = std::atoi(buffer[1].c_str());
                    break;

                default:
                    break;
            }
        }

        for(size_t i = 0; i < items.size(); ++i)
        {
            switch(i)
            {
                case 1:
                    timestamp.minutes = std::atoi(items[1].c_str());
                    break;

                case 2:
                    timestamp.hours = std::atoi(items[2].c_str());
                    break;

                default:
                    break;
            }
        }

        return timestamp;
    }

    UnicodeString ToString() const
    {
        std::stringstream buffer;
        buffer << std::setfill('0');
        buffer << std::setw(2) << hours << ":";
        buffer << std::setw(2) << minutes << ":";
        buffer << std::setw(2) << seconds << ".";
        buffer << std::setw(3) << milliSeconds;

        return buffer.str();
    }
};

UnicodeString ReaperGateway::TimestampToString(const double timestamp)
{
    UnicodeString result;

    char buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
    reaper_api::format_timestr_pos(timestamp, buffer, MAX_REAPER_STRING_BUFFER_SIZE, 0);
    if(strlen(buffer) > 0)
    {
        result = Timestamp::FromString(buffer).ToString();
    }

    return result;
}

double ReaperGateway::StringToTimestamp(const UnicodeString& input)
{
    PRECONDITION_RETURN(input.empty() == false, -1);
    return reaper_api::parse_timestr(input.c_str());
}

UnicodeString ReaperGateway::ProjectPath(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, UnicodeString());

    UnicodeString projectPath;

    ReaProject*         nativeReference                       = reinterpret_cast<ReaProject*>(projectReference);
    static const size_t MAX_REAPER_STRING_BUFFER_SIZE         = 4096;
    char                buffer[MAX_REAPER_STRING_BUFFER_SIZE] = {0};
    int                 index                                 = 0;
    ProjectReference    externalReference
        = (ProjectReference)reaper_api::EnumProjects(index++, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
    while((externalReference != 0) && (projectPath.empty() == true))
    {
        if(externalReference == nativeReference)
        {
            projectPath = H2U(buffer);
        }

        externalReference = (ProjectReference)reaper_api::EnumProjects(index++, buffer, MAX_REAPER_STRING_BUFFER_SIZE);
    }

    return projectPath;
}

UnicodeString ReaperGateway::ProjectNotes(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, UnicodeString());

    UnicodeString projectNotes;

    ReaProject*         nativeReference                = reinterpret_cast<ReaProject*>(projectReference);
    static const size_t MAX_PROJECT_NOTES_SIZE         = 4096;
    char                buffer[MAX_PROJECT_NOTES_SIZE] = {0};
    reaper_api::GetSetProjectNotes(nativeReference, false, buffer, (int)MAX_PROJECT_NOTES_SIZE);
    projectNotes = H2U(buffer);
    projectNotes.erase(std::remove(projectNotes.begin(), projectNotes.end(), '\r'), projectNotes.end());

    return projectNotes;
}

MarkerArray ReaperGateway::AllMarkers(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, MarkerArray());

    MarkerArray allMarkers;

    bool        isRegion = false;
    double      position = 0;
    double      duration = 0;
    const char* name     = 0;
    int         number   = 0;
    int         color    = 0;

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    int         nextIndex
        = reaper_api::EnumProjectMarkers3(nativeReference, 0, &isRegion, &position, &duration, &name, &number, &color);
    while(nextIndex > 0)
    {
        static const size_t MAX_CHAPTER_NAME_LENGTH = 62; // limitation in taglib/id3v2
        UnicodeString       markerName              = name;
        if(markerName.size() > MAX_CHAPTER_NAME_LENGTH)
        {
            markerName = markerName.substr(0, MAX_CHAPTER_NAME_LENGTH);
        }

        if(("_Edit" != markerName) &&                      // remove edit markers
           (false == isRegion) &&                          // remove regions
           (color != static_cast<int>(EditMarkerColor()))) // include only chapter markers
        {
            // TODO check whether reaper uses unicode or ansi
            allMarkers.push_back(Marker(position, markerName, color));
        }

        nextIndex = reaper_api::EnumProjectMarkers3(
            nativeReference, nextIndex, &isRegion, &position, &duration, &name, &number, &color);
    }

    return allMarkers;
}

size_t ReaperGateway::CountMarkers(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, false);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    int         numMarkers      = -1;
    reaper_api::CountProjectMarkers(nativeReference, &numMarkers, 0);
    return static_cast<size_t>(numMarkers);
}

bool ReaperGateway::ClearMarkers(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, false);

    ReaProject*  nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    const size_t numMarkers      = CountMarkers(projectReference);
    for(size_t i = 0; i < numMarkers; i++)
    {
        reaper_api::DeleteProjectMarkerByIndex(nativeReference, int(i));
    }

    return true;
} // namespace reaper

bool ReaperGateway::InsertMarker(ProjectReference projectReference, const UnicodeString& name, const double position)
{
    PRECONDITION_RETURN(projectReference != nullptr, false);
    PRECONDITION_RETURN(position >= 0, false);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    // TODO check whether reaper takes unicode or ansi
    return reaper_api::AddProjectMarker2(nativeReference, false, position, 0, name.c_str(), -1, 0) != -1;
}

bool ReaperGateway::InsertMarker(ProjectReference projectReference, const Marker& marker)
{
    PRECONDITION_RETURN(projectReference != nullptr, false);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    // TODO check whether reaper takes unicode or ansi
    return reaper_api::AddProjectMarker2(
               nativeReference, false, marker.Position(), 0, marker.Name().c_str(), -1, marker.Color())
           != -1;
}

bool ReaperGateway::UndoMarker(ProjectReference projectReference, const double position)
{
    PRECONDITION_RETURN(projectReference != nullptr, false);
    PRECONDITION_RETURN(position >= 0, false);

    bool        undone          = false;
    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    int         markerIndex     = -1;
    reaper_api::GetLastMarkerAndCurRegion(nativeReference, position, &markerIndex, 0);
    if(markerIndex != -1)
    {
        undone = reaper_api::DeleteProjectMarkerByIndex(nativeReference, markerIndex);
    }

    return undone;
}

int ReaperGateway::PlayState(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, -1);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    return reaper_api::GetPlayStateEx(nativeReference);
}

double ReaperGateway::CursorPosition(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, -1);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    return reaper_api::GetCursorPositionEx(nativeReference);
}

double ReaperGateway::PlayPosition(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, -1);

    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    return reaper_api::GetPlayPositionEx(nativeReference);
}

double ReaperGateway::MinPosition(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, -1);

    double minPosition = MaxPosition(projectReference);
    if(minPosition != INVALID_POSITION)
    {
        ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
        int         i               = 0;
        MediaItem*  mediaItem       = reaper_api::GetMediaItem(nativeReference, i++);
        while(mediaItem != 0)
        {
            double startPosition = reaper_api::GetMediaItemInfo_Value(mediaItem, "D_POSITION");
            if(startPosition < minPosition)
            {
                minPosition = startPosition;
            }
            mediaItem = reaper_api::GetMediaItem(nativeReference, i++);
        }
    }

    return minPosition;
}

double ReaperGateway::MaxPosition(ProjectReference projectReference)
{
    PRECONDITION_RETURN(projectReference != nullptr, -1);

    double      maxPosition     = INVALID_POSITION;
    ReaProject* nativeReference = reinterpret_cast<ReaProject*>(projectReference);
    int         i               = 0;
    MediaItem*  mediaItem       = reaper_api::GetMediaItem(nativeReference, i++);
    while(mediaItem != 0)
    {
        const double endPosition = reaper_api::GetMediaItemInfo_Value(mediaItem, "D_POSITION")
                                   + reaper_api::GetMediaItemInfo_Value(mediaItem, "D_LENGTH");
        if((endPosition >= 0) && (endPosition > maxPosition))
        {
            maxPosition = endPosition;
        }

        mediaItem = reaper_api::GetMediaItem(nativeReference, i++);
    }

    return maxPosition;
}

bool ReaperGateway::HasValue(const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION_RETURN(section.empty() == false, false);
    PRECONDITION_RETURN(key.empty() == false, false);

    return reaper_api::HasExtState(U2H(section).c_str(), U2H(key).c_str());
}

UnicodeString ReaperGateway::GetValue(const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION_RETURN(section.empty() == false, UnicodeString());
    PRECONDITION_RETURN(key.empty() == false, UnicodeString());

    return H2U(reaper_api::GetExtState(U2H(section).c_str(), U2H(key).c_str()));
}

void ReaperGateway::SetValue(const UnicodeString& section, const UnicodeString& key, const UnicodeString& value)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);
    PRECONDITION(value.empty() == false);

    reaper_api::SetExtState(U2H(section).c_str(), U2H(key).c_str(), U2H(value).c_str(), false);
}

void ReaperGateway::SaveValue(const UnicodeString& section, const UnicodeString& key, const UnicodeString& value)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);
    PRECONDITION(value.empty() == false);

    reaper_api::SetExtState(U2H(section).c_str(), U2H(key).c_str(), U2H(value).c_str(), true);
}

void ReaperGateway::ClearValue(const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    reaper_api::DeleteExtState(U2H(section).c_str(), U2H(key).c_str(), false);
}

void ReaperGateway::DeleteValue(const UnicodeString& section, const UnicodeString& key)
{
    PRECONDITION(section.empty() == false);
    PRECONDITION(key.empty() == false);

    reaper_api::DeleteExtState(U2H(section).c_str(), U2H(key).c_str(), true);
}

}} // namespace ultraschall::reaper
