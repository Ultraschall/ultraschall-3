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

#include "ID3V2.h"
#include "BinaryStream.h"
#include "FileManager.h"
#include "PictureUtilities.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper { namespace id3v2 {

Context* StartTransaction(const UnicodeString& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, 0);

    return new Context(targetName);
}

bool CommitTransaction(Context*& context)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);

    const bool success = context->Target()->save(taglib_mp3::File::ID3v2, true, 3);
    SafeDelete(context);

    return success;
}

void AbortTransaction(Context*& context)
{
    SafeDelete(context);
}

const char* QueryMIMEType(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, 0);
    PRECONDITION_RETURN(dataSize > 0, 0);

    const char* mimeType = 0;

    switch(QueryPictureFormat(data, dataSize))
    {
        case PICTURE_FORMAT::JPEG_PICTURE:
        {
            mimeType = "image/jpeg";
            break;
        }
        case PICTURE_FORMAT::PNG_PICTURE:
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

uint32_t QueryTargetDuration(const UnicodeString& target)
{
    PRECONDITION_RETURN(target.empty() == false, static_cast<uint32_t>(-1));

    uint32_t duration = 0;

    taglib::FileRef mp3(target.c_str());
    if((mp3.isNull() == false) && (mp3.audioProperties() != 0))
    {
        taglib::AudioProperties* properties = mp3.audioProperties();
        if(properties != 0)
        {
            duration = properties->length() * 1000;
        }
    }

    return duration;
}

void RemoveFrames(const UnicodeString& target, const UnicodeString& frameId)
{
    PRECONDITION(target.empty() == false);
    PRECONDITION(frameId.empty() == false);

    taglib_mp3::File mp3(target.c_str());
    if(mp3.isOpen() == true)
    {
        taglib_id3v2::Tag* id3v2 = mp3.ID3v2Tag();
        if(id3v2 != 0)
        {
            std::vector<taglib_id3v2::Frame*> foundFrames;

            taglib_id3v2::FrameList frames = id3v2->frameList(frameId.c_str());
            for(unsigned int i = 0; i < frames.size(); i++)
            {
                taglib_id3v2::Frame* frame = frames[i];
                if(frame != 0)
                {
                    foundFrames.push_back(frame);
                }
            }

            if(foundFrames.empty() == false)
            {
                for(size_t j = 0; j < foundFrames.size(); j++)
                {
                    id3v2->removeFrame(foundFrames[j]);
                }

                //            FIXME
                //            MP3_Commit(mp3);
            }
        }
    }
}

bool RemoveFrames(Context* context, const UnicodeString& id)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.empty() == false, false);

    bool success = false;

    std::vector<taglib_id3v2::Frame*> selectedFrames;

    taglib_id3v2::FrameList frames = context->Tags()->frameList(id.c_str());
    for(unsigned int i = 0; i < frames.size(); i++)
    {
        taglib_id3v2::Frame* frame = frames[i];
        if(frame != 0)
        {
            selectedFrames.push_back(frame);
        }
    }

    if(selectedFrames.empty() == false)
    {
        for(size_t j = 0; j < selectedFrames.size(); j++)
        {
            context->Tags()->removeFrame(selectedFrames[j]);
        }

        success = true;
    }

    return success;
}

bool InsertUTF8TextFrame(Context* context, const UnicodeString& id, const UnicodeString& text)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.empty() == false, false);

    bool success = false;

    RemoveFrames(context, id.c_str());

    if(text.empty() == false)
    {
        const char*                            frameIdString = id.c_str();
        taglib::ByteVector                     frameId       = taglib::ByteVector::fromCString(frameIdString);
        taglib_id3v2::TextIdentificationFrame* textFrame     = new taglib_id3v2::TextIdentificationFrame(frameId);
        if(textFrame != 0)
        {
            const char*        rawStringData = reinterpret_cast<const char*>(text.data());
            unsigned int       rawStringSize = static_cast<unsigned int>(text.size() * sizeof(char));
            taglib::ByteVector stringData(rawStringData, rawStringSize);
            textFrame->setTextEncoding(taglib::String::Type::UTF8);
            textFrame->setText(taglib::String(stringData, taglib::String::Type::UTF8));

            context->Tags()->addFrame(textFrame);
            success = true;
        }
    }
    else
    {
        success = true;
    }

    return success;
}

