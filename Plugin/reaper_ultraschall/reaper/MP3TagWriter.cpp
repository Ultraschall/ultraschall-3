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

#include <sstream>
#include <iomanip>

#include "StringUtilities.h"

#include "MP3TagWriter.h"
#include "MP3_Interface.h"

namespace ultraschall { namespace reaper {

bool MP3TagWriter::InsertStandardProperties(const std::string& targetName, const std::string& standardProperties)
{
   PRECONDITION_RETURN(targetName.empty() == false, false);
   PRECONDITION_RETURN(standardProperties.empty() == false, false);

   std::vector<std::string> tokens = framework::StringTokenize(standardProperties, '\n');
   PRECONDITION_RETURN(tokens.empty() == false, false);
   PRECONDITION_RETURN(tokens.size() >= 5, false);
   
   bool success = false;
   
   mp3::File mp3(targetName.c_str());
   if(mp3.isOpen() == true)
   {
      id3v2::Tag* tag = mp3.ID3v2Tag();
      if(tag != nullptr)
      {
         MP3_InsertSinglePodcastFrame(tag);
         
         MP3_InsertSingleTextFrame(tag, "TIT2", tokens[0]); // title
         MP3_InsertSingleTextFrame(tag, "TPE1", tokens[1]); // artist
         MP3_InsertSingleTextFrame(tag, "TALB", tokens[2]); // album
         MP3_InsertSingleTextFrame(tag, "TDRC", tokens[3]); // date
         MP3_InsertSingleTextFrame(tag, "TCON", tokens[4]); // genre
         
         if(tokens.size() > 5)
         {
            MP3_InsertSingleCommentsFrame(tag, "COMM", tokens[5]); // comment
         }
         
         success = MP3_Commit(mp3);
      }
   }
   
   return success;
}
   
bool MP3TagWriter::InsertCoverImage(const std::string& targetName, const std::string& coverImage)
{
   PRECONDITION_RETURN(targetName.empty() == false, false);
   PRECONDITION_RETURN(coverImage.empty() == false, false);
   
   bool success = false;
   
   TagLib::MPEG::File audioFile(targetName.c_str());
   if(audioFile.isOpen() == true)
   {
      TagLib::ID3v2::Tag* tag = audioFile.ID3v2Tag();
      if(tag != nullptr)
      {
         success = MP3_InsertSingleCoverPictureFrame(tag, coverImage);
         if(true == success)
         {
            success = MP3_Commit(audioFile);
         }
      }
   }
   
   return success;
}

bool MP3TagWriter::InsertChapterMarkers(const std::string& targetName, const std::vector<Marker>& chapterMarkers)
{
   PRECONDITION_RETURN(targetName.empty() == false, false);
   PRECONDITION_RETURN(chapterMarkers.empty() == false, false);
   
   const uint32_t targetDuration = MP3_QueryTargetDuration(targetName);
   PRECONDITION_RETURN(targetDuration > 0, false);
   
   bool success = false;
   
   mp3::File mp3(targetName.c_str());
   if(mp3.isOpen() == true)
   {
      id3v2::Tag *id3v2 = mp3.ID3v2Tag();
      if(id3v2 != nullptr)
      {
         MP3_RemoveMultipleFrames(id3v2, "CHAP");
         
         std::vector<std::string> tableOfContentsItems;
         
         for(size_t i = 0; i < chapterMarkers.size(); i++)
         {
            std::stringstream chapterId;
            chapterId << "chp" << i;
            std::string tableOfContensItem = chapterId.str();
            tableOfContentsItems.push_back(tableOfContensItem);
            
            const uint32_t startTime = static_cast<uint32_t>(chapterMarkers[i].Position() * 1000);
            const uint32_t endTime = (i < (chapterMarkers.size() - 1)) ? static_cast<uint32_t>(chapterMarkers[i + 1].Position() * 1000) : targetDuration;
            MP3_InsertSingleChapterFrame(id3v2, tableOfContensItem, chapterMarkers[i].Name(), startTime, endTime);
         }
         
         MP3_InsertSingleTableOfContentsFrame(id3v2, tableOfContentsItems);
      }
      
      success = MP3_Commit(mp3);
   }
   
   return success;
}

}}




