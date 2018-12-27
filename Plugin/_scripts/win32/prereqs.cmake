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

if(WIN32)
    find_library(zlib_LIBRARIES zlibstaticd ${ULTRASCHALL_EXT_PATH}/zlib/build/${CMAKE_BUILD_TYPE})
    set(zlib_INCLUDE_DIRS
        ${ULTRASCHALL_EXT_PATH}/zlib
        ${ULTRASCHALL_EXT_PATH}/zlib/contrib/minizip
        # FIXME configure zconf.h as GENERATED
        ${ULTRASCHALL_EXT_PATH}/zlib/build
    )

    find_library(curl_LIBRARIES libcurl-d ${ULTRASCHALL_EXT_PATH}/curl/build/lib/${CMAKE_BUILD_TYPE})
    set(curl_INCLUDE_DIRS
        ${ULTRASCHALL_EXT_PATH}/curl/include
    )

    find_library(taglib_LIBRARIES tag ${ULTRASCHALL_EXT_PATH}/taglib/build/taglib/${CMAKE_BUILD_TYPE})
    set(taglib_INCLUDE_DIRS
        ${ULTRASCHALL_EXT_PATH}/taglib/taglib
        ${ULTRASCHALL_EXT_PATH}/taglib/taglib/toolkit
        ${ULTRASCHALL_EXT_PATH}/taglib/taglib/mpeg
        ${ULTRASCHALL_EXT_PATH}/taglib/taglib/mpeg/id3v2
        ${ULTRASCHALL_EXT_PATH}/taglib/taglib/mpeg/id3v2/frames
        ${ULTRASCHALL_EXT_PATH}/taglib/taglib/bindings/c
        # FIXME configure taglib_config.h as GENERATED
        ${ULTRASCHALL_EXT_PATH}/taglib/build
    )

    find_library(mp4v2_LIBRARIES libmp4v2 ${ULTRASCHALL_EXT_PATH}/mp4v2/mp4v2-Win/bin/x64/${CMAKE_BUILD_TYPE})
    set(mp4v2_INCLUDE_DIRS ${ULTRASCHALL_EXT_PATH}/mp4v2/include)

    find_library(wxWidgets_CORE_LIBRARY wxmsw31ud_core ${ULTRASCHALL_EXT_PATH}/wxwidgets/lib/vc_lib)
    find_library(wxWidgets_BASE_LIBRARY wxbase31ud ${ULTRASCHALL_EXT_PATH}/wxwidgets/lib/vc_lib)
    set(wxwidgets_LIBRARIES ${wxWidgets_CORE_LIBRARY} ${wxWidgets_BASE_LIBRARY})
    set(wxWidgest_INCLUDE_DIRS ${ULTRASCHALL_EXT_PATH}/wxwidgets/include)

    set(EXTRA_LIBRARIES
        version.lib
        ws2_32.lib
        crypt32.lib
        wldap32.lib
        mfplat.lib
        mf.lib
        mfuuid.lib
        shlwapi.lib
        comctl32.lib
        comdlg32.lib
        rpcrt4.lib
    )

    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG"$ENV{USERPROFILE}/AppData/Roaming/REAPER/UserPlugins")
endif()
