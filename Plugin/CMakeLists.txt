################################################################################
#
# Copyright (c) The Ultraschall Project (http://ultraschall.fm)
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

cmake_minimum_required(VERSION 3.12.0)
project(reaper_ultraschall VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE MATCHES DEBUG)
    set(ULTRASCHALL_BUILD_TYPE Debug)
else()
    set(ULTRASCHALL_BUILD_TYPE Release)
endif()

set(ULTRASCHALL_PATH ${CMAKE_SOURCE_DIR})
set(ULTRASCHALL_EXT_PATH ${ULTRASCHALL_PATH}/_ext)
set(ULTRASCHALL_SRC_PATH ${ULTRASCHALL_PATH}/reaper_ultraschall)

if(WIN32)
    include(${CMAKE_SOURCE_DIR}/_scripts/win32/prereqs.cmake)
elseif(APPLE)
    include(_scripts/macos/prereqs.cmake)
elseif(UNIX)
    include(_scripts/linux/prereqs.cmake)
endif()

add_subdirectory(reaper_ultraschall)
