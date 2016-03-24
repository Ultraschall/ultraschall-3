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

#ifndef __ULTRASCHALL_FRAMEWORK_MALLOC_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_MALLOC_H_INCL__

#include <Framework.h>

namespace ultraschall { namespace framework {

template<typename Type> class Malloc
{
public:
   static size_t Size();

   static Type* Alloc(const size_t itemCount = 1);
   
   static void Free(Type*& ptr);
};
   
template<typename Type> size_t Malloc<Type>::Size()
{
   return sizeof(Type);
}
   
template<typename Type> Type* Malloc<Type>::Alloc(const size_t itemCount)
{
   Type* ptr = new Type[itemCount];
   if(ptr != 0)
   {
      std::memset(ptr, 0, Size() * itemCount);
   }
   
   return ptr;
}
   
template<typename Type> void Malloc<Type>::Free(Type*& ptr)
{
   SafeDeleteArray(ptr);
}
   
}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_MALLOC_H_INCL__
