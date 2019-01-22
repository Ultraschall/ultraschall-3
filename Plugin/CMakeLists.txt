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

if(WIN32)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "$ENV{USERPROFILE}/AppData/Roaming/REAPER/UserPlugins")
elseif(APPLE)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "$ENV{HOME}/Library/Application\ Support/REAPER/UserPlugins")
elseif(UNIX)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "$ENV{HOME}/.config/REAPER/UserPlugins")
endif()

include(ExternalProject)

# configure zlib

set(CURRENT_EXTERNAL_PROJECT zlib)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring ...")

ExternalProject_Add(zlib
    PREFIX libz
	GIT_REPOSITORY https://github.com/madler/zlib.git
    GIT_TAG v1.2.11
    STEP_TARGETS build
    EXCLUDE_FROM_ALL TRUE
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF
)

ExternalProject_Get_Property(zlib SOURCE_DIR)
ExternalProject_Get_Property(zlib BINARY_DIR)

set(LIBZ_INCLUDE_PATH
    ${BINARY_DIR}
    ${SOURCE_DIR}
    ${SOURCE_DIR}/contrib/minizip
)

set(LIBZ_LIBRARY_DEBUG       ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/zlibstaticd.lib)
set(LIBZ_LIBRARY_RELEASE     ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/zlibstatic.lib)
set(LIBZ_LIBRARY_SOURCE_PATH ${SOURCE_DIR})

