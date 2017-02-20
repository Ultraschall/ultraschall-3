////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 Ultraschall (http://ultraschall.fm)
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
#include "BinaryFileReader.h"
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

      std::string title = framework::AnsiStringToUnicodeString(tokens[0]);
      tags->setTitle(TagLib::String(title, TagLib::String::Type::UTF8));

      std::string artist = framework::AnsiStringToUnicodeString(tokens[1]);
      tags->setArtist(TagLib::String(artist, TagLib::String::Type::UTF8));

      std::string album = framework::AnsiStringToUnicodeString(tokens[2]);
      tags->setAlbum(TagLib::String(album, TagLib::String::Type::UTF8));

      std::string genre = framework::AnsiStringToUnicodeString(tokens[4]);
      tags->setGenre(TagLib::String(genre, TagLib::String::Type::UTF8));

      std::string comment = framework::AnsiStringToUnicodeString(tokens[5]);
      tags->setComment(TagLib::String(comment, TagLib::String::Type::UTF8));
      
      std::istringstream is(tokens[3]);
      unsigned int year = 0;
      is >> year;
      tags->setYear(year);
      
      success = mp3.save();
   }

   return success;
}

std::string QueryMIMEType(const uint8_t* data, const size_t dataSize)
{
   PRECONDITION_RETURN(data != nullptr, std::string());
   PRECONDITION_RETURN(dataSize > 0, std::string());
   
   std::string mimeType;
   
   if(dataSize >= 2)
   {
      if((data[0] == 0xff) && (data[1] == 0xd8))
      {
         mimeType = "image/jpeg";
      }
      
      if(dataSize >= 8)
      {
         if((data[0] == 0x89) && (data[1] == 0x50) && (data[2] == 0x4e) && (data[3] == 0x47))
         {
            mimeType = "image/png";
         }
      }
   }
   
   return mimeType;
}
   
bool InsertMP3Cover(const std::string& target, const std::string& image)
{
   PRECONDITION_RETURN(target.empty() == false, false);
   PRECONDITION_RETURN(image.empty() == false, false);
   
   bool success = false;
   
   TagLib::MPEG::File audioFile(target.c_str());
   
   TagLib::ID3v2::Tag *tag = audioFile.ID3v2Tag(true);
   if(tag != nullptr)
   {
      TagLib::ID3v2::AttachedPictureFrame *frame = new TagLib::ID3v2::AttachedPictureFrame;
      if(frame != nullptr)
      {
         framework::Stream<uint8_t>* imageData = framework::BinaryFileReader::ReadBytes(image);
         if(imageData != nullptr)
         {
            uint8_t imageHeader[10] = {0};
            const size_t imageHeaderSize = 10;
            if(imageData->Read(0, imageHeader, imageHeaderSize) == true)
            {
               const std::string mimeType = QueryMIMEType(imageHeader, imageHeaderSize);
               if(mimeType.empty() == false)
               {
                  frame->setMimeType(mimeType);
                  
                  TagLib::ByteVector coverData((const char*)imageData->Data(), (unsigned int)imageData->DataSize());
                  frame->setPicture(coverData);
                  tag->addFrame(frame);
                  success = audioFile.save();
               }
            }
            
            SafeRelease(imageData);
         }
      }
   }
   
   return success;
}
   
uint32_t QueryTargetDuration(const std::string& target)
{
   PRECONDITION_RETURN(target.empty() == false, static_cast<uint32_t>(-1));
   
   uint32_t duration = 0;
   
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
 
void RemoveMP3Tags(const std::string& target)
{
   PRECONDITION(target.empty() == false);

   mp3::File mp3(target.c_str());
   if(mp3.isOpen() == true)
   {
      id3v2::Tag *id3v2 = mp3.ID3v2Tag();
      if(id3v2 != nullptr)
      {
         std::vector<id3v2::ChapterFrame*> foundFrames;
         
         id3v2::FrameList frames = id3v2->frameList("CHAP");
         for(unsigned int i = 0; i < frames.size(); i++)
         {
            id3v2::ChapterFrame* frame = dynamic_cast<id3v2::ChapterFrame*>(frames[i]);
            if(frame != nullptr)
            {
               foundFrames.push_back(frame);
            }
         }
         
         if(foundFrames.empty() == false)
         {
            for(size_t j = 0; j < foundFrames.size(); j ++)
            {
               id3v2->removeFrame(foundFrames[j]);
            }

            mp3.save();
         }
      }
   }
}
   
bool InsertMP3Tags(const std::string& target, const std::vector<Marker> tags)
{
   PRECONDITION_RETURN(target.empty() == false, false);
   PRECONDITION_RETURN(tags.empty() == false, false);
   const uint32_t targetDuration = QueryTargetDuration(target);
   PRECONDITION_RETURN(targetDuration > 0, false);
   
   RemoveMP3Tags(target);
   
   bool success = false;
   
   mp3::File mp3(target.c_str());
   if(mp3.isOpen() == true)
   {
      id3v2::Tag *id3v2 = mp3.ID3v2Tag();
      if(id3v2 != nullptr)
      {
         for(size_t i = 0; i < tags.size(); i++)
         {
            const uint32_t start = static_cast<uint32_t>(tags[i].Position() * 1000);
            const uint32_t end = (i < (tags.size() - 1)) ? static_cast<uint32_t>(tags[i + 1].Position() * 1000) : targetDuration;
         
            id3v2::TextIdentificationFrame* embeddedFrame = new id3v2::TextIdentificationFrame(TagLib::ByteVector::fromCString("TIT2"), TagLib::String::Type::UTF8);
            if(embeddedFrame != nullptr)
            {
               embeddedFrame->setText(TagLib::String(tags[i].Name(), TagLib::String::Type::UTF8));

               std::stringstream str;
               str << "cp" << std::setw(2) << std::setfill('0') << i;
               TagLib::ByteVector elementId = TagLib::ByteVector::fromCString(str.str().c_str());
               id3v2::ChapterFrame* frame = new id3v2::ChapterFrame(elementId, start, end, 0, 0);
               if(frame != nullptr)
               {
                  frame->addEmbeddedFrame(embeddedFrame);
                  id3v2->addFrame(frame);
               }
            }
         }
      }
      
      success = mp3.save();
   }

   return success;
}

}}
