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

#include "TagWriterFactory.h"
#include "ID3V2Writer.h"
#include "ISOBMFFWriter.h"
#include "StringUtilities.h"

namespace ultraschall { namespace reaper {

ITagWriter* TagWriterFactory::Create(const UnicodeString& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, 0);
    PRECONDITION_RETURN(targetName.length() > 4, 0);

    ITagWriter*       tagWriter  = nullptr;
    const TARGET_TYPE targetType = FindFileType(targetName);
    if(targetType == MP3_TARGET)
    {
        tagWriter = new id3v2::Writer();
    }
#ifdef ULTRASCHALL_ENABLE_MP4
    else if(targetType == MP4_TARGET)
    {
        tagWriter = new isobmff::Writer();
    }
#endif // #ifdef ULTRASCHALL_ENABLE_MP4
    else
    {
        tagWriter = nullptr;
    }

    return tagWriter;
}

UnicodeString TagWriterFactory::NormalizeTargetName(const UnicodeString& targetName)
{
    UnicodeString firstStage  = targetName;
    UnicodeString secondStage = UnicodeStringTrimRight(firstStage);
    return StringLowercase(secondStage);
}

TagWriterFactory::TARGET_TYPE TagWriterFactory::FindFileType(const UnicodeString& targetName)
{
    PRECONDITION_RETURN(targetName.empty() == false, INVALID_TARGET_TYPE);

    TARGET_TYPE         type             = INVALID_TARGET_TYPE;
    const UnicodeString cookedTargetName = NormalizeTargetName(targetName);
    const size_t        extensionOffset  = targetName.rfind(".");
    if(extensionOffset != UnicodeString::npos)
    {
        const UnicodeString fileExtension
            = targetName.substr(extensionOffset + 1, targetName.length() - extensionOffset);
        if(fileExtension.empty() == false)
        {
            if(fileExtension == "mp3")
            {
                type = MP3_TARGET;
            }
#ifdef ULTRASCHALL_ENABLE_MP4
            else if(fileExtension == "mp4")
            {
                type = MP4_TARGET;
            }
            else if(fileExtension == "m4a")
            {
                type = MP4_TARGET;
            }
#endif // #ifdef ULTRASCHALL_ENABLE_MP4
            else
            {
                type = INVALID_TARGET_TYPE;
            }
        }
    }
    return type;
}

}} // namespace ultraschall::reaper
