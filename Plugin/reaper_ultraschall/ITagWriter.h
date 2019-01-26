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

#ifndef __ULTRASCHALL_REAPER_ITAG_WRITER_H_INCL__
#define __ULTRASCHALL_REAPER_ITAG_WRITER_H_INCL__

#include "Common.h"
#include "BasicMediaInformation.h"
#include "SharedObject.h"
#include "Marker.h"
#include "ServiceStatus.h"

namespace ultraschall { namespace reaper {

class ITagWriter : public SharedObject
{
public:
    virtual bool InsertStandardProperties(const std::string& targetName, const BasicMediaInformation& standardProperties) = 0;

    virtual bool InsertCoverImage(const std::string& targetName, const std::string& coverImage) = 0;

    virtual bool InsertChapterMarkers(const std::string& targetName, const std::vector<Marker>& chapterMarkers, const bool replace) = 0;

protected:
    virtual ~ITagWriter() {}
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_ITAG_WRITER_H_INCL__
