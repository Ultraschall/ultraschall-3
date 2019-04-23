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

#ifndef __ULTRASCHALL_REAPER_MP4_WRITER_H_INCL__
#define __ULTRASCHALL_REAPER_MP4_WRITER_H_INCL__

#include "Common.h"
#include "ITagWriter.h"

namespace ultraschall { namespace reaper { namespace isobmff {

class Writer : public ITagWriter
{
public:
    virtual bool InsertProperties(const UnicodeString& targetName, const MediaProperties& standardProperties);

    virtual bool InsertCoverImage(const UnicodeString& targetName, const UnicodeString& coverImage);

    virtual bool InsertChapterMarkers(const UnicodeString& targetName, const MarkerArray& chapterMarkers);

    virtual bool ReplaceChapterMarkers(const UnicodeString& targetName, const MarkerArray& chapterMarkers);

protected:
    virtual ~Writer() {}
};

}}} // namespace ultraschall::reaper::isobmff

#endif // #ifndef __ULTRASCHALL_REAPER_MP3_WRITER_H_INCL__
