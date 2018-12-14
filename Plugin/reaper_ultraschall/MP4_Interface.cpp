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
#include "MP4_Interface.h"

#include <new>
#include <iostream>

#include <shlwapi.h>
#include <codecapi.h>

namespace ultraschall { namespace reaper {

template <class T> void SafeRelease(T **ppT)
{
  if(*ppT)
  {
    (*ppT)->Release();
    *ppT = NULL;
  }
}

int video_profile = 0;
int audio_profile = 0;

struct MP4_VIDEO_PROFILE_INFORMATION
{
  UINT32  profile;
  MFRatio fps;
  MFRatio frame_size;
  UINT32  bitrate;
};

MP4_VIDEO_PROFILE_INFORMATION h264_profiles[] =
{
  {eAVEncH264VProfile_Base, {15, 1}, {176, 144}, 128000},
{eAVEncH264VProfile_Base, {15, 1}, {352, 288}, 384000},
{eAVEncH264VProfile_Base, {30, 1}, {352, 288}, 384000},
{eAVEncH264VProfile_Base, {29970, 1000}, {320, 240}, 528560},
{eAVEncH264VProfile_Base, {15, 1}, {720, 576}, 4000000},
{eAVEncH264VProfile_Main, {25, 1}, {720, 576}, 10000000},
{eAVEncH264VProfile_Main, {30, 1}, {352, 288}, 10000000},
};

struct MP4_AUDIO_PROFILE_INFORMATION
{
  UINT32  samplesPerSec;
  UINT32  numChannels;
  UINT32  bitsPerSample;
  UINT32  bytesPerSec;
  UINT32  aacProfile;
};

MP4_AUDIO_PROFILE_INFORMATION aac_profiles[] =
{
  {96000, 2, 16, 24000, 0x29},
{48000, 2, 16, 24000, 0x29},
{44100, 2, 16, 16000, 0x29},
{44100, 2, 16, 12000, 0x29},
};

HRESULT MP4CreateMediaSource(PCWSTR url, IMFMediaSource **ppSource)
{
  PRECONDITION_RETURN(url != 0, E_INVALIDARG);
  PRECONDITION_RETURN(ppSource != 0, E_INVALIDARG);

  IMFSourceResolver* pResolver = 0;
  HRESULT hr = MFCreateSourceResolver(&pResolver);
  if(SUCCEEDED(hr))
  {
    MF_OBJECT_TYPE ObjectType = MF_OBJECT_INVALID;
    IUnknown* pSource = 0;
    hr = pResolver->CreateObjectFromURL(url, MF_RESOLUTION_MEDIASOURCE, 0, &ObjectType, &pSource);
    if(SUCCEEDED(hr))
    {
      hr = pSource->QueryInterface(IID_PPV_ARGS(ppSource));
      SafeRelease(&pSource);
    }

    SafeRelease(&pResolver);
  }

  return hr;
}

HRESULT MP4GetSourceDuration(IMFMediaSource *pSource, MFTIME *pDuration)
{
  PRECONDITION_RETURN(pSource != 0, E_INVALIDARG);
  PRECONDITION_RETURN(pDuration != 0, E_INVALIDARG);

  *pDuration = -1;

  IMFPresentationDescriptor *pPresentationDescriptor = 0;
  HRESULT hr = pSource->CreatePresentationDescriptor(&pPresentationDescriptor);
  if(SUCCEEDED(hr))
  {
    hr = pPresentationDescriptor->GetUINT64(MF_PD_DURATION, (UINT64*)pDuration);
    SafeRelease(&pPresentationDescriptor);
  }

  return hr;
}

HRESULT MP4CreateVideoProfile(DWORD index, IMFAttributes** ppAttributes)
{
  PRECONDITION_RETURN(index < (ARRAYSIZE(h264_profiles)), E_INVALIDARG);
  PRECONDITION_RETURN(ppAttributes != 0, E_INVALIDARG);

  IMFAttributes *pAttributes = NULL;

  const MP4_VIDEO_PROFILE_INFORMATION& profile = h264_profiles[index];

  HRESULT hr = MFCreateAttributes(&pAttributes, 5);
  if(SUCCEEDED(hr))
  {
    hr = pAttributes->SetGUID(MF_MT_SUBTYPE, MFVideoFormat_H264);
  }

  if(SUCCEEDED(hr))
  {
    hr = pAttributes->SetUINT32(MF_MT_MPEG2_PROFILE, profile.profile);
  }

  if(SUCCEEDED(hr))
  {
    hr = MFSetAttributeSize(
      pAttributes, MF_MT_FRAME_SIZE,
      profile.frame_size.Numerator, profile.frame_size.Numerator);
  }

  if(SUCCEEDED(hr))
  {
    hr = MFSetAttributeRatio(
      pAttributes, MF_MT_FRAME_RATE,
      profile.fps.Numerator, profile.fps.Denominator);
  }

  if(SUCCEEDED(hr))
  {
    hr = pAttributes->SetUINT32(MF_MT_AVG_BITRATE, profile.bitrate);
  }

  if(SUCCEEDED(hr))
  {
    *ppAttributes = pAttributes;
    (*ppAttributes)->AddRef();
  }

  SafeRelease(&pAttributes);

  return hr;
}

HRESULT MP4CreateAudioProfile(DWORD index, IMFAttributes** ppAttributes)
{
  PRECONDITION_RETURN(index < (ARRAYSIZE(aac_profiles)), E_INVALIDARG);
  PRECONDITION_RETURN(ppAttributes != 0, E_INVALIDARG);

  const MP4_AUDIO_PROFILE_INFORMATION& profile = aac_profiles[index];

  IMFAttributes *pAttributes = NULL;

  HRESULT hr = MFCreateAttributes(&pAttributes, 7);
  if(SUCCEEDED(hr))
  {
    hr = pAttributes->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_AAC);
  }

