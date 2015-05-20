////////////////////////////////////////////////////////////////////////////////
// 
// Copyright (c) 2014-2015 Ultraschall (http://ultraschall.fm)
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

#include <Framework.h>
#include "Application.h"
#include "FileManager.h"

#ifdef WIN32
#include <windows.h>
#include <shobjidl.h>
#else
#import <AppKit/AppKit.h>
#endif

namespace framework = ultraschall::framework;

namespace ultraschall { namespace reaper {

const std::string FileManager::BrowseForFiles(const std::string& title)
{
   std::string path;

#ifdef WIN32
   
   const bool uninitializeRequired = (CoInitialize(0) == S_OK);

   IFileOpenDialog* pfod = 0;      
   HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, 0, CLSCTX_INPROC_SERVER, IID_IFileDialog, (void**)&pfod);
   if(SUCCEEDED(hr))
   {
      COMDLG_FILTERSPEC filterSpec = {0};
      filterSpec.pszName = L"MP4CHAPS";
      filterSpec.pszSpec = L"*.mp4chaps";

// TODO: convert title to UTF-16
      pfod->SetTitle(L"Kapitelmarken laden...");
      pfod->SetFileTypes(1, &filterSpec);
      pfod->SetOptions(FOS_FILEMUSTEXIST);

      hr = pfod->Show(Application::Instance().GetMainHwnd());
      if(SUCCEEDED(hr))
      {
         IShellItem* psi = 0;
         hr = pfod->GetResult(&psi);
         if(SUCCEEDED(hr))
         {
            LPWSTR displayName = 0;
            hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &displayName);
            if(SUCCEEDED(hr))
            {
               const size_t ansiBufferSize = (2 * (MAX_PATH + 1));
               char ansiBuffer[ansiBufferSize] = { 0 };
               size_t noConvertedChars = 0;
               wcstombs_s(&noConvertedChars, ansiBuffer, displayName, ansiBufferSize);
               path = ansiBuffer;

               CoTaskMemFree(displayName);
               displayName = 0;
            }

            framework::SafeRelease(psi);
         }
      }

      framework::SafeRelease(pfod);
   }

   if(uninitializeRequired == true)
   {
      CoUninitialize();
   }

#else
   
   NSOpenPanel* fileDialog = [NSOpenPanel openPanel];
   if(nil != fileDialog)
   {
      fileDialog.canChooseFiles = YES;
      fileDialog.canChooseDirectories = NO;
      fileDialog.canCreateDirectories = NO;
      fileDialog.allowsMultipleSelection = NO;
      fileDialog.title = [NSString stringWithUTF8String: title.c_str()];

#if 0 // can't use recent APIs. REAPER builds with an OS version less than 10.6
      fileDialog.allowedFileTypes = [[NSArray alloc] initWithObjects: @"mp4chaps", nil];
      fileDialog.allowsOtherFileTypes = NO;
      if([fileDialog runModal] == NSFileHandlingPanelOKButton)
#endif
   
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
      if([fileDialog runModalForTypes:[[NSArray alloc] initWithObjects:@"mp4chaps", nil]] == NSFileHandlingPanelOKButton)
#pragma clang diagnostic pop
      {
         path = [[fileDialog URL] fileSystemRepresentation];
      }
      
      fileDialog = nil;
   }
   
#endif
   
   return path;
}

const std::string FileManager::BrowseForFolder(const std::string& title, const std::string& folder)
{
   std::string path;
   
#ifdef WIN32

   const bool uninitializeRequired = (CoInitialize(0) == S_OK);

   IFileOpenDialog* pfod = 0;      
   HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, 0, CLSCTX_INPROC_SERVER, IID_IFileDialog, (void**)&pfod);
   if(SUCCEEDED(hr))
   {
      COMDLG_FILTERSPEC filterSpec = {0};
      filterSpec.pszName = L"MP4CHAPS";
      filterSpec.pszSpec = L"*.mp4chaps";

// TODO: convert title to UTF-16
      pfod->SetTitle(L"Kapitelmarken speichern...");
      pfod->SetFileTypes(1, &filterSpec);
      pfod->SetOptions(FOS_PICKFOLDERS|FOS_PATHMUSTEXIST);

      hr = pfod->Show(Application::Instance().GetMainHwnd());
      if(SUCCEEDED(hr))
      {
         IShellItem* psi = 0;
         hr = pfod->GetResult(&psi);
         if(SUCCEEDED(hr))
         {
            LPWSTR displayName = 0;
            hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &displayName);
            if(SUCCEEDED(hr))
            {
               const size_t ansiBufferSize = (2 * (MAX_PATH + 1));
               char ansiBuffer[ansiBufferSize] = { 0 };
               size_t noConvertedChars = 0;
               wcstombs_s(&noConvertedChars, ansiBuffer, displayName, ansiBufferSize);
               path = ansiBuffer;

               CoTaskMemFree(displayName);
               displayName = 0;
            }

            framework::SafeRelease(psi);
         }
      }

      framework::SafeRelease(pfod);
   }

   if(uninitializeRequired == true)
   {
      CoUninitialize();
   }

#else
   
   NSSavePanel* fileDialog = [NSSavePanel savePanel];
   if(nil != fileDialog)
   {
      fileDialog.canCreateDirectories = YES;
      fileDialog.title = [NSString stringWithUTF8String: title.c_str()];
      fileDialog.directoryURL = [NSURL URLWithString: [NSString stringWithUTF8String: folder.c_str()]];
      if([fileDialog runModal] == NSFileHandlingPanelOKButton)
      {
         path = [[fileDialog URL] fileSystemRepresentation];
      }
      
      fileDialog = nil;
   }
   
#endif
   
   return path;
}
   
const std::string FileManager::AppendPath(const std::string& prefix, const std::string& append)
{
#ifdef WIN32
   const char PATH_DELIMITER_CHAR = '\\';
#else
   const char PATH_DELIMITER_CHAR = '/';
#endif
   return prefix + PATH_DELIMITER_CHAR + append;
}
   
}}

