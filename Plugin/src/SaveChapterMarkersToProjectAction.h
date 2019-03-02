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

#ifndef __ULTRASCHALL_REAPER_SAVE_CHAPTER_MARKERS_TO_PROJECT_ACTION_H_INCL__
#define __ULTRASCHALL_REAPER_SAVE_CHAPTER_MARKERS_TO_PROJECT_ACTION_H_INCL__

#include "Common.h"
#include "ICustomAction.h"

namespace ultraschall { namespace reaper {

class SaveChapterMarkersToProjectAction : public ICustomAction
{
public:
    static const UnicodeChar* UniqueId()
    {
        return "ULTRASCHALL_SAVE_CHAPTERS_TO_PROJECT";
    }

    static const UnicodeChar* UniqueName()
    {
        return "ULTRASCHALL: Save chapter markers to project folder";
    }

    static ICustomAction* CreateCustomAction()
    {
        return new SaveChapterMarkersToProjectAction();
    }

    virtual ServiceStatus Execute() override;

private:
    SaveChapterMarkersToProjectAction() {}

    MarkerArray      chapters_;
    bool                     ConfigureAssets();
    void                     ResetAssets();
    UnicodeStringArray ValidateChapterMarkers();
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_SAVE_CHAPTER_MARKERS_TO_PROJECT_ACTION_H_INCL__
