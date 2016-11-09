////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2016 Ultraschall (http://ultraschall.fm)
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

#ifndef __ULTRASCHALL_REAPER_UPDATE_CHECK_ACTION_H_INCL__
#define __ULTRASCHALL_REAPER_UPDATE_CHECK_ACTION_H_INCL__

#include <string>

#include <ResourceId.h>

#include "ICustomAction.h"

namespace ultraschall {
namespace reaper {

class UpdateCheckAction : public ICustomAction
{
public:
   static const char* UniqueId();

   static ServiceStatus CreateCustomAction(ICustomAction*& pCustomAction);

   virtual const char* LocalizedName() const override;

   virtual ServiceStatus Execute() override;

protected:
   virtual ~UpdateCheckAction();

private:
   static const size_t MAX_VERSION_LENGTH = 4;
   static const char* UPDATE_FILE_URL;

   UpdateCheckAction();

   static std::string QueryUpdatedVersion();

   static std::vector<int> NormalizeVersionString(const std::string& version);

   static int CompareVersions(const std::string& lhs, const std::string& rhs);

   static std::string DownloadVersionFile();
   static void DownloadVersionFileCallback();

   static std::string ParseVersionFile(const std::string& versionFile);

   framework::ResourceId actionNameId_;
};

}
}

#endif // #ifndef __ULTRASCHALL_REAPER_UPDATE_CHECK_ACTION_H_INCL__
