////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

#ifndef __ULTRASCHALL_REAPER_STRING_UTILITIES_H_INCL__
#define __ULTRASCHALL_REAPER_STRING_UTILITIES_H_INCL__

#ifdef ULTRASCHALL_PLATFORM_MACOS
#ifdef min
#undef min
#endif // #ifdef min
#ifdef max
#undef max
#endif // #ifdef max
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS

#include "Common.h"

namespace ultraschall { namespace reaper {

#define _MAKE_TEXT(str) #str
#define MAKE_TEXT(str) _MAKE_TEXT(str)

inline StringArray StringTokenize(const std::string& input, const char delimiter)
{
    StringArray tokens;
    std::stringstream        stream(input);
    std::string              token;

    while (std::getline(stream, token, delimiter))
    {
        tokens.push_back(token);
    }

    return tokens;
}

// trim from start
static inline std::string& StringTrimLeft(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string& StringTrimRight(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string& StringTrim(std::string& s)
{
    return StringTrimLeft(StringTrimRight(s));
}

static inline void StringReplace(std::string& str, const std::string& source, const std::string& target)
{
    size_t start_pos = 0;
    while ((start_pos = str.find(source, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, source.length(), target);
        start_pos += target.length();
    }
}

static inline int StringToInt(const std::string& str)
{
    int result = -1;

    if (str.empty() == false)
    {
        std::istringstream is(str);
        is >> result;
    }

    return result;
}

std::string StringLowercase(const std::string& str);
std::string StringUppercase(const std::string& str);

#ifdef ULTRASCHALL_PLATFORM_MACOS
typedef char16_t       UnicodeChar;
typedef std::u16string UnicodeString;
#else
typedef wchar_t      UnicodeChar;
typedef std::wstring UnicodeString;
#endif // #ifdef ULTRASCHALL_PLATFORM_MACOS

UnicodeString MakeUnicodeString(const std::string& src);
UnicodeString MakeUnicodeString2(const std::string& src);

UnicodeString MakeUTF16StringWithBOM(const std::string& src);
UnicodeString MakeUTF16StringWithBOM2(const std::string& src);

std::string MakeUTF8String(const UnicodeString& src);

std::wstring AnsiStringToWideUnicodeString(const std::string& ansiString);

std::string UnicodeStringToAnsiString(const std::string& unicodeString, int codepage = 0);

std::wstring UnicodeStringToWideUnicodeString(const std::string& unicodeString);

//---------------------------------------------------------------------------------------------
// 3.1
//---------------------------------------------------------------------------------------------

template<typename I, bool SZ = false> struct UnicodeString2AllocatorT
{
    typedef I           item_type;
    static const size_t ITEM_SIZE    = sizeof(item_type);
    static const size_t INVALID_SIZE = static_cast<size_t>(-1);

    static item_type* Alloc(const size_t itemCount)
    {
        PRECONDITION_RETURN(itemCount > 0, nullptr);

        const size_t targetItemCount = (SZ == true) ? (itemCount + 1) : itemCount;
        return reinterpret_cast<item_type*>(calloc(targetItemCount, ITEM_SIZE));
    }

    static item_type* AllocCopy(const item_type* items, const size_t itemCount)
    {
        PRECONDITION_RETURN(items != nullptr, nullptr);
        PRECONDITION_RETURN(itemCount > 0, nullptr);

        item_type* target = Alloc(itemCount);
        if (target != nullptr)
        {
            memmove(target, items, itemCount);
        }

        return target;
    }

    static const void Free(item_type*& ptr)
    {
        PRECONDITION(ptr != nullptr);

        free(ptr);
        ptr = nullptr;
    }

    static size_t ItemSize()
    {
        return ITEM_SIZE;
    }
};

typedef UnicodeString2AllocatorT<uint8_t>       UnicodeString2Allocator;
typedef UnicodeString2AllocatorT<uint8_t, true> UnicodeStringSz2Allocator;

template<typename A> struct UnicodeString2T
{
    typedef A                     allocator_type;
    typedef typename A::item_type item_type;

    item_type* data_;
    size_t     size_;

    static const size_t INVALID_STRING_SIZE = static_cast<size_t>(-1);

    UnicodeString2T() : data_(nullptr), size_(INVALID_STRING_SIZE) {}

    explicit UnicodeString2T(const std::string& str) : data_(nullptr), size_(INVALID_STRING_SIZE)
    {
        if (str.empty() == false)
        {
            data_ = allocator_type::AllocCopy(reinterpret_cast<const uint8_t*>(str.c_str()), str.size());
            if (data_ != nullptr)
            {
                size_ = str.size();
            }
        }
    }

    UnicodeString2T(const item_type* data, const size_t dataSize) : data_(nullptr), size_(INVALID_STRING_SIZE)
    {
        if ((data != nullptr) && (dataSize != INVALID_STRING_SIZE))
        {
            data_ = allocator_type::AllocCopy(data, dataSize);
            if (data_ != nullptr)
            {
                size_ = dataSize;
            }
        }
    }

    ~UnicodeString2T()
    {
        Clear();
    }

    UnicodeString2T(const UnicodeString2T& rhs) : data_(nullptr), size_(INVALID_STRING_SIZE)
    {
        *this = rhs;
    }

    void operator=(const UnicodeString2T& rhs)
    {
        Clear();

        data_ = allocator_type::AllocCopy(rhs.data_, rhs.size_);
        if (data_ != nullptr)
        {
            size_ = rhs.size_;
        }
    }

    UnicodeString2T operator+(const UnicodeString2T& rhs) const
    {
        UnicodeString2T result;

        if ((rhs.data_ != nullptr) && (rhs.size_ != INVALID_STRING_SIZE))
        {
            if ((data_ != nullptr) && (size_ != INVALID_STRING_SIZE))
            {
                item_type* combinedData = allocator_type::Alloc(size_ + rhs.size_);
                if (combinedData != nullptr)
                {
                    memmove(combinedData, data_, size_);
                    memmove(&combinedData[size_], rhs.data_, rhs.size_);

                    result = UnicodeString2T(combinedData, size_ + rhs.size_);

                    allocator_type::Free(combinedData);
                }
            }
            else
            {
                result = rhs;
            }
        }
        else
        {
            result = *this;
        }

        return result;
    }

    inline const item_type* Data() const
    {
        return data_;
    }

    inline size_t Size() const
    {
        return size_;
    }

    inline void Clear()
    {
        allocator_type::Free(data_);
        size_ = INVALID_STRING_SIZE;
    }

    inline bool Empty() const
    {
        return (nullptr == data_) || (INVALID_STRING_SIZE == size_) || (0 == size_);
    }
};

typedef UnicodeString2T<UnicodeString2Allocator> UnicodeString2;

UnicodeString2 MakeUTF16String2(const std::string& str);
UnicodeString2 MakeUTF8String2(const std::string& str);

inline UnicodeString2 MakeUTF16String2WithBOM(const std::string& str)
{
    static const uint8_t bom[2] = {0xff, 0xfe};
    return UnicodeString2(bom, sizeof(bom)) + MakeUTF16String2(str);
}

inline UnicodeString2 MakeUTF8String2WithBOM(const std::string& str)
{
    static const uint8_t bom[3] = {0xef, 0xbb, 0xbf};
    return UnicodeString2(bom, sizeof(bom)) + MakeUTF8String2(str);
}

typedef UnicodeString2T<UnicodeStringSz2Allocator> UnicodeStringSz2;

UnicodeStringSz2 MakeUTF16StringSz2(const std::string& str);
UnicodeStringSz2 MakeUTF8StringSz2(const std::string& str);

inline UnicodeStringSz2 MakeUTF16StringSz2WithBOM(const std::string& str)
{
    static const uint8_t bom[2] = {0xff, 0xfe};
    return UnicodeStringSz2(bom, sizeof(bom)) + MakeUTF16StringSz2(str);
}

inline UnicodeStringSz2 MakeUTF8StringSz2WithBOM(const std::string& str)
{
    static const uint8_t bom[3] = {0xef, 0xbb, 0xbf};
    return UnicodeStringSz2(bom, sizeof(bom)) + MakeUTF8StringSz2(str);
}

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_STRING_UTILITIES_H_INCL__
