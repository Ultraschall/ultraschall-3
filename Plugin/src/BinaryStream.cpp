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

#include "BinaryStream.h"
#include <cstring>
#include <zlib.h>

namespace ultraschall { namespace reaper {

BinaryStream::BinaryStream(const size_t dataSize) : dataSize_(dataSize), data_(new uint8_t[dataSize]) {}

BinaryStream::~BinaryStream()
{
    dataSize_ = INVALID_DATA_SIZE;
    SafeDeleteArray(data_);
}

size_t BinaryStream::DataSize() const
{
    return dataSize_;
}

const uint8_t* BinaryStream::Data() const
{
    return data_;
}

bool BinaryStream::Write(const size_t offset, const uint8_t* buffer, const size_t bufferSize)
{
    PRECONDITION_RETURN(data_ != nullptr, false);
    PRECONDITION_RETURN((offset + bufferSize) <= dataSize_, false);
    PRECONDITION_RETURN(buffer != nullptr, false);

    const size_t itemSize = sizeof(uint8_t);
    memmove(&data_[offset * itemSize], buffer, bufferSize * itemSize);
    return true;
}

bool BinaryStream::Read(const size_t offset, uint8_t* buffer, const size_t bufferSize)
{
    PRECONDITION_RETURN(data_ != nullptr, false);
    PRECONDITION_RETURN((offset + bufferSize) < dataSize_, false);
    PRECONDITION_RETURN(buffer != nullptr, false);

    const size_t itemSize = sizeof(uint8_t);
    memmove(buffer, &data_[offset * itemSize], bufferSize * itemSize);
    return true;
}

uint64_t BinaryStream::CRC32() const
{
    PRECONDITION_RETURN(data_ != nullptr, UINT64_MAX);
    PRECONDITION_RETURN(dataSize_ > 0, UINT64_MAX);

    uint64_t crc = crc32(0, Z_NULL, 0);
    return crc32(static_cast<uLong>(crc), data_, static_cast<uInt>(dataSize_));
}

}} // namespace ultraschall::reaper
