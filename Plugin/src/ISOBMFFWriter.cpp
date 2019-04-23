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

#include "ISOBMFFWriter.h"
#include "ISOBMFF.h"

namespace ultraschall { namespace reaper { namespace isobmff {

bool Writer::InsertProperties(const UnicodeString& targetName, const MediaProperties& properties)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);

    bool result = false;

    isobmff::Context* context = isobmff::StartTransaction(targetName);
    if(context != nullptr)
    {
        result = isobmff::InsertName(context, properties.Title());
        result |= isobmff::InsertArtist(context, properties.Author());
        result |= isobmff::InsertAlbum(context, properties.Track());
        result |= isobmff::InsertReleaseDate(context, properties.Date());
        result |= isobmff::InsertGenre(context, properties.Content());
        result |= isobmff::InsertComments(context, properties.Comments());
        if(true == result)
        {
            result = isobmff::CommitTransaction(context);
        }
        else
        {
            isobmff::AbortTransaction(context);
        }
    }

    return result;
}

bool Writer::InsertCoverImage(const UnicodeString& targetName, const UnicodeString& file)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);
    PRECONDITION_RETURN(file.empty() == false, false);

    bool result = false;

    isobmff::Context* context = isobmff::StartTransaction(targetName);
    if(context != nullptr)
    {
        result = isobmff::InsertCoverImage(context, file);
    }

    return result;
}

bool Writer::InsertChapterMarkers(const UnicodeString& targetName, const MarkerArray& chapterMarkers)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);
    PRECONDITION_RETURN(chapterMarkers.empty() == false, false);

    bool result = false;

    isobmff::Context* context = isobmff::StartTransaction(targetName);
    if(context != nullptr)
    {
        result = isobmff::InsertChapterMarkers(context, chapterMarkers);
    }

    return result;
}

bool Writer::ReplaceChapterMarkers(const UnicodeString& targetName, const MarkerArray& chapterMarkers)
{
    PRECONDITION_RETURN(targetName.empty() == false, false);
    PRECONDITION_RETURN(chapterMarkers.empty() == false, false);

    bool result = false;

    isobmff::Context* context = isobmff::StartTransaction(targetName);
    if(context != nullptr)
    {
        result = isobmff::InsertChapterMarkers(context, chapterMarkers);
    }

    return result;
}

}}} // namespace ultraschall::reaper::isobmff

