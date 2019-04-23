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

#include "Common.h"

#include "ISOBMFFContext.h"

namespace ultraschall { namespace reaper { namespace isobmff {

Context::Context(const UnicodeString& targetName)
{
    bool initialized = false;

    target_ = MP4Modify(targetName.c_str());
    if(target_ != nullptr)
    {
        tags_ = MP4TagsAlloc();
        if(tags_ != nullptr)
        {
            initialized = MP4TagsFetch(tags_, target_);
        }
    }

    if(initialized != true)
    {
        Reset();
    }
}

Context::~Context()
{
    Reset();
}

void Context::Reset()
{
    if(tags_ != nullptr)
    {
        MP4TagsFree(tags_);
        tags_ = nullptr;
    }

    if(target_ != nullptr)
    {
        MP4Close(target_);
        target_ = nullptr;
    }
}

}}} // namespace ultraschall::reaper::isobmff

