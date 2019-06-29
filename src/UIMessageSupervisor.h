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

#ifndef __ULTRASCHALL_REAPER_UI_MESSAGE_SUPERVISOR_H_INCL__
#define __ULTRASCHALL_REAPER_UI_MESSAGE_SUPERVISOR_H_INCL__

#include "Common.h"
#include "UIMessageClass.h"
#include "UIMessageQueue.h"

namespace ultraschall { namespace reaper {

class UIMessageSupervisor
{
public:
    UIMessageSupervisor();
    ~UIMessageSupervisor();

    inline void RegisterSuccess(const UnicodeString& str);
    inline void RegisterWarning(const UnicodeString& str);
    inline void RegisterError(const UnicodeString& str);
    inline void RegisterFatalError(const UnicodeString& str);

private:
    void RegisterMessage(const UIMessageClass severity, const UnicodeString& str);

    void DisplayMessages();

    UIMessageQueue messageQueue_;
};

inline void UIMessageSupervisor::RegisterSuccess(const UnicodeString& str)
{
    RegisterMessage(UIMessageClass::MESSAGE_SUCCESS, str);
}

inline void UIMessageSupervisor::RegisterWarning(const UnicodeString& str)
{
    RegisterMessage(UIMessageClass::MESSAGE_WARNING, str);
}

inline void UIMessageSupervisor::RegisterError(const UnicodeString& str)
{
    RegisterMessage(UIMessageClass::MESSAGE_ERROR, str);
}

inline void UIMessageSupervisor::RegisterFatalError(const UnicodeString& str)
{
    RegisterMessage(UIMessageClass::MESSAGE_FATAL_ERROR, str);
}

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_UI_MESSAGE_SUPERVISOR_H_INCL__
