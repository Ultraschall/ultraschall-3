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

#include <iomanip>
#include <sstream>

#include "StringUtilities.h"

#include "MP3TagWriter.h"
#include "MP3_Interface.h"

namespace ultraschall { namespace reaper {

bool MP3TagWriter::InsertProperties(const UnicodeString& targetName, const BasicMediaInformation& standardProperties)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);

    const UnicodeString durationString = UnicodeStringFromInt(MP3_QueryTargetDuration(targetName));
    const UnicodeString encoderString  = "Ultraschall v3.2";

    bool                success = true;
    MP3_EXPORT_CONTEXT* context = MP3_StartTransaction(targetName);
    if(context != 0)
    {
        // ATP Frame Order:
        // TALB:    UTF-16 -> Title
        // TPE1:    UTF-16 -> Title
        // TIT2:    UTF-16 -> Track
        // COMM:    UTF-16 -> Comments
        // USLT:    UTF-16 -> Comments
        // TLEN:    ASCII  -> <dynamic>
        // TYER:    ASCII  -> Date
        // TENC:    ASCII  -> "Ultraschall v3.2"

        static const size_t MAX_SIMPLE_FRAME_MAPPINGS  = 6;
        static const size_t MAX_COMPLEX_FRAME_MAPPINGS = 2;
        struct MAP_ULTRASCHALL_PROPERTIES_TO_REQUIRED_APPLE_TAGS
        {
            const UnicodeChar*   FrameId;
            const CHAR_ENCODING  Encoding;
            const UnicodeString& DataReference;
        } simpleFrameMappings[MAX_SIMPLE_FRAME_MAPPINGS]
            = {{"TALB", UTF16, standardProperties.Title()}, {"TPE1", UTF16, standardProperties.Title()},
               {"TIT2", UTF16, standardProperties.Track()}, {"TLEN", UTF8, durationString},
               {"TYER", UTF8, standardProperties.Date()},   {"TENC", UTF8, encoderString}},
            complexFrameMapping[MAX_COMPLEX_FRAME_MAPPINGS]
            = {{"COMM", UTF16, standardProperties.Comments()}, {"USLT", UTF16, standardProperties.Comments()}};
        for(size_t i = 0; (i < MAX_SIMPLE_FRAME_MAPPINGS) && (true == success); i++)
        {
            success
                = MP3_InsertTextFrame(context, simpleFrameMappings[i].FrameId, simpleFrameMappings[i].DataReference, simpleFrameMappings[i].Encoding);
        }
        if(true == success)
        {
            for(size_t i = 0; (i < MAX_COMPLEX_FRAME_MAPPINGS) && (true == success); i++)
            {
                success = MP3_InsertCommentsFrame(
                    context, complexFrameMapping[i].FrameId, complexFrameMapping[i].DataReference);
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

bool MP3TagWriter::InsertCoverImage(const UnicodeString& targetName, const UnicodeString& coverImage)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);
    PRECONDITION_RETURN(coverImage.empty() == false, false);

    bool success = false;

    MP3_EXPORT_CONTEXT* context = MP3_StartTransaction(targetName);
    if(context != 0)
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

bool MP3TagWriter::InsertChapterMarkers(const UnicodeString& targetName, const MarkerArray& chapterMarkers)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);
    PRECONDITION_RETURN(chapterMarkers.empty() == false, false);

    const uint32_t targetDuration = MP3_QueryTargetDuration(targetName);
    PRECONDITION_RETURN(targetDuration > 0, false);

    bool success = false;

    MP3_EXPORT_CONTEXT* context = MP3_StartTransaction(targetName);
    if(context != 0)
    {
        UnicodeStringArray tableOfContentsItems;
        success = true;
        for(size_t i = 0; (i < chapterMarkers.size()) && (true == success); i++)
        {
            std::stringstream chapterId;
            chapterId << "chp" << i;
            UnicodeString tableOfContensItem = chapterId.str();
            tableOfContentsItems.push_back(tableOfContensItem);

            const uint32_t startTime = static_cast<uint32_t>(chapterMarkers[i].Position() * 1000);
            const uint32_t endTime   = (i < (chapterMarkers.size() - 1)) ?
                                         static_cast<uint32_t>(chapterMarkers[i + 1].Position() * 1000) :
                                         targetDuration;
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

bool MP3TagWriter::ReplaceChapterMarkers(const UnicodeString& targetName, const MarkerArray& chapterMarkers)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);
    PRECONDITION_RETURN(chapterMarkers.empty() == false, false);

    const uint32_t targetDuration = MP3_QueryTargetDuration(targetName);
    PRECONDITION_RETURN(targetDuration > 0, false);

    bool success = false;

    MP3_EXPORT_CONTEXT* context = MP3_StartTransaction(targetName);
    if(context != 0)
    {
        MP3_RemoveFrames(context, "CHAP");

        UnicodeStringArray tableOfContentsItems;
        success = true;
        for(size_t i = 0; (i < chapterMarkers.size()) && (true == success); i++)
        {
            std::stringstream chapterId;
            chapterId << "chp" << i;
            UnicodeString tableOfContensItem = chapterId.str();
            tableOfContentsItems.push_back(tableOfContensItem);

            const uint32_t startTime = static_cast<uint32_t>(chapterMarkers[i].Position() * 1000);
            const uint32_t endTime   = (i < (chapterMarkers.size() - 1)) ?
                                         static_cast<uint32_t>(chapterMarkers[i + 1].Position() * 1000) :
                                         targetDuration;
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

}} // namespace ultraschall::reaper
