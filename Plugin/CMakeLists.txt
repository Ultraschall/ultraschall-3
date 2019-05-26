################################################################################
#
# Copyright (c) The Ultraschall Project (http://ultraschall.fm)
#
# The MIT License (MIT)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
################################################################################

cmake_minimum_required(VERSION 3.10.2)
project(reaper_ultraschall VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "Currently running on " ${CMAKE_SYSTEM})

set(ULTRASCHALL_TARGET_NAME "<unknown>")

if(WIN32)
    set(ULTRASCHALL_TARGET_SYSTEM "win32")
elseif(APPLE)
    set(ULTRASCHALL_TARGET_SYSTEM "macos")
elseif(UNIX)
    if(${CMAKE_SYSTEM} MATCHES "arch")
        set(ULTRASCHALL_TARGET_SYSTEM "arch")
    elseif(${CMAKE_SYSTEM} MATCHES "ubuntu")
        set(ULTRASCHALL_TARGET_SYSTEM "ubuntu")
    elseif(${CMAKE_SYSTEM} MATCHES "Microsoft")
        set(ULTRASCHALL_TARGET_SYSTEM "ubuntu")
    endif()
endif()

message(STATUS "ULTRASCHALL_TARGET_SYSTEM = " ${ULTRASCHALL_TARGET_SYSTEM})

if(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "win32")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/win32.cmake)
elseif(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "macos")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/macos.cmake)
elseif(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "arch")
   	include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/arch.cmake)
elseif(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "ubuntu")
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/ubuntu.cmake)
else()
    message(STATUS "Unsupported platform: " ${ULTRASCHALL_TARGET_SYSTEM})
    message(FATAL_ERROR "Supported platforms are Windows, macOS, Arch Linux or Ubuntu Linux")
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)
