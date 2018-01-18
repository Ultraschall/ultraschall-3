////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2017 Ultraschall ultraschall.fm
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

#ifndef __ULTRASCHALL_REAPER_MP3_TAG_WRITER_H_INCL__
#define __ULTRASCHALL_REAPER_MP3_TAG_WRITER_H_INCL__

#include "Framework.h"
#include "ITagWriter.h"

namespace ultraschall { namespace reaper {

class MP3TagWriter : public ITagWriter
{
public:
   virtual bool InsertStandardProperties(const std::string& targetName, const BasicMediaInformation& standardProperties);

   virtual bool InsertCoverImage(const std::string& targetName, const std::string& coverImage);

   virtual bool InsertChapterMarkers(const std::string& targetName, const std::vector<Marker>& chapterMarkers, const bool replace);

protected:
   virtual ~MP3TagWriter()
   {
   }
};

}}

#endif // #ifndef __ULTRASCHALL_REAPER_MP3_TAG_WRITER_H_INCL__


