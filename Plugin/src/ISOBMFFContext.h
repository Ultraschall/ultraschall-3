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

#ifndef __ULTRASCHALL_REAPER_ISOBMFF_CONTEXT_H_INCL__
#define __ULTRASCHALL_REAPER_ISOBMFF_CONTEXT_H_INCL__

#define MP4V2_EXPORTS 0
#define MP4V2_NO_STDINT_DEFS 1
#include <mp4v2/mp4v2.h>

namespace ultraschall { namespace reaper { namespace isobmff {

class Context
{
public:
    Context(const UnicodeString& targetName);
    ~Context();

    inline bool IsValid() const;

    inline const MP4FileHandle Target() const;
    inline const MP4Tags*      Tags() const;

private:
    MP4FileHandle  target_ = nullptr;
    const MP4Tags* tags_   = nullptr;

    void Reset();

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
};

bool Context::IsValid() const
{
    return (target_ != nullptr) && (tags_ != nullptr);
}

inline const MP4FileHandle Context::Target() const
{
    return target_;
}

inline const MP4Tags* Context::Tags() const
{
    return tags_;
}

}}} // namespace ultraschall::reaper::isobmff

#endif // #ifndef __ULTRASCHALL_REAPER_ISOBMFF_CONTEXT_H_INCL__
