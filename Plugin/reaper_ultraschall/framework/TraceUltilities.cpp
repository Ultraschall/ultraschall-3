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

#include <cstdio>

#ifdef ULTRASCHALL_PLATFORM_WIN32
#include <windows.h>
#endif

#include "TraceUtilities.h"

namespace ultraschall {
namespace framework {

static const size_t MAX_TRACE_MESSAGE_SIZE = 1024;

void Trace_0(const TraceLevel level, const char* format, ...)
{
   va_list args = {0};
   va_start(args, format);
   TraceVa_0(level, format, args);
   va_end(args);
}

void TraceVa_0(const TraceLevel /*level*/, const char* format, va_list args)
{
#ifdef ULTRASCHALL_PLATFORM_WIN32
   char buffer[MAX_TRACE_MESSAGE_SIZE] = {0};
   _vsnprintf_s(buffer, MAX_TRACE_MESSAGE_SIZE, format, args);

   char message[MAX_TRACE_MESSAGE_SIZE * 2] = {0};
   _snprintf_s(message, MAX_TRACE_MESSAGE_SIZE * 2, "ULTRASCHALL: %s\n",  buffer);

   OutputDebugStringA(message);
#else
#ifdef ULTRASCHALL_PLATFORM_MACOS
// TODO
#endif
#endif

}

void Trace_1(const TraceLevel level, const char* file, const int line, const char* format, ...)
{
   va_list args = {0};
   va_start(args, format);
   TraceVa_1(level, file, line, format, args);
   va_end(args);
}

void TraceVa_1(const TraceLevel /*level*/, const char* file, const int line, const char* format, va_list args)
{
#ifdef ULTRASCHALL_PLATFORM_WIN32
   char buffer[MAX_TRACE_MESSAGE_SIZE] = { 0 };
   _vsnprintf_s(buffer, MAX_TRACE_MESSAGE_SIZE, format, args);

   char message[MAX_TRACE_MESSAGE_SIZE * 2] = { 0 };
   _snprintf_s(message, MAX_TRACE_MESSAGE_SIZE * 2, "ULTRASCHALL: %s(%d): %s\n", file, line, buffer);

   OutputDebugStringA(message);
#else
#ifdef ULTRASCHALL_PLATFORM_MACOS
// TODO
#endif
#endif
}


}
}

