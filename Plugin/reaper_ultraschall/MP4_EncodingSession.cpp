////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

#include "Framework.h"
#include "MP4_EncodingSession.h"

#include <new>
#include <iostream>

#include <shlwapi.h>
#include <codecapi.h>

namespace ultraschall { namespace reaper {

template <class T> void SafeRelease(T **ppi)
{
  if(*ppi)
  {
    (*ppi)->Release();
    *ppi = 0;
  }
}

MP4EncodingSession::MP4EncodingSession() :
  refCount_(1), pSession_(0), pClock_(0), status_(S_OK), waitHandle_(0)
{
}

MP4EncodingSession::~MP4EncodingSession()
{
  if(pSession_ != 0)
  {
    pSession_->Shutdown();
  }

  SafeRelease(&pSession_);
  SafeRelease(&pClock_);
  CloseHandle(waitHandle_);
  waitHandle_ = 0;
}

HRESULT MP4EncodingSession::Create(MP4EncodingSession **ppSession)
{
  PRECONDITION_RETURN(ppSession != 0, E_INVALIDARG);

  *ppSession = NULL;

  MP4EncodingSession *pSession = new(std::nothrow)MP4EncodingSession();
  if(pSession != 0)
  {
    HRESULT hr = pSession->Initialize();
    if(SUCCEEDED(hr))
    {
      *ppSession = pSession;
    }
    else
    {
      SafeRelease(&pSession);
      return hr;
    }
  }
  else
  {
    return E_OUTOFMEMORY;
  }

  return S_OK;
}

STDMETHODIMP MP4EncodingSession::QueryInterface(REFIID riid, void** ppv)
{
  PRECONDITION_RETURN(ppv != 0, E_INVALIDARG);

  static const QITAB qit[] = { QITABENT(MP4EncodingSession, IMFAsyncCallback), {0}};
  return QISearch(this, qit, riid, ppv);
}

STDMETHODIMP_(ULONG) MP4EncodingSession::AddRef()
{
  return InterlockedIncrement(&refCount_);
}

STDMETHODIMP_(ULONG) MP4EncodingSession::Release()
{
  const long refCount = InterlockedDecrement(&refCount_);
  if(0 == refCount)
  {
    delete this;
  }

  return refCount;
}

HRESULT MP4EncodingSession::Initialize()
{
  HRESULT hr = MFCreateMediaSession(0, &pSession_);
  if(SUCCEEDED(hr))
  {
    IMFClock *pClock = 0;
    hr = pSession_->GetClock(&pClock);
    if(SUCCEEDED(hr))
    {
      hr = pClock->QueryInterface(IID_PPV_ARGS(&pClock_));
      if(SUCCEEDED(hr))
      {
        hr = pSession_->BeginGetEvent(this, NULL);
        if(SUCCEEDED(hr))
        {
          waitHandle_ = CreateEvent(0, FALSE, FALSE, 0);
          if(0 == waitHandle_)
          {
            hr = HRESULT_FROM_WIN32(GetLastError());
            SafeRelease(&pClock_);
            SafeRelease(&pSession_);
          }
        }
        else
        {
          SafeRelease(&pClock_);
          SafeRelease(&pSession_);
        }
      }
      else
      {
        SafeRelease(&pSession_);
      }

      SafeRelease(&pClock);
    }
    else
    {
      SafeRelease(&pSession_);
    }
  }

  return hr;
}

STDMETHODIMP MP4EncodingSession::GetParameters(DWORD*, DWORD*)
{
  // Implementation of this method is optional.
  return E_NOTIMPL;
}

// Implements IMFAsyncCallback::Invoke
STDMETHODIMP MP4EncodingSession::Invoke(IMFAsyncResult *pResult)
{
  PRECONDITION_RETURN(pSession_ != 0, E_INVALIDARG);
  PRECONDITION_RETURN(waitHandle_ != 0, E_INVALIDARG);
  PRECONDITION_RETURN(pResult != 0, E_INVALIDARG);

  IMFMediaEvent* pEvent = NULL;
  HRESULT hr = pSession_->EndGetEvent(pResult, &pEvent);
  if(FAILED(hr))
  {
    goto done;
  }

  MediaEventType mediaEventType = MEUnknown;
  hr = pEvent->GetType(&mediaEventType);
  if(FAILED(hr))
  {
    goto done;
  }

  HRESULT hrStatus = S_OK;
  hr = pEvent->GetStatus(&hrStatus);
  if(FAILED(hr))
  {
    goto done;
  }

  if(FAILED(hrStatus))
  {
    hr = hrStatus;
    goto done;
  }

  switch(mediaEventType)
  {
  case MESessionEnded:
    hr = pSession_->Close();
    if(FAILED(hr))
    {
      goto done;
    }
    break;

  case MESessionClosed:
    SetEvent(waitHandle_);
    break;
  }

  if(mediaEventType != MESessionClosed)
  {
    hr = pSession_->BeginGetEvent(this, NULL);
  }

done:
  if(FAILED(hr))
  {
    status_ = hr;
    pSession_->Close();
  }

  SafeRelease(&pEvent);
  return hr;
}

HRESULT MP4EncodingSession::StartEncodingSession(IMFTopology *pTopology)
{
  PRECONDITION_RETURN(pSession_ != 0, E_INVALIDARG);
  PRECONDITION_RETURN(pTopology != 0, E_INVALIDARG);

  HRESULT hr = pSession_->SetTopology(0, pTopology);
  if(SUCCEEDED(hr))
  {
    PROPVARIANT varStart = {0};
    PropVariantClear(&varStart);
    hr = pSession_->Start(&GUID_NULL, &varStart);
  }

  return hr;
}

HRESULT MP4EncodingSession::GetEncodingPosition(MFTIME *pTime)
{
  PRECONDITION_RETURN(pClock_ != 0, E_UNEXPECTED);
  PRECONDITION_RETURN(pTime != 0, E_INVALIDARG);

  return pClock_->GetTime(pTime);
}

HRESULT MP4EncodingSession::Wait(DWORD timeout)
{
  PRECONDITION_RETURN(waitHandle_ != 0, E_UNEXPECTED);

  HRESULT hr = S_OK;

  DWORD dwTimeoutStatus = WaitForSingleObject(waitHandle_, timeout);
  if(dwTimeoutStatus != WAIT_OBJECT_0)
  {
    hr = E_PENDING;
  }
  else
  {
    hr = status_;
  }

  return hr;
}

}}
