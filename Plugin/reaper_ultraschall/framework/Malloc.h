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

#ifndef __ULTRASCHALL_FRAMEWORK_MALLOC_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_MALLOC_H_INCL__

#include <Framework.h>

namespace ultraschall { namespace framework {

template<typename I> class CAllocator
{
public:
   typedef I item_type;

   static item_type* Alloc(const size_t itemCount)
   {
      PRECONDITION_RETURN(itemCount > 0, 0);

      return reinterpret_cast<item_type*>(calloc(itemCount, sizeof(I)));
   }

   static item_type* Realloc(item_type* ptr, const size_t itemCount)
   {
      PRECONDITION_RETURN(ptr != 0, 0);
      PRECONDITION_RETURN(itemCount > 0, 0);

      return reinterpret_cast<item_type*>(realloc(ptr, sizeof(item_type) * itemCount));
   }
   
   static void Free(item_type*& ptr)
   {
      PRECONDITION(ptr != 0);
      
      free(reinterpret_cast<void*>(ptr));
      ptr = 0;
   }
};
   
template<typename I> class CppAllocator
{
public:
   typedef I item_type;

   static item_type* Alloc(const size_t itemCount)
   {
      PRECONDITION_RETURN(itemCount > 0, 0);

      item_type* ptr = new item_type[itemCount];
      if(ptr != 0)
      {
         memset(ptr, 0, sizeof(item_type) * itemCount);
      }

      return ptr;
   }
   
   static item_type* Realloc(item_type*, const size_t)
   {
      return 0;
   }

   static void Free(item_type*& ptr)
   {
      delete [] ptr;
      ptr = 0;
}
};

#ifdef WIN32
template<class I> class ComAllocator
{
public:
   typedef typename I item_type;
   

   static item_type* Alloc(const size_t itemCount)
   {
      PRECONDITION_RETURN(itemCount > 0, 0);

      void *ptr = CoTaskMemAlloc(sizeof(item_type) * itemCount);
      if(ptr != 0)
      {
         std::memset(ptr, 0, sizeof(item_type) * itemCount);
      }
   
      return reinterpret_cast<I>(ptr);
   }

   static item_type* Realloc(item_type* ptr, const size_t itemCount)
   {
      PRECONDITION_RETURN(itemCount > 0, 0);

      return reinterpret_cast<item_type*>(CoTaskMemRealloc(reinterpret_cast<void*>(ptr), sizeof(item_type) * itemCount));
   }

   static void Free(item_type*& ptr)
   {
      PRECONDITION(ptr != 0);
      
      CoTaskMemFree(reinterpret_cast<void*>(ptr));
      ptr = 0;
   }
};
#endif

template<class I, class A = CAllocator<I>> class Malloc
{
public:
   typedef I item_type;
   typedef A allocator_type;

   static size_t Size()
   {
      return sizeof(item_type);
   }

   static item_type* Alloc(const size_t itemCount = 1)
   {
      return allocator_type::Alloc(itemCount);
   }

   static item_type* Realloc(item_type* ptr, const size_t itemCount)
   {
      return allocator_type::Realloc(ptr, itemCount);
   }
   
   static void Free(item_type*& ptr)
   {
      allocator_type::Free(ptr);
   }
};
   
}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_MALLOC_H_INCL__
