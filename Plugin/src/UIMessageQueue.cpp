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

void UIMessageQueue::Add(const UIMessage& message)
{
    std::lock_guard<std::recursive_mutex> lock(itemsLock_);
    items_.push_back(message);
}

void UIMessageQueue::Add(const UIMessageClass severity, const UnicodeString& str)
{
    Add(UIMessage(severity, str));
    //Add(UIMessage(UIMessageClass::MESSAGE_FATAL_ERROR, str));
    //Add(UIMessage(UIMessageClass::MESSAGE_ERROR, str));
    //Add(UIMessage(UIMessageClass::MESSAGE_WARNING, str));
    //Add(UIMessage(UIMessageClass::MESSAGE_SUCCESS, str));
}

void UIMessageQueue::Clear()
{
    items_.clear();
}

const UIMessageArray& UIMessageQueue::Items() const
{
    return items_;
}

size_t UIMessageQueue::ItemCount() const
{
    return items_.size();
}

}} // namespace ultraschall::reaper
