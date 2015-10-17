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

#ifndef __ULTRASCHALL_FRAMEWORK_STRING_TRAITS_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_STRING_TRAITS_H_INCL__

#include <Framework.h>

namespace ultraschall { namespace framework {
   
template<typename CharType> class UnicodeStringTraits
{
public:
   typedef CharType char_type;
   
   static const bool Equal(const char_type* lhs, const char_type* rhs);
   
private:
   static const size_t strlen(const char_type* str);

   static const int strcmp(const char_type* left, const char_type* right);
   
   static void strcpy(char_type* target, const char_type* source);

   static const char_type* strdup(const char_type* source);
};
   
template<typename CharacterType> const bool UnicodeStringTraits<CharacterType>::Equal(const CharacterType* lhs, const CharacterType* rhs)
{
   return strcmp(lhs, rhs) == 0;
}

}}

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_STRING_TRAITS_H_INCL__
