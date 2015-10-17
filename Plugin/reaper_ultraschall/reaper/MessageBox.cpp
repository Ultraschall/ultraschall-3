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

#include "MessageBox.h"

#ifdef WIN32
#include <windows.h>
#else
#import <AppKit/AppKit.h>
#endif

namespace ultraschall { namespace reaper {
   
void MessageBox::Show(const std::string& message, const bool isError)
{
#ifdef WIN32
#else
   NSAlert* alert = [[NSAlert alloc] init];
   alert.messageText = [NSString stringWithUTF8String: message.c_str()];
   alert.alertStyle = isError ? NSCriticalAlertStyle : NSInformationalAlertStyle;
   [alert runModal];
#endif
}

void MessageBox::Show(const framework::ResourceId id, const bool isError)
{
#ifdef WIN32
#else
   
   framework::ResourceManager& resourceManager = framework::ResourceManager::Instance();
   std::string message = resourceManager.GetLocalizedString(id);
   Show(message, isError);
#endif
}
   
}}

