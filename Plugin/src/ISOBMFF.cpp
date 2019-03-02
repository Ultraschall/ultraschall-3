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

#include "ISOBMFF.h"
#include "Common.h"
#include "FileManager.h"
#include "Marker.h"
#include "PictureUtilities.h"

#define MP4V2_EXPORTS 0
#define MP4V2_NO_STDINT_DEFS 1
#include <mp4v2/mp4v2.h>

namespace ultraschall { namespace reaper { namespace isobmff {

struct TargetContext
{
    MP4FileHandle  target_;
    const MP4Tags* tags_;

    TargetContext(const UnicodeString& targetName) : target_(nullptr), tags_(nullptr)
    {
        bool initialized = false;

        target_ = MP4Modify(targetName.c_str());
        if(target_ != nullptr)
        {
            tags_ = MP4TagsAlloc();
            if(tags_ != nullptr)
            {
                initialized = MP4TagsFetch(tags_, target_);
            }
        }

        if(initialized != true)
        {
            Reset();
        }
    }

    ~TargetContext()
    {
        Reset();
    }

    inline bool IsValid() const
    {
        return (target_ != nullptr) && (tags_ != nullptr);
    }

    void Reset()
    {
        if(tags_ != nullptr)
        {
            MP4TagsFree(tags_);
            tags_ = nullptr;
        }

        if(target_ != nullptr)
        {
            MP4Close(target_);
            target_ = nullptr;
        }
    }

    TargetContext(const TargetContext&) = delete;
    TargetContext& operator=(const TargetContext&) = delete;
};

TargetContext* StartTransaction(const UnicodeString& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, 0);

    return new TargetContext(targetName);
}

bool CommitTransaction(TargetContext*& context)
{
    PRECONDITION_RETURN(context->IsValid(), false);

    const bool success = MP4TagsStore(context->tags_, context->target_);
    SafeDelete(context);

    return success;
}

void AbortTransaction(TargetContext*& context)
{
    SafeDelete(context);
}

static MP4TagArtworkType QueryArtworkType(const uint8_t* data, const size_t dataSize)
{
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

static double QueryDuration(const TargetContext* context)
{
    PRECONDITION_RETURN(context != nullptr, -1);
    PRECONDITION_RETURN(context->IsValid(), -1);

    const uint32_t    scale    = MP4GetTimeScale(context->target_);
    const MP4Duration duration = MP4GetDuration(context->target_);

    return static_cast<double>(duration / scale);
}

static std::vector<MP4Chapter_t> ConvertChapters(const MarkerArray& chapterMarkers, const double duration)
{
    // mp4v2 library has a define named MP4V2_CHAPTER_TITLE_MAX which is 1023
    // However when mp4v2 library is writing Nero chapter in MP4File::AddNeroChapter() the title
    // will be further truncated to 255 byte length disregarding any possible utf8 multi-byte characters.
    // So we have to take care of properly truncating to that size ourselves beforehand.
    // This function does not do so itself but expects such truncated input.

    const size_t maxTitleBytes = std::min(255, MP4V2_CHAPTER_TITLE_MAX);

    double                    current_chapter_start = 0.;
    std::vector<MP4Chapter_t> mp4_chapters;
    for(size_t i = 0; i < chapterMarkers.size(); i++)
    {
        double duration = (i == chapterMarkers.size() - 1) ?
                              duration :
                              chapterMarkers[i + 1].Position() - chapterMarkers[i].Position();

        // if we run over the total size clients (like VLC) may get confused
        if(current_chapter_start + duration > duration)
            duration = duration - current_chapter_start;

        MP4Chapter_t chapter;
        {
            chapter.duration = static_cast<uint32_t>(duration * 1000.0);

            const UnicodeString& markerName = chapterMarkers[i].Name();
            if(markerName.empty() == false)
            {
                const size_t markerNameSize = std::min(markerName.size(), maxTitleBytes);
                memset(chapter.title, 0, (markerNameSize + 1) * sizeof(char));
                memmove(chapter.title, markerName.c_str(), markerNameSize);
                chapter.title[markerNameSize] = '\0';
            }
        }
        mp4_chapters.push_back(chapter);

        current_chapter_start += duration;
    }

    return mp4_chapters;
}

bool InsertName(const TargetContext* context, const UnicodeString& name)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(name.empty() == false, false);

    return MP4TagsSetName(context->tags_, name.c_str());
}

bool InsertArtist(const TargetContext* context, const UnicodeString& artist)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(artist.empty() == false, false);

    return MP4TagsSetArtist(context->tags_, artist.c_str());
}

bool InsertAlbum(const TargetContext* context, const UnicodeString& album)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(album.empty() == false, false);

    return MP4TagsSetAlbum(context->tags_, album.c_str());
}

bool InsertReleaseDate(const TargetContext* context, const UnicodeString& releaseDate)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(releaseDate.empty() == false, false);

    return MP4TagsSetReleaseDate(context->tags_, releaseDate.c_str());
}

bool InsertGenre(const TargetContext* context, const UnicodeString& genre)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(genre.empty() == false, false);

    return MP4TagsSetGenre(context->tags_, genre.c_str());
}

bool InsertComments(const TargetContext* context, const UnicodeString& comments)
{
    PRECONDITION_RETURN(context != nullptr, false);
    PRECONDITION_RETURN(context->IsValid() != false, false);
    PRECONDITION_RETURN(comments.empty() == false, false);

    return MP4TagsSetComments(context->tags_, comments.c_str());
}

bool InsertCoverImage(const TargetContext* context, const UnicodeString& file)
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
            while((context->tags_->artworkCount > 0) && (true == removedAll))
            {
                removedAll = MP4TagsRemoveArtwork(context->tags_, 0);
            }

            if(true == removedAll)
            {
                result = MP4TagsAddArtwork(context->tags_, &mp4ArtWork);
            }
        }

        SafeRelease(picture);
    }

    return result;
}

bool InsertChapterMarkers(const TargetContext* context, const MarkerArray& markers)
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
                context->target_, &chapters[0], static_cast<uint32_t>(chapters.size()), MP4ChapterTypeAny);
            if(MP4ChapterTypeAny == type)
            {
                result = true;
            }
        }
    }

    return result;
}

}}} // namespace ultraschall::reaper::isobmff