message(STATUS "LIBZ_INCLUDE_PATH        = ${LIBZ_INCLUDE_PATH}")
message(STATUS "LIBZ_LIBRARY_DEBUG       = ${LIBZ_LIBRARY_DEBUG}")
message(STATUS "LIBZ_LIBRARY_RELEASE     = ${LIBZ_LIBRARY_RELEASE}")
message(STATUS "LIBZ_LIBRARY_SOURCE_PATH = ${LIBZ_LIBRARY_SOURCE_PATH}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure curl

set(CURRENT_EXTERNAL_PROJECT curl)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring ...")

ExternalProject_Add(curl
    PREFIX libcurl
	GIT_REPOSITORY https://github.com/curl/curl.git
	GIT_TAG curl-7_63_0
    STEP_TARGETS build
    EXCLUDE_FROM_ALL TRUE
	CMAKE_ARGS -DBUILD_CURL_EXE=OFF -DBUILD_SHARED_LIBS=OFF -DHTTP_ONLY=ON -DENABLE_IPV6=ON -DBUILD_TESTING=OFF
)

ExternalProject_Get_Property(curl SOURCE_DIR)
ExternalProject_Get_Property(curl BINARY_DIR)

set(LIBCURL_INCLUDE_PATH ${SOURCE_DIR}/include)

set(LIBCURL_LIBRARY_DEBUG   ${BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/libcurl-d.lib)
set(LIBCURL_LIBRARY_RELEASE ${BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/libcurl.lib)

message(STATUS "LIBCURL_INCLUDE_PATH    = ${LIBCURL_INCLUDE_PATH}")
message(STATUS "LIBCURL_LIBRARY_DEBUG   = ${LIBCURL_LIBRARY_DEBUG}")
message(STATUS "LIBCURL_LIBRARY_RELEASE = ${LIBCURL_LIBRARY_RELEASE}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure mp4v2

set(CURRENT_EXTERNAL_PROJECT mp4v2)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring ...")

include(ExternalProject)
ExternalProject_Add(mp4v2
    PREFIX libmp4v2
	GIT_REPOSITORY https://github.com/Ultraschall/mp4v2.git
	GIT_TAG v4.0.0-prerelease1
    STEP_TARGETS build
    EXCLUDE_FROM_ALL TRUE
	CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DMP4V2_EXPORTS=0 -DMP4V2_NO_STDINT_DEFS=1
)

ExternalProject_Get_Property(mp4v2 SOURCE_DIR)
ExternalProject_Get_Property(mp4v2 BINARY_DIR)

set(LIBMP4V2_INCLUDE_PATH ${SOURCE_DIR}/include)

set(LIBMP4V2_LIBRARY_DEBUG   ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/mp4v2.lib)
set(LIBMP4V2_LIBRARY_RELEASE ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/mp4v2.lib)

message(STATUS "LIBMP4V2_INCLUDE_PATH    = ${LIBMP4V2_INCLUDE_PATH}")
message(STATUS "LIBMP4V2_LIBRARY_DEBUG   = ${LIBMP4V2_LIBRARY_DEBUG}")
message(STATUS "LIBMP4V2_LIBRARY_RELEASE = ${LIBMP4V2_LIBRARY_RELEASE}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure taglib

set(CURRENT_EXTERNAL_PROJECT taglib)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring ...")

include(ExternalProject)
ExternalProject_Add(taglib
    PREFIX libtag
	GIT_REPOSITORY https://github.com/taglib/taglib.git
	GIT_TAG v1.11.1
    STEP_TARGETS build
    EXCLUDE_FROM_ALL TRUE
	CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DBUILD_TESTS=OFF -DBUILD_EXAMPLES=OFF -DBUILD_BINDINGS=OFF
)

ExternalProject_Get_Property(taglib SOURCE_DIR)
ExternalProject_Get_Property(taglib BINARY_DIR)

set(LIBTAG_INCLUDE_PATH
    ${BINARY_DIR} # taglib_config.h
    ${SOURCE_DIR}/taglib
    ${SOURCE_DIR}/taglib/toolkit
    ${SOURCE_DIR}/taglib/mpeg
    ${SOURCE_DIR}/taglib/mpeg/id3v2
    ${SOURCE_DIR}/taglib/mpeg/id3v2/frames
)

set(LIBTAG_LIBRARY_DEBUG   ${BINARY_DIR}/taglib/${CMAKE_BUILD_TYPE}/tag.lib)
set(LIBTAG_LIBRARY_RELEASE ${BINARY_DIR}/taglib/${CMAKE_BUILD_TYPE}/tag.lib)

message(STATUS "LIBTAG_INCLUDE_PATH    = ${LIBTAG_INCLUDE_PATH}")
message(STATUS "LIBTAG_LIBRARY_DEBUG   = ${LIBTAG_LIBRARY_DEBUG}")
message(STATUS "LIBTAG_LIBRARY_RELEASE = ${LIBTAG_LIBRARY_RELEASE}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure json11

set(CURRENT_EXTERNAL_PROJECT json11)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring ...")

ExternalProject_Add(json11
    PREFIX libjson11
	GIT_REPOSITORY https://github.com/dropbox/json11.git
    GIT_TAG v1.0.0
    STEP_TARGETS build
    EXCLUDE_FROM_ALL TRUE
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF
)

ExternalProject_Get_Property(json11 SOURCE_DIR)
ExternalProject_Get_Property(json11 BINARY_DIR)

set(LIBJSON11_INCLUDE_PATH ${SOURCE_DIR})

set(LIBJSON11_LIBRARY_DEBUG   ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/json11.lib)
set(LIBJSON11_LIBRARY_RELEASE ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/json11.lib)

message(STATUS "LIBJSON11_INCLUDE_PATH    = ${LIBJSON11_INCLUDE_PATH}")
message(STATUS "LIBJSON11_LIBRARY_DEBUG   = ${LIBJSON11_LIBRARY_DEBUG}")
message(STATUS "LIBJSON11_LIBRARY_RELEASE = ${LIBJSON11_LIBRARY_RELEASE}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure wxwidgets

set(CURRENT_EXTERNAL_PROJECT wxwidgets)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring ...")

ExternalProject_Add(wxwidgets
    PREFIX libwxwidgets
	GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG v3.1.2
    STEP_TARGETS build
    EXCLUDE_FROM_ALL TRUE
    CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DwxBUILD_SAMPLES=OFF -DwxBUILD_TESTS=OFF -DwxBUILD_DEMOS=OFF -DwxBUILD_INSTALL=OFF -DwxBUILD_MSVC_MULTIPROC=ON -DwxUSE_STL=ON -DwxUSE_STD_CONTAINERS=ON
)

ExternalProject_Get_Property(wxwidgets SOURCE_DIR)
ExternalProject_Get_Property(wxwidgets BINARY_DIR)

set(LIBWXWIDGETS_INCLUDE_PATH ${SOURCE_DIR}/include)

set(LIBWXWIDGETS_LIBRARY_DEBUG
    ${BINARY_DIR}/lib/vc_x64_lib/wxbase31ud.lib
    ${BINARY_DIR}/lib/vc_x64_lib/wxmsw31ud_core.lib
)
set(LIBWXWIDGETS_LIBRARY_RELEASE
    ${BINARY_DIR}/lib/vc_x64_lib/wxbase31u.lib
    ${BINARY_DIR}/lib/vc_x64_lib/wxmsw31u_core.lib
)

message(STATUS "LIBWXWIDGETS_INCLUDE_PATH    = ${LIBWXWIDGETS_INCLUDE_PATH}")
message(STATUS "LIBWXWIDGETS_LIBRARY_DEBUG   = ${LIBWXWIDGETS_LIBRARY_DEBUG}")
message(STATUS "LIBWXWIDGETS_LIBRARY_RELEASE = ${LIBWXWIDGETS_LIBRARY_RELEASE}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

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

set(ULTRASCHALL_PATH ${CMAKE_SOURCE_DIR})
set(ULTRASCHALL_EXT_PATH ${ULTRASCHALL_PATH}/_ext)
set(ULTRASCHALL_SRC_PATH ${ULTRASCHALL_PATH}/reaper_ultraschall)

add_subdirectory(reaper_ultraschall)
