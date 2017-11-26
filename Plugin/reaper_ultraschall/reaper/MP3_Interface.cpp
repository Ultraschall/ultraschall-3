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

#include "MP3_Interface.h"
#include "StringUtilities.h"
#include "BinaryFileReader.h"
#include "ImageTools.h"

namespace ultraschall {
namespace reaper {
  
struct MP3_EXPORT_CONTEXT
{
   TagLib::MPEG::File targetFile_;
   TagLib::ID3v2::Tag* tag_;
   
   MP3_EXPORT_CONTEXT(const std::string& targetName) : targetFile_(targetName.c_str()), tag_(nullptr)
   {
      if(targetFile_.isOpen() == true)
      {
         tag_ = targetFile_.ID3v2Tag();
      }
   }
   
   ~MP3_EXPORT_CONTEXT()
   {
      tag_ = nullptr;
   }
};
   
static const char* MP3_QueryMIMEType(const uint8_t* data, const size_t dataSize);

MP3_EXPORT_CONTEXT* MP3_StartTransaction(const std::string& targetName)
{
   PRECONDITION_RETURN(targetName.empty() == false, nullptr);
   
   return new MP3_EXPORT_CONTEXT(targetName);
}

bool MP3_CommitTransaction(MP3_EXPORT_CONTEXT*& context)
{
   PRECONDITION_RETURN(context != nullptr, false);
   PRECONDITION_RETURN(context->tag_ != nullptr, false);
   
   const bool success = context->targetFile_.save(TagLib::MPEG::File::ID3v2, true, 3);
   framework::SafeDelete(context);
   
   return success;
}

void MP3_AbortTransaction(MP3_EXPORT_CONTEXT*& context)
{
   framework::SafeDelete(context);
}

const char* MP3_QueryMIMEType(const uint8_t* data, const size_t dataSize)
{
   PRECONDITION_RETURN(data != nullptr, nullptr);
   PRECONDITION_RETURN(dataSize > 0, nullptr);
   
   const char* mimeType = nullptr;

   switch (FindImageFormat (data, dataSize))
   {
      case ImageFormat::Jpeg:
      {
         mimeType = "image/jpeg";
         break;
      }
      case ImageFormat::Png:
      {
         mimeType = "image/png";
         break;
      }
      default:
      {
         break;
      }
   }

   return mimeType;
}
   
uint32_t MP3_QueryTargetDuration(const std::string& target)
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

void MP3_RemoveFrames(const std::string& target, const std::string& frameId)
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
            
//            FIXME
//            MP3_Commit(mp3);
         }
      }
   }
}
   
bool MP3_RemoveFrames(MP3_EXPORT_CONTEXT* context, const std::string& id)
{
   PRECONDITION_RETURN(context != nullptr, false);
   PRECONDITION_RETURN(context->tag_ != nullptr, false);
   PRECONDITION_RETURN(id.empty() == false, false);
   
   bool success = false;
   
   std::vector<id3v2::Frame*> selectedFrames;
   
   TagLib::ID3v2::FrameList frames = context->tag_->frameList(id.c_str());
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
         context->tag_->removeFrame(selectedFrames[j]);
      }
      
      success = true;
   }
   
   return success;
}
   
bool MP3_InsertTextFrame(MP3_EXPORT_CONTEXT* context, const std::string& id, const std::string& text)
{
   PRECONDITION_RETURN(context != nullptr, false);
   PRECONDITION_RETURN(context->tag_ != nullptr, false);
   PRECONDITION_RETURN(id.empty() == false, false);
   PRECONDITION_RETURN(text.empty() == false, false);
   
   bool success = false;
   
   MP3_RemoveFrames(context, id.c_str());
   
   const char* frameIdString = id.c_str();
   TagLib::ByteVector frameId = TagLib::ByteVector::fromCString(frameIdString);
   TagLib::ID3v2::TextIdentificationFrame* textFrame = new TagLib::ID3v2::TextIdentificationFrame(frameId);
   if(textFrame != nullptr)
   {
      framework::UnicodeString convertedString = framework::MakeUTF16StringWithBOM(text);
      const char* rawStringData = reinterpret_cast<const char*>(convertedString.data());
      unsigned int rawStringSize =  static_cast<unsigned int>(convertedString.size() * sizeof(char16_t));
      TagLib::ByteVector stringData(rawStringData, rawStringSize);
      textFrame->setTextEncoding(TagLib::String::Type::UTF16);
      textFrame->setText(TagLib::String(stringData, TagLib::String::Type::UTF16));
      
      context->tag_->addFrame(textFrame);
      success = true;
   }
   
   return success;
}
 