bool InsertUTF16TextFrame(Context* context, const UnicodeString& id, const UnicodeString& text)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.empty() == false, false);

    bool success = false;

    RemoveFrames(context, id.c_str());

    if(text.empty() == false)
    {
        const char*                            frameIdString = id.c_str();
        taglib::ByteVector                     frameId       = taglib::ByteVector::fromCString(frameIdString);
        taglib_id3v2::TextIdentificationFrame* textFrame     = new taglib_id3v2::TextIdentificationFrame(frameId);
        if(textFrame != 0)
        {
            WideUnicodeString  convertedString = UnicodeStringToWideUnicodeString(text, WITH_UTF16_BOM_LE);
            const char*        rawStringData   = reinterpret_cast<const char*>(convertedString.data());
            unsigned int       rawStringSize   = static_cast<unsigned int>(convertedString.size() * sizeof(char16_t));
            taglib::ByteVector stringData(rawStringData, rawStringSize);
            textFrame->setTextEncoding(taglib::String::Type::UTF16);
            textFrame->setText(taglib::String(stringData, taglib::String::Type::UTF16));

            context->Tags()->addFrame(textFrame);
            success = true;
        }
    }
    else
    {
        success = true;
    }

    return success;
}

bool InsertTextFrame(Context* context, const UnicodeString& id, const UnicodeString& text, const CHAR_ENCODING encoding)
{
    return (encoding == UTF16) ? InsertUTF16TextFrame(context, id, text) : InsertUTF8TextFrame(context, id, text);
}

bool InsertCommentsFrame(Context* context, const UnicodeString& id, const UnicodeString& text)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.empty() == false, false);

    bool success = false;

    RemoveFrames(context, id.c_str());

    if(text.empty() == false)
    {
        taglib_id3v2::CommentsFrame* commentsFrame = new taglib_id3v2::CommentsFrame(taglib::String::Type::UTF16);
        if(commentsFrame != 0)
        {
            WideUnicodeString  convertedString = UnicodeStringToWideUnicodeString(text, WITH_UTF16_BOM_LE);
            taglib::ByteVector stream(
                (const char*)convertedString.data(), (unsigned int)(convertedString.size() * sizeof(char16_t)));
            commentsFrame->setLanguage(taglib::ByteVector::fromCString("eng"));
            commentsFrame->setTextEncoding(taglib::String::Type::UTF16);
            commentsFrame->setText(taglib::String(stream, taglib::String::Type::UTF16));

            context->Tags()->addFrame(commentsFrame);
            success = true;
        }
    }
    else
    {
        success = true;
    }

    return success;
}

