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

#ifndef __ULTRASCHALL_REAPER_ID3V2_CONTEXT_H_INCL__
#define __ULTRASCHALL_REAPER_ID3V2_CONTEXT_H_INCL__

#include "Common.h"

#include "taglib_include.h"

namespace ultraschall { namespace reaper { namespace id3v2 {

class Context
{
public:
    Context(const UnicodeString& targetName);
    ~Context();

    inline bool IsValid() const;

    inline taglib_mp3::File*  Target();
    inline taglib_id3v2::Tag* Tags();

private:
    taglib_mp3::File*  target_ = nullptr;
    taglib_id3v2::Tag* tags_   = nullptr;

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
};

inline bool Context::IsValid() const
{
    return (target_ != nullptr) && (tags_ != nullptr);
}

inline taglib_mp3::File* Context::Target()
{
    return target_;
}

inline taglib_id3v2::Tag* Context::Tags()
{
    return tags_;
}

}}} // namespace ultraschall::reaper::id3v2

#endif // #ifndef __ULTRASCHALL_REAPER_ID3V2_CONTEXT_H_INCL__
