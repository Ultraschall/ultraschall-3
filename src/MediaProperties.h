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

#ifndef __ULTRASCHALL_REAPER_BASIC_MEDIA_INFORMATION_H_INCL__
#define __ULTRASCHALL_REAPER_BASIC_MEDIA_INFORMATION_H_INCL__

#include "Common.h"

namespace ultraschall { namespace reaper {

class MediaProperties
{
public:
    MediaProperties();
    ~MediaProperties();

    static MediaProperties ParseProjectNotes();

    bool Validate() const;
    void Clear();

    inline const UnicodeString& Title() const
    {
        return title_;
    }

    inline const UnicodeString& Author() const
    {
        return author_;
    }

    inline const UnicodeString& Track() const
    {
        return track_;
    }

    inline const UnicodeString& Date() const
    {
        return date_;
    }

    inline const UnicodeString& Content() const
    {
        return content_;
    }

    inline const UnicodeString& Comments() const
    {
        return comments_;
    }

private:
    UnicodeString title_;    // TIT2
    UnicodeString author_;   // TPE1
    UnicodeString track_;    // TALB
    UnicodeString date_;     // TDRC
    UnicodeString content_;  // TCON
    UnicodeString comments_; // COMM
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_BASIC_MEDIA_INFORMATION_H_INCL__
