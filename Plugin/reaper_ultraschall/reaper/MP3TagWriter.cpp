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
   
   MP3_EXPORT_CONTEXT* context = MP3_StartTransaction(targetName);
   if(context != nullptr)
   {
      success = MP3_InsertPodcastFrame(context);
      if(true == success)
      {
         success = MP3_InsertTextFrame(context, "TIT2", tokens[0]); // title
      }
      
      if(true == success)
      {
         success = MP3_InsertTextFrame(context, "TPE1", tokens[1]); // artist
      }
      
      if(true == success)
      {
         success = MP3_InsertTextFrame(context, "TALB", tokens[2]); // album
      }

      if(true == success)
      {
         success = MP3_InsertTextFrame(context, "TDRC", tokens[3]); // date
      }

      if(true == success)
      {
         success = MP3_InsertTextFrame(context, "TCON", tokens[4]); // genre
      }

      if(true == success)
      {
         if(tokens.size() > 5)
         {
            success = MP3_InsertCommentsFrame(context, "COMM", tokens[5]); // comment
         }
      }

      if(true == success)
      {
         success = MP3_CommitTransaction(context);
      }
      else
      {
         MP3_AbortTransaction(context);
      }
   }
   
   return success;
}
   
bool MP3TagWriter::InsertCoverImage(const std::string& targetName, const std::string& coverImage)
{
   PRECONDITION_RETURN(targetName.empty() == false, false);
   PRECONDITION_RETURN(coverImage.empty() == false, false);
   
   bool success = false;
   
   MP3_EXPORT_CONTEXT* context = MP3_StartTransaction(targetName);
   if(context != nullptr)
   {
      success = MP3_InsertCoverPictureFrame(context, coverImage);
      if(true == success)
      {
         success = MP3_CommitTransaction(context);
      }
      else
      {
         MP3_AbortTransaction(context);
      }
   }
   
   return success;
}

bool MP3TagWriter::InsertChapterMarkers(const std::string& targetName, const std::vector<Marker>& chapterMarkers, const bool replace)
{
   PRECONDITION_RETURN(targetName.empty() == false, false);
   PRECONDITION_RETURN(chapterMarkers.empty() == false, false);
   
   const uint32_t targetDuration = MP3_QueryTargetDuration(targetName);
   PRECONDITION_RETURN(targetDuration > 0, false);
   
   bool success = false;
   
   MP3_EXPORT_CONTEXT* context = MP3_StartTransaction(targetName);
   if(context != nullptr)
   {
      if(true == replace)
      {
         MP3_RemoveFrames(context, "CHAP");
      }
      
      std::vector<std::string> tableOfContentsItems;
      success = true;
      for(size_t i = 0; (i < chapterMarkers.size()) && (true == success); i++)
      {
         std::stringstream chapterId;
         chapterId << "chp" << i;
         std::string tableOfContensItem = chapterId.str();
         tableOfContentsItems.push_back(tableOfContensItem);
         
         const uint32_t startTime = static_cast<uint32_t>(chapterMarkers[i].Position() * 1000);
         const uint32_t endTime = (i < (chapterMarkers.size() - 1)) ? static_cast<uint32_t>(chapterMarkers[i + 1].Position() * 1000) : targetDuration;
         success = MP3_InsertChapterFrame(context, tableOfContensItem, chapterMarkers[i].Name(), startTime, endTime);
      }

      if(true == success)
      {
         success = MP3_InsertTableOfContentsFrame(context, tableOfContentsItems);
      }
      
      if(true == success)
      {
         success = MP3_CommitTransaction(context);
      }
      else
      {
         MP3_AbortTransaction(context);
      }
   }
   
   return success;
}

}}




