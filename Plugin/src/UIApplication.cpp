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

#include "UIApplication.h"
#include "ReaperEntryPoints.h"

namespace ultraschall { namespace reaper {

IMPLEMENT_APP_NO_MAIN(UIApplication)

REAPER_PLUGIN_HINSTANCE UIApplication::hInstance_ = 0;
wxWindow* UIApplication::mainWindow_ = 0;

void UIApplication::Initialize(REAPER_PLUGIN_HINSTANCE hInstance)
{
    hInstance_ = hInstance;
    wxEntryStart(hInstance_);

	mainWindow_ = new wxWindow();
	mainWindow_->SetHWND((WXHWND)reaper_api::GetMainHwnd());
    mainWindow_->AdoptAttributesFromHWND();
    wxTopLevelWindows.Append(mainWindow_);
}

void UIApplication::Uninitialize()
{
    wxTopLevelWindows.DeleteObject(mainWindow_);
    mainWindow_->SetHWND((WXHWND)0);
    delete mainWindow_;
    mainWindow_ = 0;

    wxEntryCleanup();
}

wxWindow* UIApplication::GetMainWindow()
{
    return mainWindow_;
}

bool UIApplication::OnInit()
{
    return true;
}

}} // namespace ultraschall::reaper
