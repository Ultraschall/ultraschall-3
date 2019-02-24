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

cmake_minimum_required(VERSION 3.13.0)
project(reaper_ultraschall VERSION 3.2)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    include(win32.cmake)
elseif(APPLE)
    include(macos.cmake)
elseif(UNIX)
    include(linux.cmake)
endif()

set(REAPER_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/_ext/reaper_extension_sdk/jmde)

message(STATUS "REAPER_INCLUDE_PATH = ${REAPER_INCLUDE_PATH}")

include_directories(
    ${LIBZ_INCLUDE_PATH}
    ${LIBCURL_INCLUDE_PATH}
    ${LIBMP4V2_INCLUDE_PATH}
    ${LIBTAG_INCLUDE_PATH}
    ${LIBJSON11_INCLUDE_PATH}
    ${LIBWXWIDGETS_INCLUDE_PATH}
    ${REAPER_INCLUDE_PATH}
)

add_subdirectory(reaper_ultraschall)

add_dependencies(reaper_ultraschall zlib-build)
add_dependencies(reaper_ultraschall curl-build)
add_dependencies(reaper_ultraschall mp4v2-build)
add_dependencies(reaper_ultraschall taglib-build)
add_dependencies(reaper_ultraschall json11-build)
add_dependencies(reaper_ultraschall wxwidgets-build)

set_target_properties(reaper_ultraschall PROPERTIES PREFIX "")
