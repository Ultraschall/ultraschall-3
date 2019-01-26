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

#ifndef __ULTRASCHALL_REAPER_BASIC_MEDIA_INFORMATION_H_INCL__
#define __ULTRASCHALL_REAPER_BASIC_MEDIA_INFORMATION_H_INCL__

#include "Common.h"

namespace ultraschall { namespace reaper {

class BasicMediaInformation
{
public:
    BasicMediaInformation();
    ~BasicMediaInformation();

    static BasicMediaInformation ParseString(const std::string& str);

    bool Validate() const;
    void Reset();

    inline const std::string& Title() const
    {
        return title_;
    }

    inline const std::string& Author() const
    {
        return author_;
    }

    inline const std::string& Track() const
    {
        return track_;
    }

    inline const std::string& Date() const
    {
        return date_;
    }

    inline const std::string& Content() const
    {
        return content_;
    }

    inline const std::string& Comments() const
    {
        return comments_;
    }

private:
    std::string title_;    // TIT2
    std::string author_;   // TPE1
    std::string track_;    // TALB
    std::string date_;     // TDRC
    std::string content_;  // TCON
    std::string comments_; // COMM
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_BASIC_MEDIA_INFORMATION_H_INCL__
