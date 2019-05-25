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

#include "Common.h"

#include "UIMessageDialog.h"

#include "ReaperEntryPoints.h"

namespace ultraschall
{
namespace reaper
{

#ifdef ULTRASCHALL_BROADCASTER
static const bool forceDisplay = false;
#else  // #ifndef ULTRASCHALL_BROADCASTER
static const bool forceDisplay = true;
#endif // #ifndef ULTRASCHALL_BROADCASTER

class UIMessageDisplay
{
public:
    UIMessageDisplay();
    UIMessageDisplay(const UIMessageArray &items);
    ~UIMessageDisplay();

private:
    static const UnicodeString UI_MESSAGE_DIALOG_CAPTION;

    static UnicodeString StringFromMessageSeverity(const UIMessageClass severity);
    // static wxColour ColorFromMessageSeverity(const UIMessageClass severity);
};

const UnicodeString UIMessageDisplay::UI_MESSAGE_DIALOG_CAPTION("Ultraschall");

UIMessageDisplay::UIMessageDisplay() {}

UIMessageDisplay::UIMessageDisplay(const UIMessageArray &items)
{
    // static const wxColour background(43, 43, 43);
    // static const wxColour foreground(244, 247, 255);

    // SetBackgroundColour(background);
    // SetForegroundColour(background);

    // layout_ = new wxBoxSizer(wxVERTICAL);
    // closeButton_ = new wxButton(this, wxID_ANY, "Close", wxPoint(10, 435), wxSize(70, 25));
    // layout_->Add(closeButton_, 1);

    // itemList_ = new wxListView(this, wxID_ANY, wxPoint(10, 10), wxSize(775, 412), wxBORDER | wxLC_REPORT | wxLC_NO_HEADER);
    // itemList_->SetBackgroundColour(background);
    // itemList_->SetForegroundColour(foreground);
    // itemList_->InsertColumn(0, "#", wxLIST_FORMAT_RIGHT, 20);
    // itemList_->InsertColumn(1, "Severity", wxLIST_FORMAT_LEFT, 100);
    // itemList_->InsertColumn(2, "Message", wxLIST_FORMAT_LEFT, 200);
    // layout_->Add(itemList_, 2);

    // itemList_->Hide();

    // for (size_t i = 0; i < items.size(); i++)
    // {
    //     UnicodeStringStream os;
    //     os << (i + 1);
    //     itemList_->InsertItem(i, os.str(), 0);
    //     itemList_->SetItemBackgroundColour(i, ColorFromMessageSeverity(items[i].Severity()));
    //     itemList_->SetItemTextColour(i, wxColour(255, 255, 255));
    //     itemList_->SetItem(i, 1, StringFromMessageSeverity(items[i].Severity()));
    //     itemList_->SetItem(i, 2, items[i].Str());
    // }

    // itemList_->Show();

    // itemList_->SetColumnWidth(0, wxLIST_AUTOSIZE);
    // itemList_->SetColumnWidth(1, wxLIST_AUTOSIZE);
    // itemList_->SetColumnWidth(2, wxLIST_AUTOSIZE_USEHEADER);
}

UIMessageDisplay::~UIMessageDisplay()
{
}

UnicodeString UIMessageDisplay::StringFromMessageSeverity(const UIMessageClass severity)
{
    switch (severity)
    {
    case UIMessageClass::MESSAGE_SUCCESS:
        return "Success";
    case UIMessageClass::MESSAGE_WARNING:
        return "Warning";
    case UIMessageClass::MESSAGE_ERROR:
        return "Error";
    case UIMessageClass::MESSAGE_FATAL_ERROR:
        return "Fatal Error";
    default:
        return "<Unknown>";
    }
}

// wxColour UIMessageDisplay::ColorFromMessageSeverity(const UIMessageClass severity)
// {
//     switch (severity)
//     {
//     case UIMessageClass::MESSAGE_SUCCESS:
//         return wxColour(0, 128, 0);
//     case UIMessageClass::MESSAGE_WARNING:
//         return wxColour(255, 140, 0);
//     case UIMessageClass::MESSAGE_ERROR:
//         return wxColour(128, 0, 0);
//     case UIMessageClass::MESSAGE_FATAL_ERROR:
//         return wxColour(128, 0, 128);
//     default:
//         return wxColour(0, 255, 0);
//     }
// }

UIMessageDialog::UIMessageDialog() {}

int UIMessageDialog::Display(const UIMessageArray &items, const UIMessageClass &severityThreshold)
{
    if (true == forceDisplay)
    {
        return ForceDisplay(items, severityThreshold);
    }

    return 0;
}

int UIMessageDialog::ForceDisplay(const UIMessageArray &items, const UIMessageClass &severityThreshold)
{
    PRECONDITION_RETURN(items.empty() == false, 0);

    UIMessageDisplay messageDisplay(items);
    // messageDisplay.Center();
    // messageDisplay.ShowModal();

    return 0;
}

UIMessageClass UIMessageDialog::MaxSeverity(const UIMessageArray &items)
{
    PRECONDITION_RETURN(items.empty() == false, UIMessageClass::INVALID_MESSAGE_CLASS);

    UIMessageClass maxSeverity = UIMessageClass::MESSAGE_SUCCESS;
    for (size_t i = 0; i < items.size(); i++)
    {
        if (items[i].Severity() > maxSeverity)
        {
            maxSeverity = items[i].Severity();
        }
    }

    return maxSeverity;
}

} // namespace reaper
} // namespace ultraschall
