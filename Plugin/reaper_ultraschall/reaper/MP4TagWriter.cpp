////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 Ultraschall ultraschall.fm
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

#include "MP4TagWriter.h"

#include "BinaryFileReader.h"
#include "StringUtilities.h"
#include "ImageTools.h"

#include <mp4v2/mp4v2.h>

namespace ultraschall { namespace reaper {
   
bool MP4TagWriter::InsertStandardProperties(const std::string& targetName, const StandardMediaProperties& standardProperties)
{
   PRECONDITION_RETURN(targetName.empty() == false, false);
   
   bool success = false;

   const MP4FileHandle mp4_handle = MP4Modify(targetName.c_str());
   if (mp4_handle)
   {
      const MP4Tags* tags = MP4TagsAlloc ();
      if (tags)
      {
         if (MP4TagsFetch( tags, mp4_handle))
         {
            success = MP4TagsSetName (tags, standardProperties.title.c_str());
            success &= MP4TagsSetArtist (tags, standardProperties.author.c_str());
            success &= MP4TagsSetAlbum (tags, standardProperties.track.c_str());
            success &= MP4TagsSetReleaseDate (tags, standardProperties.date.c_str());
            success &= MP4TagsSetGenre (tags, standardProperties.content.c_str());
            success &= MP4TagsSetComments (tags, standardProperties.comments.c_str());
      
            if (success == true)
            {
               success = MP4TagsStore(tags, mp4_handle);
            }
         }
         MP4TagsFree (tags);
      }

      MP4Close(mp4_handle);
   }

   return success;
}

static MP4TagArtworkType getMp4ImageFormat (const uint8_t* data, const size_t dataSize)
{
   MP4TagArtworkType mp4_format = MP4_ART_UNDEFINED;

   switch (FindImageFormat (data, dataSize))
   {
      case ImageFormat::Jpeg:
      {
         mp4_format = MP4_ART_JPEG;
         break;
      }
      case ImageFormat::Png:
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

bool MP4TagWriter::InsertCoverImage(const std::string& targetName, const std::string& coverImage)
{
   PRECONDITION_RETURN(targetName.empty() == false, false);
   PRECONDITION_RETURN(coverImage.empty() == false, false);
   
   bool success = false;

   MP4FileHandle mp4_handle = MP4Modify(targetName.c_str());
   if (mp4_handle)
   {
      const MP4Tags* tags = MP4TagsAlloc ();
      if (tags)
      {
         if (MP4TagsFetch( tags, mp4_handle))
         {
            framework::Stream* imageData = framework::BinaryFileReader::ReadBytes(coverImage);
            if(imageData != nullptr)
            {
               MP4TagArtwork mp4ArtWork;
               mp4ArtWork.size = static_cast<uint32_t> (imageData->DataSize());
               mp4ArtWork.data = const_cast<void*> (static_cast<const void*> (imageData->Data()));
               mp4ArtWork.type = getMp4ImageFormat (imageData->Data(), imageData->DataSize());

               if (mp4ArtWork.type != MP4_ART_UNDEFINED)
               {
                  bool removedAll = true;
                  while (tags->artworkCount > 0 && removedAll == true)
                  {
                     removedAll = MP4TagsRemoveArtwork (tags, 0);
                  }

                  if (removedAll)
                  {
                     if (MP4TagsAddArtwork(tags, &mp4ArtWork))
                     {
                        success = MP4TagsStore(tags, mp4_handle);
                     }
                  }
               }
            }
         }
         MP4TagsFree (tags);
      }

      MP4Close(mp4_handle);
   }

   return success;
}


static double getMp4TimeInSeconds (MP4FileHandle mp4_file)
{
   const uint32_t scale = MP4GetTimeScale (mp4_file);
   const MP4Duration duration = MP4GetDuration (mp4_file);

   return static_cast<double> (duration / scale);
}

static std::vector<MP4Chapter_t> convertToMp4Chapters (const std::vector<Marker>& chapterMarkers, double full_duration)
{
   // mp4v2 library has a define named MP4V2_CHAPTER_TITLE_MAX which is 1023
   // However when mp4v2 library is writing Nero chapter in MP4File::AddNeroChapter() the title
   // will be further truncated to 255 byte length disregarding any possible utf8 multibtye characters.
   // So we have to take care of properly truncating to that size ourselfes beforehand.
   // This function does not do so itself but expects such truncated input.
   const size_t maxTitleBytes = std::min (255, MP4V2_CHAPTER_TITLE_MAX);


   double current_chapter_start = 0.;
   std::vector<MP4Chapter_t> mp4_chapters;
   for (size_t i = 0; i < chapterMarkers.size(); i++)
   {
      double duration = (i == chapterMarkers.size() - 1) ? full_duration : chapterMarkers[i+1].Position()
                              - chapterMarkers[i].Position();

	  // if we run over the total size clients (like VLC) may get confused
      if (current_chapter_start + duration > full_duration)
         duration = full_duration - current_chapter_start;

      MP4Chapter_t chapter;
      {
         chapter.duration = static_cast<uint32_t> (duration * 1000.);

         const framework::UnicodeString2 title_utf8 = framework::MakeUTF8String2 (chapterMarkers[i].Name());
         const size_t size = std::min (title_utf8.size_, maxTitleBytes);

         memmove (chapter.title, title_utf8.data_, size);
         chapter.title[size] = 0;
      }
      mp4_chapters.push_back(chapter);

      current_chapter_start += duration;
   }

   return mp4_chapters;
}


bool MP4TagWriter::InsertChapterMarkers(const std::string& targetName, const std::vector<Marker>& chapterMarkers, const bool)
{
   PRECONDITION_RETURN(targetName.empty() == false, false);
   PRECONDITION_RETURN(chapterMarkers.empty() == false, false);

   bool success = false;

   MP4FileHandle mp4_file = MP4Modify(targetName.c_str());
   if (mp4_file)
   {
      const double full_duration = getMp4TimeInSeconds (mp4_file);
      auto mp4_chapters = convertToMp4Chapters (chapterMarkers, full_duration);

      const MP4ChapterType written = MP4SetChapters(mp4_file, &mp4_chapters[0], static_cast<uint32_t> (mp4_chapters.size()), MP4ChapterTypeAny);
      if (written == MP4ChapterTypeAny)
         success = true;

      MP4Close(mp4_file);
   }

   return success;
}
   
}}





