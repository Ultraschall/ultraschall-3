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

#include <cstring>

#include "ISOBMFF.h"
#include "Common.h"
#include "FileManager.h"
#include "Marker.h"
#include "PictureUtilities.h"

#define MP4V2_EXPORTS 0
#define MP4V2_NO_STDINT_DEFS 1
#include <mp4v2/mp4v2.h>

namespace ultraschall { namespace reaper { namespace isobmff {

Context* StartTransaction(const UnicodeString& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, 0);

    return new Context(targetName);
}

bool CommitTransaction(Context*& context)
{
    PRECONDITION_RETURN(context->IsValid(), false);

    const bool success = MP4TagsStore(context->Tags(), context->Target());
    SafeDelete(context);

    return success;
}

void AbortTransaction(Context*& context)
{
    SafeDelete(context);
}

static MP4TagArtworkType QueryArtworkType(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != nullptr, MP4_ART_UNDEFINED);
    PRECONDITION_RETURN(dataSize > 0, MP4_ART_UNDEFINED);

    MP4TagArtworkType mp4_format = MP4_ART_UNDEFINED;

    switch(QueryPictureFormat(data, dataSize))
    {
        case PICTURE_FORMAT::JPEG_PICTURE:
        {
            mp4_format = MP4_ART_JPEG;
            break;
        }
        case PICTURE_FORMAT::PNG_PICTURE:
        {
            mp4_format = MP4_ART_PNG;
            break;
        }
        default:
        {
            break;
        }
    }

    return mp4_format;
}

static double QueryDuration(const Context* context)
{
    PRECONDITION_RETURN(context != nullptr, -1);
    PRECONDITION_RETURN(context->IsValid(), -1);

    const uint32_t    scale    = MP4GetTimeScale(context->Target());
    const MP4Duration duration = MP4GetDuration(context->Target());

    return static_cast<double>(duration / scale);
}

static std::vector<MP4Chapter_t> ConvertChapters(const MarkerArray& chapterMarkers, const double maxDuration)
{
    PRECONDITION_RETURN(chapterMarkers.empty() == false, std::vector<MP4Chapter_t>());
    PRECONDITION_RETURN(maxDuration >= 0, std::vector<MP4Chapter_t>());

    std::vector<MP4Chapter_t> result;

    // mp4v2 library has a define named MP4V2_CHAPTER_TITLE_MAX which is 1023
    // However when mp4v2 library is writing Nero chapter in MP4File::AddNeroChapter() the title
    // will be further truncated to 255 byte length disregarding any possible utf8 multi-byte characters.
    // So we have to take care of properly truncating to that size ourselves beforehand.
    // This function does not do so itself but expects such truncated input.
    const size_t maxTitleBytes = std::min(255, MP4V2_CHAPTER_TITLE_MAX);
    double       currentStart  = 0;
    for(size_t i = 0; i < chapterMarkers.size(); i++)
    {
        double currentDuration = (i == chapterMarkers.size() - 1) ?
                                     maxDuration :
                                     chapterMarkers[i + 1].Position() - chapterMarkers[i].Position();

        // if we run over the total size clients (like VLC) may get confused
        if(currentStart + currentDuration > maxDuration)
        {
            currentDuration = maxDuration - currentStart;
        }

        MP4Chapter_t currentChapter     = {0};
        currentChapter.duration         = static_cast<uint32_t>(currentDuration * 1000);
        const UnicodeString& markerName = chapterMarkers[i].Name();
        if(markerName.empty() == false)
        {
            const size_t markerNameSize = std::min(markerName.size(), maxTitleBytes);
            memset(currentChapter.title, 0, (markerNameSize + 1) * sizeof(char));
            memmove(currentChapter.title, markerName.c_str(), markerNameSize);
            result.push_back(currentChapter);
        }

        currentStart += currentDuration;
    }

    return result;
}

bool InsertName(const Context* context, const UnicodeString& name)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(name.empty() == false, false);

    return MP4TagsSetName(context->Tags(), name.c_str());
}

bool InsertArtist(const Context* context, const UnicodeString& artist)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(artist.empty() == false, false);

    return MP4TagsSetArtist(context->Tags(), artist.c_str());
}

bool InsertAlbum(const Context* context, const UnicodeString& album)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(album.empty() == false, false);

    return MP4TagsSetAlbum(context->Tags(), album.c_str());
}

bool InsertReleaseDate(const Context* context, const UnicodeString& releaseDate)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(releaseDate.empty() == false, false);

    return MP4TagsSetReleaseDate(context->Tags(), releaseDate.c_str());
}

bool InsertGenre(const Context* context, const UnicodeString& genre)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(genre.empty() == false, false);

    return MP4TagsSetGenre(context->Tags(), genre.c_str());
}

bool InsertComments(const Context* context, const UnicodeString& comments)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(comments.empty() == false, false);

    return MP4TagsSetComments(context->Tags(), comments.c_str());
}

bool InsertCoverImage(const Context* context, const UnicodeString& file)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(file.empty() == false, false);

    bool result = false;

    BinaryStream* picture = FileManager::ReadBinaryFile(file);
    if(picture != nullptr)
    {
        MP4TagArtwork mp4ArtWork;
        mp4ArtWork.size = static_cast<uint32_t>(picture->DataSize());
        mp4ArtWork.data = const_cast<void*>(static_cast<const void*>(picture->Data()));
        mp4ArtWork.type = QueryArtworkType(picture->Data(), picture->DataSize());
        if(mp4ArtWork.type != MP4_ART_UNDEFINED)
        {
            bool removedAll = true;
            while((context->Tags()->artworkCount > 0) && (true == removedAll))
            {
                removedAll = MP4TagsRemoveArtwork(context->Tags(), 0);
            }

            if(true == removedAll)
            {
                result = MP4TagsAddArtwork(context->Tags(), &mp4ArtWork);
            }
        }

        SafeRelease(picture);
    }

    return result;
}

bool InsertChapterMarkers(const Context* context, const MarkerArray& markers)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(markers.empty() == false, false);

    bool result = false;

    const double duration = QueryDuration(context);
    if(duration >= 0) // this is safe!
    {
        std::vector<MP4Chapter_t> chapters = ConvertChapters(markers, duration);
        if(chapters.empty() == false)
        {
            const MP4ChapterType type = MP4SetChapters(
                context->Target(), &chapters[0], static_cast<uint32_t>(chapters.size()), MP4ChapterTypeAny);
            if(MP4ChapterTypeAny == type)
            {
                result = true;
            }
        }
    }

    return result;
}

}}} // namespace ultraschall::reaper::isobmff


