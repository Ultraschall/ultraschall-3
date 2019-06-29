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

#ifndef __ULTRASCHALL_REAPER_BINARY_STREAM_H_INCL__
#define __ULTRASCHALL_REAPER_BINARY_STREAM_H_INCL__

#include "Common.h"
#include "SharedObject.h"

namespace ultraschall { namespace reaper {

class BinaryStream : public SharedObject
{
public:
    static const size_t INVALID_DATA_SIZE = -1;

    BinaryStream(const size_t dataSize);

    size_t DataSize() const;

    const uint8_t* Data() const;

    bool Write(const size_t offset, const uint8_t* buffer, const size_t bufferSize);

    bool Read(const size_t offset, uint8_t* buffer, const size_t bufferSize);

    uint64_t CRC32() const;

protected:
    virtual ~BinaryStream();

private:
    size_t   dataSize_ = INVALID_DATA_SIZE;
    uint8_t* data_     = nullptr;
};

}} // namespace ultraschall::reaper

#endif // #ifdef __ULTRASCHALL_REAPER_BINARY_STREAM_H_INCL__
