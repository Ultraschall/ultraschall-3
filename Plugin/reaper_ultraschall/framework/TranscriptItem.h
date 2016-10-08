////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2014-2015 Ultraschall (http://ultraschall.fm)
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

#ifndef __ULTRASCHALL_REAPER_TRANSCRIPT_ITEM_H_INCL__
#define __ULTRASCHALL_REAPER_TRANSCRIPT_ITEM_H_INCL__

#include <string>

namespace ultraschall { namespace framework {
    
class TranscriptItem
{
public:
    TranscriptItem(const std::string& speaker, const double position, const std::string& script);
    
    inline const std::string& Speaker() const
    {
        return speaker_;
    }
    
    inline double Position() const
    {
        return position_;
    }

    inline const std::string& Script() const
    {
        return script_;
    }

protected:
    inline void SetSpeaker(const std::string& speaker)
    {
        speaker_ = speaker;
    }
    
    inline void SetPosition(const double position)
    {
        position_ = position;
    }
    
    inline void SetScript(const std::string& script)
    {
        script_ = script;
    }
    
private:
    std::string speaker_;
    double position_;
    std::string script_;
};

}}

#endif // #ifndef __ULTRASCHALL_REAPER_TRANSCRIPT_ITEM_H_INCL__

