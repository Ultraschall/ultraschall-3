////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016 Ultraschall (http://ultraschall.fm)
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

#include "MP3Properties.h"
#include "StringUtilities.h"
#include "taglib_include.h"

namespace ultraschall {
namespace reaper {

bool InsertMP3Properties(const std::string& target, const std::string& properties)
{
   PRECONDITION_RETURN(target.empty() == false, false);
   PRECONDITION_RETURN(properties.empty() == false, false);
   std::vector<std::string> tokens = framework::split(properties, '\n');
   PRECONDITION_RETURN(tokens.empty() == false, false);
   PRECONDITION_RETURN(tokens.size() == 6, false);
   
   bool success = false;
   
   TagLib::FileRef mp3(target.c_str());
   if((mp3.isNull() == false) && (mp3.tag() != nullptr))
   {
      TagLib::Tag* tags = mp3.tag();
      tags->setTitle(TagLib::String(tokens[0], TagLib::String::Type::UTF8));
      tags->setArtist(TagLib::String(tokens[1], TagLib::String::Type::UTF8));
      tags->setAlbum(TagLib::String(tokens[2], TagLib::String::Type::UTF8));
      tags->setGenre(TagLib::String(tokens[4], TagLib::String::Type::UTF8));
      tags->setComment(TagLib::String(tokens[5], TagLib::String::Type::UTF8));
      
      std::istringstream is(tokens[3]);
      unsigned int year = -1;
      is >> year;
      tags->setYear(year);
      
      success = mp3.save();
   }

   return success;
}

uint32_t QueryTargetDuration(const std::string& target)
{
   PRECONDITION_RETURN(target.empty() == false, -1);
   
   uint32_t duration = -1;
   
   TagLib::FileRef mp3(target.c_str());
   if((mp3.isNull() == false) && (mp3.audioProperties() != nullptr))
   {
      
      TagLib::AudioProperties* properties = mp3.audioProperties();
      if(properties != nullptr)
      {
         duration = properties->length() * 1000;
      }
   }
   
   return duration;
}
   
bool InsertMP3Tags(const std::string& target, const std::vector<Marker> tags)
{
   PRECONDITION_RETURN(target.empty() == false, false);
   PRECONDITION_RETURN(tags.empty() == false, false);
   const uint32_t targetDuration = QueryTargetDuration(target);
   PRECONDITION_RETURN(targetDuration > 0, false);
   
   bool success = false;
   
   mp3::File mp3(target.c_str());
   if(mp3.isOpen() == true)
   {
      for(size_t i = 0; i < tags.size(); i++)
      {
         const uint32_t start = static_cast<uint32_t>(tags[i].Position() * 1000);
         const uint32_t end = (i < (tags.size() - 1)) ? static_cast<uint32_t>(tags[i + 1].Position() * 1000) : targetDuration;
         
         id3v2::Tag *id3v2 = mp3.ID3v2Tag();
         id3v2::TextIdentificationFrame* embeddedFrame = new id3v2::TextIdentificationFrame(TagLib::ByteVector::fromCString("TIT2"), TagLib::String::Type::UTF8);
         embeddedFrame->setText(TagLib::String(tags[i].Name(), TagLib::String::Type::UTF8));
         
         std::stringstream str;
         str << "cp" << std::setw(2) << std::setfill('0') << i;
         TagLib::ByteVector elementId = TagLib::ByteVector::fromCString(str.str().c_str());
         id3v2::ChapterFrame* frame = new id3v2::ChapterFrame(elementId, start, end, 0, 0);
         frame->addEmbeddedFrame(embeddedFrame);
         id3v2->addFrame(frame);
      }
      
      success = mp3.save();
   }

   return success;
}

}}
