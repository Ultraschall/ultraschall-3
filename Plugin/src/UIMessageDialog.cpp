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

#include "wx/wx.h"

namespace ultraschall { namespace reaper {

const UnicodeString UIMessageDialog::UI_MESSAGE_DIALOG_CAPTION("Ultraschall");

void UIMessageDialog::Show(int32_t style, const UnicodeString& message, const UnicodeString& details)
{
    PRECONDITION(message.empty() == false);
    wxMessageBox(U2H(message), U2H(UI_MESSAGE_DIALOG_CAPTION), style);
}

void UIMessageDialog::Show(const UnicodeString& message, const UnicodeString& description)
{
    PRECONDITION(message.empty() == false);

    UIMessageDialog messageDialog;
    messageDialog.Show(wxICON_INFORMATION, U2H(message), U2H(UI_MESSAGE_DIALOG_CAPTION));
}

void UIMessageDialog::ShowWarning(const UnicodeString& message, const UnicodeString& description)
{
    PRECONDITION(message.empty() == false);

    UIMessageDialog messageDialog;
    messageDialog.Show(wxICON_WARNING, U2H(message), U2H(UI_MESSAGE_DIALOG_CAPTION));
}

void UIMessageDialog::ShowError(const UnicodeString& message, const UnicodeString& description)
{
    PRECONDITION(message.empty() == false);

    UIMessageDialog messageDialog;
    messageDialog.Show(wxICON_ERROR, U2H(message), U2H(UI_MESSAGE_DIALOG_CAPTION));
}

}} // namespace ultraschall::reaper