bool InsertChapterFrame(
    Context* context, const UnicodeString& id, const UnicodeString& text, const uint32_t startTime,
    const uint32_t endTime)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(id.empty() == false, false);
    PRECONDITION_RETURN(text.empty() == false, false);
    PRECONDITION_RETURN(startTime != 0xffffffff, false);
    PRECONDITION_RETURN(endTime != 0xffffffff, false);

    bool success = false;

    const uint32_t              startOffset = 0xffffffff;
    const uint32_t              endOffset   = 0xffffffff;
    taglib::ByteVector          chapterId   = taglib::ByteVector::fromCString(id.c_str());
    taglib_id3v2::ChapterFrame* chapterFrame
        = new taglib_id3v2::ChapterFrame(chapterId, startTime, endTime, startOffset, endOffset);
    if(chapterFrame != 0)
    {
        const char*                            embeddedFrameIdString = "TIT2";
        taglib::ByteVector                     embeddedFrameId = taglib::ByteVector::fromCString(embeddedFrameIdString);
        taglib_id3v2::TextIdentificationFrame* embeddedFrame
            = new taglib_id3v2::TextIdentificationFrame(embeddedFrameId);
        if(embeddedFrame != 0)
        {
            WideUnicodeString  convertedString = UnicodeStringToWideUnicodeString(text, WITH_UTF16_BOM_LE);
            taglib::ByteVector rawStringData(
                (const char*)convertedString.c_str(), (unsigned int)(convertedString.size() * sizeof(char16_t)));
            embeddedFrame->setTextEncoding(taglib::String::Type::UTF16);
            embeddedFrame->setText(taglib::String(rawStringData, taglib::String::Type::UTF16));

            chapterFrame->addEmbeddedFrame(embeddedFrame);
            context->Tags()->addFrame(chapterFrame);

            success = true;
        }
    }

    return success;
}

bool InsertTableOfContentsFrame(Context* context, const UnicodeStringArray& tableOfContentsItems)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(tableOfContentsItems.empty() == false, false);

    bool success = false;

    RemoveFrames(context, "CTOC");

    taglib::ByteVector                  tableOfContentsId = taglib::ByteVector::fromCString("toc");
    taglib_id3v2::TableOfContentsFrame* tableOfContentsFrame
        = new taglib_id3v2::TableOfContentsFrame(tableOfContentsId);
    if(tableOfContentsFrame != 0)
    {
        for(size_t j = 0; j < tableOfContentsItems.size(); j++)
        {
            tableOfContentsFrame->addChildElement(taglib::ByteVector::fromCString(tableOfContentsItems[j].c_str()));
        }

        taglib_id3v2::TextIdentificationFrame* embeddedFrame
            = new taglib_id3v2::TextIdentificationFrame(taglib::ByteVector::fromCString("TIT2"));
        if(embeddedFrame != 0)
        {
            WideUnicodeString  convertedString = UnicodeStringToWideUnicodeString("toplevel toc", WITH_UTF16_BOM_LE);
            taglib::ByteVector stream(
                (const char*)convertedString.c_str(), (unsigned int)(convertedString.size() * sizeof(char16_t)));
            embeddedFrame->setTextEncoding(taglib::String::Type::UTF16);
            embeddedFrame->setText(taglib::String(stream, taglib::String::Type::UTF16));
            tableOfContentsFrame->addEmbeddedFrame(embeddedFrame);
        }

        context->Tags()->addFrame(tableOfContentsFrame);

        success = true;
    }

    return success;
}

bool InsertCoverPictureFrame(Context* context, const UnicodeString& image)
{
    PRECONDITION_RETURN(context != 0, false);
    PRECONDITION_RETURN(context->Tags() != 0, false);
    PRECONDITION_RETURN(image.empty() == false, false);

    bool success = false;

    RemoveFrames(context, "APIC");

    taglib_id3v2::AttachedPictureFrame* frame = new taglib_id3v2::AttachedPictureFrame();
    if(frame != 0)
    {
        BinaryStream* imageData = FileManager::ReadBinaryFile(image);
        if(imageData != 0)
        {
            uint8_t      imageHeader[10] = {0};
            const size_t imageHeaderSize = 10;
            if(imageData->Read(0, imageHeader, imageHeaderSize) == true)
            {
                const UnicodeString mimeType = QueryMIMEType(imageHeader, imageHeaderSize);
                if(mimeType.empty() == false)
                {
                    frame->setMimeType(mimeType);
                    taglib::ByteVector coverData((const char*)imageData->Data(), (unsigned int)imageData->DataSize());
                    frame->setPicture(coverData);

                    context->Tags()->addFrame(frame);

                    success = true;
                }
            }

            SafeRelease(imageData);
        }
    }

    return success;
}

}}} // namespace ultraschall::reaper::id3v2
