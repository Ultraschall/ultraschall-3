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

#include "UIMessageDialog.h"
#include "Common.h"

#include "wx/wx.h"

namespace ultraschall { namespace reaper {

#ifdef ULTRASCHALL_BROADCASTER
static const bool forceDisplay = false;
#else  // #ifndef ULTRASCHALL_BROADCASTER
static const bool forceDisplay = true;
#endif // #ifndef ULTRASCHALL_BROADCASTER

const UnicodeString UIMessageDialog::UI_MESSAGE_DIALOG_CAPTION("Ultraschall");

UIMessageDialog::UIMessageDialog() {}

int UIMessageDialog::Display(const UIMessageArray& items, const UIMessageClass& severityThreshold)
{
    if(true == forceDisplay)
    {
        return ForceDisplay(items, severityThreshold);
    }

    return 0;
}

int UIMessageDialog::ForceDisplay(const UIMessageArray& items, const UIMessageClass& severityThreshold)
{
    PRECONDITION_RETURN(items.empty() == false, 0);

    return 0;
}

UIMessageClass UIMessageDialog::MaxSeverity(const UIMessageArray& items)
{
    PRECONDITION_RETURN(items.empty() == false, UIMessageClass::INVALID_MESSAGE_CLASS);

    UIMessageClass maxSeverity = UIMessageClass::MESSAGE_SUCCESS;
    for(size_t i = 0; i < items.size(); i++)
    {
        if(items[i].Severity() > maxSeverity)
        {
            maxSeverity = items[i].Severity();
        }
    }

    return maxSeverity;
}

}} // namespace ultraschall::reaper
