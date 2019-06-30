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

#ifndef __ULTRASCHALL_REAPER_TAG_LIB_H_INCL__
#define __ULTRASCHALL_REAPER_TAG_LIB_H_INCL__

#ifdef __APPLE__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#endif // #ifdef __APPLE__

#define TAGLIB_STATIC
#include <tstringlist.h>
#include <fileref.h>
#include <tag.h>
#include <tbytevectorlist.h>
#include <tpropertymap.h>
#include <mpegfile.h>
#include <id3v2tag.h>
#include <chapterframe.h>
#include <textidentificationframe.h>
#include <attachedpictureframe.h>
#include <commentsframe.h>
#include <tableofcontentsframe.h>
#include <podcastframe.h>

namespace taglib = TagLib;
namespace taglib_id3v2 = TagLib::ID3v2;
namespace taglib_mp3 = TagLib::MPEG;

#ifdef __APPLE__
#pragma clang diagnostic pop
#endif // #ifdef __APPLE__

#endif // #ifndef __ULTRASCHALL_REAPER_TAG_LIB_H_INCL__
