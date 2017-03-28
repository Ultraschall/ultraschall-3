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

void RemoveMP3Frames(const std::string& target, const std::string& frameId);

bool SaveMP3File(TagLib::MPEG::File& file)
{
   return file.save(TagLib::MPEG::File::ID3v2, true, 3);
}
   
void RemoveMultipleFrames(TagLib::ID3v2::Tag* parent, const std::string& id)
{
   PRECONDITION(parent != nullptr);
   PRECONDITION(id.empty() == false);
   
   std::vector<id3v2::Frame*> selectedFrames;
   
   TagLib::ID3v2::FrameList frames = parent->frameList(id.c_str());
   for(unsigned int i = 0; i < frames.size(); i++)
   {
      id3v2::Frame* frame = frames[i];
      if(frame != nullptr)
      {
         selectedFrames.push_back(frame);
      }
   }
   
   if(selectedFrames.empty() == false)
   {
      for(size_t j = 0; j < selectedFrames.size(); j ++)
      {
         parent->removeFrame(selectedFrames[j]);
      }
   }
}
   
bool InsertSingleTextFrame(TagLib::ID3v2::Tag* parent, const std::string& id, const std::string& text)
{
   PRECONDITION_RETURN(parent != nullptr, false);
   PRECONDITION_RETURN(id.empty() == false, false);
   PRECONDITION_RETURN(text.empty() == false, false);
   
   bool success = false;
   
   RemoveMultipleFrames(parent, id.c_str());
   
   const char* frameIdString = id.c_str();
   TagLib::ByteVector frameId = TagLib::ByteVector::fromCString(frameIdString);
   TagLib::ID3v2::TextIdentificationFrame* textFrame = new TagLib::ID3v2::TextIdentificationFrame(frameId);
   if(textFrame != nullptr)
   {
      framework::UnicodeString convertedString = framework::MakeUnicodeStringWithBOM(text);
      const char* rawStringData = reinterpret_cast<const char*>(convertedString.data());
      unsigned int rawStringSize =  static_cast<unsigned int>(convertedString.size() * sizeof(char16_t));
      TagLib::ByteVector stringData(rawStringData, rawStringSize);
      textFrame->setTextEncoding(TagLib::String::Type::UTF16);
      textFrame->setText(TagLib::String(stringData, TagLib::String::Type::UTF16));
      
      parent->addFrame(textFrame);
      success = true;
   }
   
   return success;
}
 
bool InsertSingleCommentsFrame(TagLib::ID3v2::Tag* parent, const std::string& id, const std::string& text)
{
   PRECONDITION_RETURN(parent != nullptr, false);
   PRECONDITION_RETURN(id.empty() == false, false);
   PRECONDITION_RETURN(text.empty() == false, false);
   
   bool success = false;
   
   RemoveMultipleFrames(parent, id.c_str());
   
   TagLib::ID3v2::CommentsFrame* commentsFrame = new TagLib::ID3v2::CommentsFrame(TagLib::String::Type::UTF16);
   if(commentsFrame != nullptr)
   {
      framework::UnicodeString convertedString = framework::MakeUnicodeStringWithBOM(text);
      TagLib::ByteVector stream((const char*)convertedString.c_str(), (unsigned int)(convertedString.size() * sizeof(char16_t)));
      commentsFrame->setLanguage(TagLib::ByteVector::fromCString("eng"));
      commentsFrame->setTextEncoding(TagLib::String::Type::UTF16);
      commentsFrame->setText(TagLib::String(stream, TagLib::String::Type::UTF16));
      
      parent->addFrame(commentsFrame);
      success = true;
   }
   
   return success;
}

