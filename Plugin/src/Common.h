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

#ifndef __ULTRASCHALL_REAPER_COMMON_H_INCL__
#define __ULTRASCHALL_REAPER_COMMON_H_INCL__

#include <cctype>
#include <cstdint>
#include <cstdlib>

#include <map>
#include <string>
#include <vector>
#include <deque>

#include <algorithm>
#include <functional>

#include <sstream>
#include <fstream>
#include <iomanip>

#include <atomic>
#include <mutex>

#include <chrono>
#include <ctime>

#include "ServiceStatus.h"
#include "SharedObject.h"
#include "UnicodeString.h"

namespace ultraschall { namespace reaper {

#define PRECONDITION(a) \
    {                   \
        if ((a) == 0)   \
        {               \
            return;     \
        }               \
    }

#define PRECONDITION_RETURN(a, b) \
    {                             \
        if ((a) == 0)             \
        {                         \
            return (b);           \
        }                         \
    }

template<class T> inline static void SafeDelete(T*& ptr)
{
    delete ptr;
    ptr = 0;
}

template<class T> inline static void SafeDeleteArray(T*& ptr)
{
    delete[] ptr;
    ptr = 0;
}

template<class T> inline static void SafeRelease(T*& ptr)
{
    if (ptr != 0)
    {
        ptr->Release();
        ptr = 0;
    }
}

}} // namespace ultraschall::reaper

#endif // #ifndef __ULTRASCHALL_REAPER_COMMON_H_INCL__