  if(SUCCEEDED(hr))
  {
    hr = pAttributes->SetUINT32(
      MF_MT_AUDIO_BITS_PER_SAMPLE, profile.bitsPerSample);
  }

  if(SUCCEEDED(hr))
  {
    hr = pAttributes->SetUINT32(
      MF_MT_AUDIO_SAMPLES_PER_SECOND, profile.samplesPerSec);
  }

  if(SUCCEEDED(hr))
  {
    hr = pAttributes->SetUINT32(
      MF_MT_AUDIO_NUM_CHANNELS, profile.numChannels);
  }

  if(SUCCEEDED(hr))
  {
    hr = pAttributes->SetUINT32(
      MF_MT_AUDIO_AVG_BYTES_PER_SECOND, profile.bytesPerSec);
  }
  if(SUCCEEDED(hr))
  {
    hr = pAttributes->SetUINT32(MF_MT_AUDIO_BLOCK_ALIGNMENT, 1);
  }

  if(SUCCEEDED(hr))
  {
    hr = pAttributes->SetUINT32(
      MF_MT_AAC_AUDIO_PROFILE_LEVEL_INDICATION, profile.aacProfile);
  }

  if(SUCCEEDED(hr))
  {
    *ppAttributes = pAttributes;
    (*ppAttributes)->AddRef();
  }

  SafeRelease(&pAttributes);
  return hr;
}

HRESULT MP4CreateTranscodingProfile(IMFTranscodeProfile **ppProfile)
{
  PRECONDITION_RETURN(ppProfile != 0, E_INVALIDARG);

  IMFTranscodeProfile *pProfile = 0;
  IMFAttributes *pAudio = 0;
  IMFAttributes *pVideo = 0;
  IMFAttributes *pContainer = 0;

  HRESULT hr = MFCreateTranscodeProfile(&pProfile);
  if(FAILED(hr))
  {
    goto done;
  }

  // Audio attributes.
  hr = MP4CreateAudioProfile(audio_profile, &pAudio);
  if(FAILED(hr))
  {
    goto done;
  }

  hr = pProfile->SetAudioAttributes(pAudio);
  if(FAILED(hr))
  {
    goto done;
  }

  // Video attributes.
  hr = MP4CreateVideoProfile(video_profile, &pVideo);
  if(FAILED(hr))
  {
    goto done;
  }

  hr = pProfile->SetVideoAttributes(pVideo);
  if(FAILED(hr))
  {
    goto done;
  }

  // Container attributes.
  hr = MFCreateAttributes(&pContainer, 1);
  if(FAILED(hr))
  {
    goto done;
  }

  hr = pContainer->SetGUID(MF_TRANSCODE_CONTAINERTYPE, MFTranscodeContainerType_MPEG4);
  if(FAILED(hr))
  {
    goto done;
  }

  hr = pProfile->SetContainerAttributes(pContainer);
  if(FAILED(hr))
  {
    goto done;
  }

  *ppProfile = pProfile;
  (*ppProfile)->AddRef();

done:
  SafeRelease(&pProfile);
  SafeRelease(&pAudio);
  SafeRelease(&pVideo);
  SafeRelease(&pContainer);
  return hr;
}

HRESULT MP4RunEncodingSession(MP4EncodingSession *pSession, MFTIME duration)
{
  PRECONDITION_RETURN(pSession != 0, E_INVALIDARG);

  const DWORD WAIT_PERIOD = 500;
  const int   UPDATE_INCR = 5;

  HRESULT hr = S_OK;
  MFTIME pos;
  LONGLONG prev = 0;
  while(1)
  {
    hr = pSession->Wait(WAIT_PERIOD);
    if(hr == E_PENDING)
    {
      hr = pSession->GetEncodingPosition(&pos);

      LONGLONG percent = (100 * pos) / duration;
      if(percent >= prev + UPDATE_INCR)
      {
        std::cout << percent << "% .. ";
        prev = percent;
      }
    }
    else
    {
      std::cout << std::endl;
      break;
    }
  }
  return hr;
}

HRESULT MP4EncodeFile(PCWSTR pszInput, PCWSTR pszOutput)
{
  PRECONDITION_RETURN(pszInput != 0, E_INVALIDARG);
  PRECONDITION_RETURN(pszOutput != 0, E_INVALIDARG);

  IMFMediaSource* pSource = 0;
  HRESULT hr = MP4CreateMediaSource(pszInput, &pSource);
  if(SUCCEEDED(hr))
  {
    MFTIME duration = 0;
    hr = MP4GetSourceDuration(pSource, &duration);
    if(SUCCEEDED(hr))
    {
      IMFTranscodeProfile* pProfile = 0;
      hr = MP4CreateTranscodingProfile(&pProfile);
      if(SUCCEEDED(hr))
      {
        IMFTopology* pTopology = 0;
        hr = MFCreateTranscodeTopology(pSource, pszOutput, pProfile, &pTopology);
        if(SUCCEEDED(hr))
        {
          MP4EncodingSession* pSession = 0;
          hr = MP4EncodingSession::Create(&pSession);
          if(SUCCEEDED(hr))
          {
            hr = pSession->StartEncodingSession(pTopology);
            if(SUCCEEDED(hr))
            {
              hr = MP4RunEncodingSession(pSession, duration);
              pSource->Shutdown();
            }

            SafeRelease(&pSession);
          }

          SafeRelease(&pTopology);
        }

        SafeRelease(&pProfile);
      }
    }

    SafeRelease(&pSource);
  }

  return hr;
}

}}
