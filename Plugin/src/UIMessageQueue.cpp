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

#include "UIMessageQueue.h"
#include "UIMessageDialog.h"

namespace ultraschall { namespace reaper {

UIMessageQueue::UIMessageQueue() {}

UIMessageQueue::~UIMessageQueue() {}

UIMessageQueue& UIMessageQueue::Instance()
{
    static UIMessageQueue self;
    return self;
}

void UIMessageQueue::Add(const UIMessage& message)
{
    std::lock_guard<std::recursive_mutex> lock(itemsLock_);
    items_.push_back(message);
}

void UIMessageQueue::Add(const UIMessageClass severity, const UnicodeString& str)
{
    Add(UIMessage(severity, str));
}

void UIMessageQueue::DisplayReport(const UIMessageClass severityThreshold)
{
    if(items_.empty() == false)
    {
        items_.clear();
    }
}

}} // namespace ultraschall::reaper