bool InsertSingleChapterFrame(TagLib::ID3v2::Tag* parent, const std::string& id, const std::string& text, const uint32_t startTime, const uint32_t endTime)
{
   PRECONDITION_RETURN(parent != nullptr, false);
   PRECONDITION_RETURN(id.empty() == false, false);
   PRECONDITION_RETURN(text.empty() == false, false);
   PRECONDITION_RETURN(startTime != 0xffffffff, false);
   PRECONDITION_RETURN(endTime != 0xffffffff, false);
   
   bool success = false;
   
   const uint32_t startOffset = 0xffffffff;
   const uint32_t endOffset = 0xffffffff;
   TagLib::ByteVector chapterId = TagLib::ByteVector::fromCString(id.c_str());
   id3v2::ChapterFrame* chapterFrame = new id3v2::ChapterFrame(chapterId, startTime, endTime, startOffset, endOffset);
   if(chapterFrame != nullptr)
   {
      const char* embeddedFrameIdString = "TIT2";
      TagLib::ByteVector embeddedFrameId = TagLib::ByteVector::fromCString(embeddedFrameIdString);
      TagLib::ID3v2::TextIdentificationFrame* embeddedFrame = new TagLib::ID3v2::TextIdentificationFrame(embeddedFrameId);
      if(embeddedFrame != nullptr)
      {
         framework::UnicodeString convertedString = framework::MakeUnicodeStringWithBOM(text);
         TagLib::ByteVector rawStringData((const char*)convertedString.c_str(), (unsigned int)(convertedString.size() * sizeof(char16_t)));
         embeddedFrame->setTextEncoding(TagLib::String::Type::UTF16);
         embeddedFrame->setText(TagLib::String(rawStringData, TagLib::String::Type::UTF16));
      
         chapterFrame->addEmbeddedFrame(embeddedFrame);
         parent->addFrame(chapterFrame);
         
         success = true;
      }
   }

   return success;
}
   
bool InsertSingleTableOfContentsFrame(TagLib::ID3v2::Tag* parent, const std::vector<std::string>& tableOfContentsItems)
{
   PRECONDITION_RETURN(parent != nullptr, false);
   PRECONDITION_RETURN(tableOfContentsItems.empty() == false, false);
   
   bool success = false;
   
   RemoveMultipleFrames(parent, "CTOC");
   
   TagLib::ByteVector tableOfContentsId = TagLib::ByteVector::fromCString("toc");
   TagLib::ID3v2::TableOfContentsFrame* tableOfContentsFrame = new TagLib::ID3v2::TableOfContentsFrame(tableOfContentsId);
   if(tableOfContentsFrame != nullptr)
   {
      for(size_t j = 0; j < tableOfContentsItems.size(); j++)
      {
         tableOfContentsFrame->addChildElement(TagLib::ByteVector::fromCString(tableOfContentsItems[j].c_str()));
      }
      
      id3v2::TextIdentificationFrame* embeddedFrame = new id3v2::TextIdentificationFrame(TagLib::ByteVector::fromCString("TIT2"));
      if(embeddedFrame != nullptr)
      {
         framework::UnicodeString convertedString = framework::MakeUnicodeStringWithBOM("toplevel toc");
         TagLib::ByteVector stream((const char*)convertedString.c_str(), (unsigned int)(convertedString.size() * sizeof(char16_t)));
         embeddedFrame->setTextEncoding(TagLib::String::Type::UTF16);
         embeddedFrame->setText(TagLib::String(stream, TagLib::String::Type::UTF16));
         tableOfContentsFrame->addEmbeddedFrame(embeddedFrame);
      }
      
      parent->addFrame(tableOfContentsFrame);
      
      success = true;
   }
   
   return success;
}

bool InsertSinglePodcastFrame(TagLib::ID3v2::Tag* parent)
{
   PRECONDITION_RETURN(parent != nullptr, false);
   
   bool success = false;
   
   RemoveMultipleFrames(parent, "PCST");
   
   TagLib::ID3v2::PodcastFrame* podcastFrame = new TagLib::ID3v2::PodcastFrame();
   if(podcastFrame != nullptr)
   {
      parent->addFrame(podcastFrame);
      success = true;
   }
   
   return success;
}
   