bool MP3_InsertCommentsFrame(MP3_EXPORT_CONTEXT* context, const std::string& id, const std::string& text)
{
   PRECONDITION_RETURN(context != nullptr, false);
   PRECONDITION_RETURN(context->tag_ != nullptr, false);
   PRECONDITION_RETURN(id.empty() == false, false);
   PRECONDITION_RETURN(text.empty() == false, false);
   
   bool success = false;
   
   MP3_RemoveFrames(context, id.c_str());
   
   TagLib::ID3v2::CommentsFrame* commentsFrame = new TagLib::ID3v2::CommentsFrame(TagLib::String::Type::UTF16);
   if(commentsFrame != nullptr)
   {
      framework::UnicodeString convertedString = framework::MakeUTF16StringWithBOM(text);
      TagLib::ByteVector stream((const char*)convertedString.c_str(), (unsigned int)(convertedString.size() * sizeof(char16_t)));
      commentsFrame->setLanguage(TagLib::ByteVector::fromCString("eng"));
      commentsFrame->setTextEncoding(TagLib::String::Type::UTF16);
      commentsFrame->setText(TagLib::String(stream, TagLib::String::Type::UTF16));
      
      context->tag_->addFrame(commentsFrame);
      success = true;
   }
   
   return success;
}

bool MP3_InsertChapterFrame(MP3_EXPORT_CONTEXT* context, const std::string& id, const std::string& text, const uint32_t startTime, const uint32_t endTime)
{
   PRECONDITION_RETURN(context != nullptr, false);
   PRECONDITION_RETURN(context->tag_ != nullptr, false);
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
         framework::UnicodeString convertedString = framework::MakeUTF16StringWithBOM(text);
         TagLib::ByteVector rawStringData((const char*)convertedString.c_str(), (unsigned int)(convertedString.size() * sizeof(char16_t)));
         embeddedFrame->setTextEncoding(TagLib::String::Type::UTF16);
         embeddedFrame->setText(TagLib::String(rawStringData, TagLib::String::Type::UTF16));
      
         chapterFrame->addEmbeddedFrame(embeddedFrame);
         context->tag_->addFrame(chapterFrame);
         
         success = true;
      }
   }

   return success;
}
   
bool MP3_InsertTableOfContentsFrame(MP3_EXPORT_CONTEXT* context, const std::vector<std::string>& tableOfContentsItems)
{
   PRECONDITION_RETURN(context != nullptr, false);
   PRECONDITION_RETURN(context->tag_ != nullptr, false);
   PRECONDITION_RETURN(tableOfContentsItems.empty() == false, false);
   
   bool success = false;
   
   MP3_RemoveFrames(context, "CTOC");
   
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
         framework::UnicodeString convertedString = framework::MakeUTF16StringWithBOM("toplevel toc");
         TagLib::ByteVector stream((const char*)convertedString.c_str(), (unsigned int)(convertedString.size() * sizeof(char16_t)));
         embeddedFrame->setTextEncoding(TagLib::String::Type::UTF16);
         embeddedFrame->setText(TagLib::String(stream, TagLib::String::Type::UTF16));
         tableOfContentsFrame->addEmbeddedFrame(embeddedFrame);
      }
      
      context->tag_->addFrame(tableOfContentsFrame);
      
      success = true;
   }
   
   return success;
}

bool MP3_InsertPodcastFrame(MP3_EXPORT_CONTEXT* context)
{
   PRECONDITION_RETURN(context != nullptr, false);
   PRECONDITION_RETURN(context->tag_ != nullptr, false);

   bool success = false;
   
   MP3_RemoveFrames(context, "PCST");
   
   TagLib::ID3v2::PodcastFrame* podcastFrame = new TagLib::ID3v2::PodcastFrame();
   if(podcastFrame != nullptr)
   {
      context->tag_->addFrame(podcastFrame);
      success = true;
   }
   
   return success;
}
   
bool MP3_InsertCoverPictureFrame(MP3_EXPORT_CONTEXT* context, const std::string& image)
{
   PRECONDITION_RETURN(context != nullptr, false);
   PRECONDITION_RETURN(context->tag_ != nullptr, false);
   PRECONDITION_RETURN(image.empty() == false, false);
   
   bool success = false;
   
   MP3_RemoveFrames(context, "APIC");
   
   TagLib::ID3v2::AttachedPictureFrame *frame = new TagLib::ID3v2::AttachedPictureFrame();
   if(frame != nullptr)
   {
      framework::Stream* imageData = framework::BinaryFileReader::ReadBytes(image);
      if(imageData != nullptr)
      {
         uint8_t imageHeader[10] = {0};
         const size_t imageHeaderSize = 10;
         if(imageData->Read(0, imageHeader, imageHeaderSize) == true)
         {
            const std::string mimeType = MP3_QueryMIMEType(imageHeader, imageHeaderSize);
            if(mimeType.empty() == false)
            {
               frame->setMimeType(mimeType);
               TagLib::ByteVector coverData((const char*)imageData->Data(), (unsigned int)imageData->DataSize());
               frame->setPicture(coverData);
               
               context->tag_->addFrame(frame);
               
               success = true;
            }
         }
         
         SafeRelease(imageData);
      }
   }
   
   return success;
}

}}
