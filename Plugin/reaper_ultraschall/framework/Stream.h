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
#ifndef __ULTRASCHALL_FRAMEWORK_STREAM_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_STREAM_H_INCL__

#include <zlib.h>
#include <SharedObject.h>
#include <Malloc.h>

namespace ultraschall { namespace framework {
   

template <typename ItemType> class Stream : public SharedObject
{
public:
   Stream(const size_t dataSize) : dataSize_(dataSize)
   {
      data_ = Malloc<ItemType>::Alloc(dataSize_);
   }
   
   const bool Write(const size_t offset, const ItemType* buffer, const size_t bufferSize)
   {
      PRECONDITION_RETURN((offset + bufferSize) <= dataSize_, false);
      PRECONDITION_RETURN(buffer != 0, false);
      
      memmove(&data_[offset * Malloc<ItemType>::Size()], buffer, bufferSize * Malloc<ItemType>::Size());
      return true;
   }
   
   const bool Read(const size_t offset, ItemType* buffer, const size_t bufferSize)
   {
      PRECONDITION_RETURN((offset + bufferSize) < dataSize_, false);
      PRECONDITION_RETURN(buffer != 0, false);

      memmove(buffer, &data_[offset * Malloc<ItemType>::Size()], bufferSize * Malloc<ItemType>::Size());
      return true;
   }
   
   const uint64_t CRC32() const
   {
      PRECONDITION_RETURN(data_ != 0, UINT64_MAX);
      PRECONDITION_RETURN(dataSize_ > 0, UINT64_MAX);
      
      uint64_t crc = crc32(0, Z_NULL, 0);
      return crc32(static_cast<uLong>(crc), data_, static_cast<uInt>(dataSize_));
   }
   
protected:
   virtual ~Stream()
   {
      Malloc<ItemType>::Free(data_);
      dataSize_ = 0;
   }
   
private:
   ItemType* data_;
   size_t dataSize_;
};
   
}}

#endif // #ifdef __ULTRASCHALL_FRAMEWORK_STREAM_H_INCL__