bool InsertMP3Properties(const std::string& target, const std::string& properties)
{
   PRECONDITION_RETURN(target.empty() == false, false);
   PRECONDITION_RETURN(properties.empty() == false, false);
   std::vector<std::string> tokens = framework::StringTokenize(properties, '\n');
   PRECONDITION_RETURN(tokens.empty() == false, false);
   PRECONDITION_RETURN(tokens.size() >= 5, false);
   
   bool success = false;
   
   mp3::File mp3(target.c_str());
   if(mp3.isOpen() == true)
   {
      id3v2::Tag* tag = mp3.ID3v2Tag();
      if(tag != nullptr)
      {
         InsertSinglePodcastFrame(tag);
         
         InsertSingleTextFrame(tag, "TIT2", tokens[0]); // title
         InsertSingleTextFrame(tag, "TPE1", tokens[1]); // artist
         InsertSingleTextFrame(tag, "TALB", tokens[2]); // album
         InsertSingleTextFrame(tag, "TDRC", tokens[3]); // date
         InsertSingleTextFrame(tag, "TCON", tokens[4]); // genre
         
         if(tokens.size() > 5)
         {
            InsertSingleCommentsFrame(tag, "COMM", tokens[5]); // comment
         }
         
         success = SaveMP3File(mp3);
      }
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
   
bool InsertSingleCoverPictureFrame(TagLib::ID3v2::Tag* parent, const std::string& image)
{
   PRECONDITION_RETURN(parent != nullptr, false);
   PRECONDITION_RETURN(image.empty() == false, false);
   
   bool success = false;
   
   RemoveMultipleFrames(parent, "APIC");
   
   TagLib::ID3v2::AttachedPictureFrame *frame = new TagLib::ID3v2::AttachedPictureFrame();
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
               
               parent->addFrame(frame);
               
               success = true;
            }
         }
         
         SafeRelease(imageData);
      }
   }
   
   return success;
}

bool InsertMP3CoverPicture(const std::string& target, const std::string& image)
{
   PRECONDITION_RETURN(target.empty() == false, false);
   PRECONDITION_RETURN(image.empty() == false, false);
   
   bool success = false;
   
   TagLib::MPEG::File audioFile(target.c_str());
   if(audioFile.isOpen() == true)
   {
      TagLib::ID3v2::Tag* tag = audioFile.ID3v2Tag();
      if(tag != nullptr)
      {
         success = InsertSingleCoverPictureFrame(tag, image);
         if(true == success)
         {
            success = SaveMP3File(audioFile);
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
 
void RemoveMP3Frames(const std::string& target, const std::string& frameId)
{
   PRECONDITION(target.empty() == false);
   PRECONDITION(frameId.empty() == false);
   
   mp3::File mp3(target.c_str());
   if(mp3.isOpen() == true)
   {
      id3v2::Tag *id3v2 = mp3.ID3v2Tag();
      if(id3v2 != nullptr)
      {
         std::vector<id3v2::Frame*> foundFrames;
         
         id3v2::FrameList frames = id3v2->frameList(frameId.c_str());
         for(unsigned int i = 0; i < frames.size(); i++)
         {
            id3v2::Frame* frame = frames[i];
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
          
            SaveMP3File(mp3);
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
   
   bool success = false;
   
   mp3::File mp3(target.c_str());
   if(mp3.isOpen() == true)
   {
      id3v2::Tag *id3v2 = mp3.ID3v2Tag();
      if(id3v2 != nullptr)
      {
         RemoveMultipleFrames(id3v2, "CHAP");
         
         std::vector<std::string> tableOfContentsItems;

         for(size_t i = 0; i < tags.size(); i++)
         {
            std::stringstream chapterId;
            chapterId << "chp" << i;
            std::string tableOfContensItem = chapterId.str();
            tableOfContentsItems.push_back(tableOfContensItem);

            const uint32_t startTime = static_cast<uint32_t>(tags[i].Position() * 1000);
            const uint32_t endTime = (i < (tags.size() - 1)) ? static_cast<uint32_t>(tags[i + 1].Position() * 1000) : targetDuration;
            InsertSingleChapterFrame(id3v2, tableOfContensItem, tags[i].Name(), startTime, endTime);
         }
         
         InsertSingleTableOfContentsFrame(id3v2, tableOfContentsItems);
      }
      
      success = SaveMP3File(mp3);
   }

   return success;
}

}}
