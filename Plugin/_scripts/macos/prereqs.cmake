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

if(APPLE)
    find_package(zlib)
    find_package(curl)

    find_library(taglib_LIBRARIES tag ${ULTRASCHALL_EXT_PATH}/taglib/build/taglib/${ULTRASCHALL_BUILD_TYPE})
    set(taglib_INCLUDE_DIRS
        ${ULTRASCHALL_EXT_PATH}/taglib/include
        ${ULTRASCHALL_EXT_PATH}/taglib/include/toolkit
        ${ULTRASCHALL_EXT_PATH}/taglib/include/mpeg
        ${ULTRASCHALL_EXT_PATH}/taglib/include/mpeg/id3v2
        ${ULTRASCHALL_EXT_PATH}/taglib/include/mpeg/id3v2/frames
        ${ULTRASCHALL_EXT_PATH}/taglib/include/bindings/c
    )

    find_library(mp4v2_LIBRARIES libmp4v2 ${ULTRASCHALL_EXT_PATH}/mp4v2/mp4v2-Win/bin/x64/${ULTRASCHALL_BUILD_TYPE})
    set(mp4v2_INCLUDE_DIRS ${ULTRASCHALL_EXT_PATH}/mp4v2/include)

    find_package(wxWidgets COMPONENTS core base REQUIRED)
    include("${wxWidgets_USE_FILE}")

    set(EXTRA_LIBRARIES "-framework AppKit")

    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "$ENV{HOME}/Library/Application\ Support/REAPER/UserPlugins")
endif()
