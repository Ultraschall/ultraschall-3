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

#ifndef __ULTRASCHALL_REAPER_ID3V2_H_INCL__
#define __ULTRASCHALL_REAPER_ID3V2_H_INCL__

#include "Common.h"
#include "ID3V2Context.h"
#include "Marker.h"

namespace ultraschall { namespace reaper { namespace id3v2 {

Context* StartTransaction(const UnicodeString& targetName);
bool     CommitTransaction(Context*& context);
void     AbortTransaction(Context*& context);

uint32_t QueryTargetDuration(const UnicodeString& targetName);

void RemoveFrames(const UnicodeString& target, const UnicodeString& frameId);
bool RemoveFrames(Context* context, const UnicodeString& id);

bool InsertTextFrame(
    Context* context, const UnicodeString& id, const UnicodeString& text, const CHAR_ENCODING encoding);
bool InsertCommentsFrame(Context* context, const UnicodeString& id, const UnicodeString& text);
bool InsertChapterFrame(
    Context* context, const UnicodeString& id, const UnicodeString& text, const uint32_t startTime,
    const uint32_t endTime);
bool InsertTableOfContentsFrame(Context* context, const UnicodeStringArray& tableOfContentsItems);
bool InsertCoverPictureFrame(Context* context, const UnicodeString& image);

}}} // namespace ultraschall::reaper::id3v2

#endif // #ifndef __ULTRASCHALL_REAPER_ID3V2_H_INCL__
