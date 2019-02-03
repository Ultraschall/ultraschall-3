////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

#ifndef __ULTRASCHALL_REAPER_MP3_INTERFACE_H_INCL__
#define __ULTRASCHALL_REAPER_MP3_INTERFACE_H_INCL__

#include "taglib_include.h"

#include "Common.h"
#include "Marker.h"

namespace ultraschall { namespace reaper {

struct MP3_EXPORT_CONTEXT;

MP3_EXPORT_CONTEXT* MP3_StartTransaction(const UnicodeString& targetName);
bool                MP3_CommitTransaction(MP3_EXPORT_CONTEXT*& context);
void                MP3_AbortTransaction(MP3_EXPORT_CONTEXT*& context);

uint32_t MP3_QueryTargetDuration(const UnicodeString& targetName);

void MP3_RemoveFrames(const UnicodeString& target, const UnicodeString& frameId);
bool MP3_RemoveFrames(MP3_EXPORT_CONTEXT* context, const UnicodeString& id);

bool MP3_InsertTextFrame(MP3_EXPORT_CONTEXT* context, const UnicodeString& id, const UnicodeString& text);
bool MP3_InsertCommentsFrame(MP3_EXPORT_CONTEXT* context, const UnicodeString& id, const UnicodeString& text);
bool MP3_InsertChapterFrame(MP3_EXPORT_CONTEXT* context, const UnicodeString& id, const UnicodeString& text, const uint32_t startTime, const uint32_t endTime);
bool MP3_InsertTableOfContentsFrame(MP3_EXPORT_CONTEXT* context, const UnicodeStringArray& tableOfContentsItems);
bool MP3_InsertPodcastFrame(MP3_EXPORT_CONTEXT* context);
bool MP3_InsertCoverPictureFrame(MP3_EXPORT_CONTEXT* context, const UnicodeString& image);

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_MP3_INTERFACE_H_INCL__
