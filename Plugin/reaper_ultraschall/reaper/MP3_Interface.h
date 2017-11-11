////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 Ultraschall (http://ultraschall.fm)
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

#include <vector>
#include "taglib_include.h"
#include "Marker.h"

namespace ultraschall {
namespace reaper {

bool MP3_Commit(TagLib::MPEG::File& file);

uint32_t MP3_QueryTargetDuration(const std::string& target);

void MP3_RemoveFrames(const std::string& target, const std::string& frameId);
void MP3_RemoveMultipleFrames(TagLib::ID3v2::Tag* parent, const std::string& id);

bool MP3_InsertSingleTextFrame(TagLib::ID3v2::Tag* parent, const std::string& id, const std::string& text);
bool MP3_InsertSingleCommentsFrame(TagLib::ID3v2::Tag* parent, const std::string& id, const std::string& text);
bool MP3_InsertSingleChapterFrame(TagLib::ID3v2::Tag* parent, const std::string& id, const std::string& text, const uint32_t startTime, const uint32_t endTime);
bool MP3_InsertSingleTableOfContentsFrame(TagLib::ID3v2::Tag* parent, const std::vector<std::string>& tableOfContentsItems);
bool MP3_InsertSinglePodcastFrame(TagLib::ID3v2::Tag* parent);
bool MP3_InsertSingleCoverPictureFrame(TagLib::ID3v2::Tag* parent, const std::string& image);

}}

#endif // #ifndef __ULTRASCHALL_REAPER_MP3_INTERFACE_H_INCL__
