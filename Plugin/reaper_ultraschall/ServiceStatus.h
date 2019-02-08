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

#ifndef __ULTRASCHALL_REAPER_SERVICE_STATUS_H_INCL__
#define __ULTRASCHALL_REAPER_SERVICE_STATUS_H_INCL__

#include "Common.h"

typedef uint32_t ServiceStatus;

#define SERVICE_STATUS_CODE(facility, code) ((facility) | (code))
#define DEFINE_SERVICE_STATUS(status, facility, code) extern ServiceStatus(status) = SERVICE_STATUS_CODE((facility), (code))

// General status codes
#define SERVICE_FRAMEWORK_FACILITY 0x00000000
#define SERVICE_SUCCESS SERVICE_STATUS_CODE(SERVICE_FRAMEWORK_FACILITY, 0x00000000)
#define SERVICE_FAILURE SERVICE_STATUS_CODE(SERVICE_FRAMEWORK_FACILITY, 0x00000001)
#define SERVICE_NOT_FOUND SERVICE_STATUS_CODE(SERVICE_FRAMEWORK_FACILITY, 0x00000002)
#define SERVICE_INVALID_ARGUMENT SERVICE_STATUS_CODE(SERVICE_FRAMEWORK_FACILITY, 0x00000003)
#define SERVICE_NOT_IMPLEMENTED SERVICE_STATUS_CODE(SERVICE_FRAMEWORK_FACILITY, 0x00000004)

// Service manager status codes
#define SERVICE_MANAGER_FACILITY 0x80000000
#define SERVICE_MANAGER_ALREADY_REGISTERED SERVICE_STATUS_CODE(SERVICE_MANAGER_FACILITY, 0x00000002)
#define SERVICE_MANAGER_NOT_FOUND SERVICE_STATUS_CODE(SERVICE_MANAGER_FACILITY, 0x00000003)
#define SERVICE_MANAGER_ACQUIRE_FAILED SERVICE_STATUS_CODE(SERVICE_MANAGER_FACILITY, 0x00000004)

// Service factory status codes
#define SERVICE_FACTORY_FACILITY 0x08000000
#define SERVICE_FACTORY_ALREADY_REGISTERED SERVICE_STATUS_CODE(SERVICE_FACTORY_FACILITY, 0x00000002)
#define SERVICE_FACTORY_NOT_FOUND SERVICE_STATUS_CODE(SERVICE_FACTORY_FACILITY, 0x00000003)
#define SERVICE_FACTORY_CREATE_FAILED SERVICE_STATUS_CODE(SERVICE_FACTORY_FACILITY, 0x00000004)

#define ServiceSucceeded(status) ((status) == SERVICE_SUCCESS)
#define ServiceFailed(status) ((status) != SERVICE_SUCCESS)

#endif // #ifndef __ULTRASCHALL_REAPER_SERVICE_STATUS_H_INCL__
