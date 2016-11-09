////////////////////////////////////////////////////////////////////////////////
// 
// Copyright (c) 2016 Ultraschall (http://ultraschall.fm)
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

#ifndef __ULTRASCHALL_FRAMEWORK_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_H_INCL__

#include <Platform.h>

#include <cstdint>
#include <string>
#include <vector>
#include <map>

namespace ultraschall { namespace framework {

#define PRECONDITION(a) \
{ \
   if((a) == 0) \
   { \
      return; \
   } \
}

#define PRECONDITION_RETURN(a, b) \
{ \
   if((a) == 0) \
      { \
      return (b); \
      } \
}

template<class PointerType> inline static void SafeDelete(PointerType*& ptr)
{
   delete ptr;
   ptr = 0;
}

template<class PointerType> inline static void SafeDeleteArray(PointerType*& ptr)
{
   delete [] ptr;
   ptr = 0;
}

template<class ReferenceCountedType> inline static void SafeRelease(ReferenceCountedType*& ptr)
{
   if(ptr != 0)
   {
      ptr->Release();
      ptr = 0;
   }
}

template<class ReferenceCountedType> inline static void SafeRetain(ReferenceCountedType* ptr)
{
   if(ptr != 0)
   {
      ptr->AddRef();
   }
}
   
}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_H_INCL__
