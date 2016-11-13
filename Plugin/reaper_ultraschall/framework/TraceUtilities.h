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

#ifndef __ULTRASCHALL_FRAMEWORK_TRACE_UTILITIES_H_INCL__
#define __ULTRASCHALL_FRAMEWORK_TRACE_UTILITIES_H_INCL__

#include <cstdarg>

typedef const enum {
   TRACE_LEVEL_FATAL    = 0x00000000,
   TRACE_LEVEL_ERROR    = 0x00000001,
   TRACE_LEVEL_WARNING  = 0x00000002,
   TRACE_LEVEL_INFO     = 0x00000003,
   TRACE_LEVEL_DEBUG    = 0x00000004,
   MAX_TRACE_LEVEL      = TRACE_LEVEL_DEBUG,
   INVALID_TRACE_LEVEL  = MAX_TRACE_LEVEL + 1
} TraceLevel;

namespace ultraschall {
namespace framework {

void TraceVa_0(const TraceLevel level, const char* format, va_list args);

void Trace_0(const TraceLevel level, const char* format, ...);

void TraceVa_1(const TraceLevel level, const char* file, const int line, const char* format, va_list args);

void Trace_1(const TraceLevel level, const char* file, const int line, const char* format, ...);

}
}

#define Trace0(level, format) \
ultraschall::framework::Trace_1((level), __FILE__, __LINE__, (format))
#define Trace1(level, format, arg1) \
ultraschall::framework::Trace_1((level), __FILE__, __LINE__, (format), (arg1))
#define Trace2(level, format, arg1, arg2) \
ultraschall::framework::Trace_1((level), __FILE__, __LINE__, (format), (arg1), (arg2))
#define Trace3(level, format, arg1, arg2, arg3) \
ultraschall::framework::Trace_1((level), __FILE__, __LINE__, (format), (arg1), (arg2), (arg3))
#define Trace4(level, format, arg1, arg2, arg3, arg4) \
ultraschall::framework::Trace_1((level), __FILE__, __LINE__, (format), (arg1), (arg2), (arg3), (arg4))
#define Trace5(level, format, arg1, arg2, arg3, arg4, arg5) \
ultraschall::framework::Trace_1((level), __FILE__, __LINE__, (format), (arg1), (arg2), (arg3), (arg4), (arg5))
#define Trace6(level, format, arg1, arg2, arg3, arg4, arg5, arg6) \
ultraschall::framework::Trace_1((level), __FILE__, __LINE__, (format), (arg1), (arg2), (arg3), (arg4), (arg5), (arg6))
#define Trace7(level, format, arg1, arg2, arg3, arg4, arg5, arg6, arg7) \
ultraschall::framework::Trace_1((level), __FILE__, __LINE__, (format), (arg1), (arg2), (arg3), (arg4), (arg5), (arg6), (arg7))
#define Trace8(level, format, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8) \
ultraschall::framework::Trace_1((level), __FILE__, __LINE__, (format), (arg1), (arg2), (arg3), (arg4), (arg5), (arg6), (arg7), (arg8))
#define Trace9(level, format, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9) \
ultraschall::framework::Trace_1((level), __FILE__, __LINE__, (format), (arg1), (arg2), (arg3), (arg4), (arg5), (arg6), (arg7), (arg8), (arg9))
#define Trace10(level, format, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10) \
ultraschall::framework::Trace_1((level), __FILE__, __LINE__, (format), (arg1), (arg2), (arg3), (arg4), (arg5), (arg6), (arg7), (arg8), (arg9), (arg10))

#endif // #ifndef __ULTRASCHALL_FRAMEWORK_TRACE_UTILITIES_H_INCL__
