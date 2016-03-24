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

#include <ResourceManager.h>
#include "ReaperEntryPoints.h"
#include "MessageBox.h"

#ifndef WIN32
#import "NotificationWindow.h"
#endif // #ifndef WIN32

namespace ultraschall { namespace reaper {
   
void NotificationWindow::Show(const std::string& message, const bool isError)
{
#ifndef WIN32
   [NotificationPanel showWithMessage: [NSString stringWithUTF8String: message.c_str()]
                               asError: isError ? YES : NO];
#else
    MessageBox(reaper_api::GetMainHwnd(), message.c_str(), "Ultraschall REAPER Extension", (isError == true) ? MB_ICONERROR : MB_ICONINFORMATION);
#endif // #ifndef WIN32
}

void NotificationWindow::Show(const std::string& message, const std::string& information, const bool isError)
{
#ifndef WIN32
    [NotificationPanel showWithMessage : [NSString stringWithUTF8String : message.c_str()]
                                  info: [NSString stringWithUTF8String: information.c_str()]
                                  asError: isError ? YES : NO];
#else
    MessageBox(reaper_api::GetMainHwnd(), information.c_str(), message.c_str(), (isError == true) ? MB_ICONERROR : MB_ICONINFORMATION);
#endif // #ifndef WIN32
}
   
   
void NotificationWindow::Show(const framework::ResourceId id, const bool isError)
{
   framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
   std::string message = resourceManager.GetLocalizedString(id);
   Show(message, isError);
}

void NotificationWindow::ShowUpdateAvailable(const std::string& message, const std::string& info, const std::string& changelog)
{
#ifndef WIN32
  [NotificationPanel showUpdateMessage: [NSString stringWithUTF8String : message.c_str()]
                                  info: [NSString stringWithUTF8String: info.c_str()]
                             changeLog: [NSString stringWithUTF8String: changelog.c_str()]];
#else
  // TODO: Make a proper windows dialog
  MessageBox(reaper_api::GetMainHwnd(), info.c_str(), message.c_str(), MB_ICONINFORMATION);
#endif
}

}}

