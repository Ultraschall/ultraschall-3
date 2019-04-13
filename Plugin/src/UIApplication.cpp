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
#include "Common.h"

#include "wxwidgets_include.h"

namespace ultraschall { namespace reaper {

class UIApplicationImpl : public wxApp
{
public:
    UIApplicationImpl();
    virtual ~UIApplicationImpl();

    void Initialize(void* hInstance, void* hwnd);
    void Uninitialize();

    wxWindow* GetMainWindow();

    virtual bool OnInit();

private:
    void*     hInstance_;
    wxWindow* mainWindow_;
};

IMPLEMENT_APP_NO_MAIN(UIApplicationImpl)

UIApplicationImpl::UIApplicationImpl() : wxApp(), hInstance_(nullptr), mainWindow_(nullptr) {}

UIApplicationImpl::~UIApplicationImpl()
{
    delete mainWindow_;
    mainWindow_ = nullptr;
    hInstance_  = nullptr;
}

void UIApplicationImpl::Initialize(void* hInstance, void* hwnd)
{
    hInstance_ = hInstance;

#ifdef _WIN32
    wxEntryStart((HINSTANCE)hInstance_);

    mainWindow_ = new wxWindow();
    mainWindow_->SetHWND((WXHWND)hwnd);
    mainWindow_->AdoptAttributesFromHWND();
    wxTopLevelWindows.Append(mainWindow_);
#else  /// #ifdef _WIN32
    wxInitialize();
#endif // #ifdef _WIN32
}

void UIApplicationImpl::Uninitialize()
{
#ifdef _WIN32
    wxTopLevelWindows.DeleteObject(mainWindow_);
    mainWindow_->SetHWND((WXHWND)0);
    delete mainWindow_;
    mainWindow_ = 0;

    wxEntryCleanup();
#else  // #ifdef _WIN32
    wxUninitialize();
#endif // #ifdef _WIN32

    hInstance_ = 0;
}

wxWindow* UIApplicationImpl::GetMainWindow()
{
    return mainWindow_;
}

bool UIApplicationImpl::OnInit()
{
    return true;
}

UIApplicationImpl* UIApplication::impl_ = new UIApplicationImpl();

void UIApplication::Initialize(void* hInstance, void* hwnd)
{
    PRECONDITION(impl_ != nullptr);
    impl_->Initialize(hInstance, hwnd);
}

void UIApplication::Uninitialize()
{
    PRECONDITION(impl_ != nullptr);
    impl_->Uninitialize();
}

void* UIApplication::GetMainWindow()
{
    PRECONDITION_RETURN(impl_ != nullptr, nullptr);
    return impl_->GetMainWindow();
}

}} // namespace ultraschall::reaper
