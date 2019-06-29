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

#include "UIFileDialog.h"

#include "ReaperEntryPoints.h"

namespace ultraschall
{
namespace reaper
{

UIFileDialog::UIFileDialog(const UnicodeString &caption, const UnicodeString &initialDirectory) : caption_(caption), initialDirectory_(initialDirectory)
{
    if (caption_.empty() == true)
    {
        caption_ = "Open file";
    }
}

UnicodeString UIFileDialog::BrowseForFile(const UnicodeString &fileExtensions)
{
    UnicodeString filename;

    UnicodeString actualFileExtension = "All files|*.*";
    if (fileExtensions.empty() == false)
    {
        actualFileExtension = fileExtensions;
    }

    // wxFileDialog fileDialog(
    //     reaoer_api::GetMainHwnd(), U2H(caption_), U2H(initialDirectory_), "",
    //     U2H(actualFileExtension), wxFD_OPEN, wxDefaultPosition);
    // if (fileDialog.ShowModal() == wxID_OK)
    // {
    //     wxString resultPath;
    //     resultPath.Append(fileDialog.GetDirectory());
    //     resultPath.Append(wxFileName::GetPathSeparator());
    //     resultPath.Append(fileDialog.GetFilename());
    //     filename = H2U(UnicodeString(resultPath.mb_str()));
    // }

    return filename;
}

UnicodeString UIFileDialog::BrowseForChapters()
{
    const UnicodeString fileExtensions = "MP4 chapters|*.chapters.txt|"
                                         "MP4 chapters|*.mp4chaps|"
                                         "All files|*.*";
    return BrowseForFile(fileExtensions);
}

#ifdef ULTRASCHALL_ENABLE_MP4
UnicodeString UIFileDialog::BrowseForAudio()
{
    const UnicodeString fileExtensions = "MP3 file|*.mp3|"
                                         "MP4 file|*.mp4|"
                                         "M4A file|*.m4a|"
                                         "All files|*.*";
    return BrowseForFile(fileExtensions);
}
#else  // #ifdef ULTRASCHALL_ENABLE_MP4
UnicodeString UIFileDialog::BrowseForAudio()
{
    const UnicodeString fileExtensions = "MP3 file|*.mp3|"
                                         "All files|*.*";
    return BrowseForFile(fileExtensions);
}
#endif // #ifdef ULTRASCHALL_ENABLE_MP4

UnicodeString UIFileDialog::BrowseForPicture()
{
    const UnicodeString fileExtensions = "JPG file|*.jpg|"
                                         "PNG file|*.png|"
                                         "All files|*.*";
    return BrowseForFile(fileExtensions);
}

UnicodeString UIFileDialog::BrowseForDirectory()
{
    UnicodeString directory;

    // wxDirDialog directoryDialog(
    //     reaoer_api::GetMainHwnd(), "Select", U2H(initialDirectory_), 0,
    //     wxDefaultPosition);
    // if (directoryDialog.ShowModal() == wxID_OK)
    // {
    //     wxString resultPath;
    //     resultPath.Append(directoryDialog.GetPath());
    //     directory = H2U(UnicodeString(resultPath.mb_str()));
    // }

    return directory;
}

} // namespace reaper
} // namespace ultraschall
