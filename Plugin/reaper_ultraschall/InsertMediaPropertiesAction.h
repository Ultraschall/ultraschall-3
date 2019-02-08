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

#ifndef __ULTRASCHALL_REAPER_INSERT_MEDIA_PROPERTIES_ACTION_H_INCL__
#define __ULTRASCHALL_REAPER_INSERT_MEDIA_PROPERTIES_ACTION_H_INCL__

#include "ICustomAction.h"
#include "MP3TagWriter.h"
#include "MP4TagWriter.h"

namespace ultraschall { namespace reaper {

class ITagWriter;

class InsertMediaPropertiesAction : public ICustomAction
{
public:
    static const UnicodeChar* UniqueId()
    {
        return "ULTRASCHALL_INSERT_MEDIA_PROPERTIES";
    }

    static const UnicodeChar* UniqueName()
    {
        return "ULTRASCHALL: Insert media properties into target...";
    }

    static ICustomAction* CreateCustomAction()
    {
        return new InsertMediaPropertiesAction();
    }

    virtual ServiceStatus Execute() override;

private:
    InsertMediaPropertiesAction() {}

    bool ConfigureAssets();
    void ResetAssets();

    UnicodeStringArray    targetNames_;
    UnicodeString         cover_;
    MarkerArray           chapters_;
    BasicMediaInformation id3v2_;

    static UnicodeStringArray FindTargetFiles(const Project& project);

    static UnicodeString FindCoverImage(const Project& project);

    static ITagWriter* CreateTagWriter(const UnicodeString& targetName);

    static UnicodeString NormalizeTargetName(const UnicodeString& targetName);

    typedef enum { MP3_TARGET, MP4_TARGET, INVALID_TARGET_TYPE, MAX_TARGET_TYPE = INVALID_TARGET_TYPE } TARGET_TYPE;

    static TARGET_TYPE EvaluateFileType(const UnicodeString& targetName);

    bool ValidateChapterMarkers(UnicodeStringArray& errorRecords);
};

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_INSERT_MEDIA_PROPERTIES_ACTION_H_INCL__
