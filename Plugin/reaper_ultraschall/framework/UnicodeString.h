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

#ifndef __ULTRASCHALL_FRAMEWORK_STRING_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_STRING_H_INCL__

#include <Framework.h>
#include <UnicodeStringTraits.h>
#include <Malloc.h>

namespace ultraschall { namespace framework {
   
template<typename CharType> class UnicodeString
{
public:
   typedef CharType char_type;
   
   UnicodeString();
   UnicodeString(const UnicodeString& rhs);
   UnicodeString(const char_type* rhs);

   virtual ~UnicodeString();
   
   const UnicodeString& operator=(const UnicodeString& rhs);
   const UnicodeString& operator=(const char_type* rhs);

   const bool operator==(const UnicodeString& rhs) const;
   const bool operator!=(const UnicodeString& rhs) const;
   
private:
   char_type* data_;
};

template<typename CharType> UnicodeString<CharType>::UnicodeString() :
   data_(0)
{
}

template<typename CharType> UnicodeString<CharType>::UnicodeString(const UnicodeString<CharType>& rhs) :
   data_(0)
{
   *this = rhs;
}

template<typename CharType> UnicodeString<CharType>::UnicodeString(const char_type* rhs) :
   data_(0)
{
   operator=(rhs);
}
   
   
template<typename CharType> UnicodeString<CharType>::~UnicodeString()
{
   Malloc<char_type>::Free(data_);
}

template<typename CharType> const UnicodeString<CharType>& UnicodeString<CharType>::operator=(const UnicodeString<CharType>& rhs)
{
   if(this != &rhs)
   {
      operator=(data_);
   }

   return *this;
}

template<typename CharType> const UnicodeString<CharType>& UnicodeString<CharType>::operator=(const char_type* rhs)
{
   if(data_ != rhs)
   {
      Malloc<char_type>::Free(data_);
      
      const size_t sourceSize = UnicodeStringTraits<char_type>::strlen(rhs);
      if(sourceSize > 0)
      {
         data_ = Malloc<char_type>::Alloc(sourceSize + 1);
         if(data_ != 0)
         {
            UnicodeStringTraits<char_type>::strcpy(data_, rhs);
         }
      }
   }

   return *this;
}
   
template<typename CharType> const bool UnicodeString<CharType>::operator==(const UnicodeString<CharType>& rhs) const
{
   return UnicodeStringTraits<CharType>::strcmp(data_, rhs.data_) == 0;
}

template<typename CharType> const bool UnicodeString<CharType>::operator!=(const UnicodeString<CharType>& rhs) const
{
   return operator==(rhs) == false;
}
   
}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_STRING_H_INCL__
