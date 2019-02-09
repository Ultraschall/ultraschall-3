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

#include "PictureUtilities.h"

namespace ultraschall { namespace reaper {

PICTURE_FORMAT QueryPictureFormat(const uint8_t* data, const size_t dataSize)
{
    PRECONDITION_RETURN(data != 0, PICTURE_FORMAT::UNKNOWN_PICTURE);
    PRECONDITION_RETURN(dataSize > 0, PICTURE_FORMAT::UNKNOWN_PICTURE);

    PICTURE_FORMAT format = PICTURE_FORMAT::UNKNOWN_PICTURE;

    if (dataSize >= 2)
    {
        if ((data[0] == 0xff) && (data[1] == 0xd8))
        {
            format = PICTURE_FORMAT::JPEG_PICTURE;
        }

        if (dataSize >= 8)
        {
            if ((data[0] == 0x89) && (data[1] == 0x50) && (data[2] == 0x4e) && (data[3] == 0x47))
            {
                format = PICTURE_FORMAT::PNG_PICTURE;
            }
        }
    }

    return format;
}

}} // namespace ultraschall::reaper
