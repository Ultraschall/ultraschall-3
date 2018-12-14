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

#ifndef __ULTRASCHALL_REAPER_MP4_ENCODING_SESSION_H_INCL__
#define __ULTRASCHALL_REAPER_MP4_ENCODING_SESSION_H_INCL__

#include <windows.h>
#include <mfapi.h>
#include <mfidl.h>

namespace ultraschall { namespace reaper {

class MP4EncodingSession : public IMFAsyncCallback
{
public:
  static HRESULT Create(MP4EncodingSession **ppSession);

  // IUnknown methods
  STDMETHODIMP QueryInterface(REFIID riid, void** ppv);
  STDMETHODIMP_(ULONG) AddRef();
  STDMETHODIMP_(ULONG) Release();

  // IMFAsyncCallback methods
  STDMETHODIMP GetParameters(DWORD* pFlags, DWORD* pQueue);
  STDMETHODIMP Invoke(IMFAsyncResult *pResult);

  // Other methods
  HRESULT StartEncodingSession(IMFTopology *pTopology);
  HRESULT GetEncodingPosition(MFTIME *pTime);
  HRESULT Wait(DWORD timeout);

private:
  MP4EncodingSession();
  virtual ~MP4EncodingSession();

  HRESULT Initialize();

  IMFMediaSession * pSession_;
  IMFPresentationClock *pClock_;
  HRESULT status_;
  HANDLE  waitHandle_;
  long    refCount_;
};

}}

#endif // #ifndef __ULTRASCHALL_REAPER_MP4_ENCODING_SESSION_H_INCL__
