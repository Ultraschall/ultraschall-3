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
project(reaper_ultraschall VERSION 3.1.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "$ENV{USERPROFILE}/AppData/Roaming/REAPER/UserPlugins")
elseif(APPLE)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "$ENV{HOME}/Library/Application\ Support/REAPER/UserPlugins")
endif()

set(COMMON_INCLUDES
  framework
  ../reaper_extension_sdk/jmde
  ../3rd_party/taglib/include
  ../3rd_party/taglib/include/toolkit
  ../3rd_party/taglib/include/mpeg
  ../3rd_party/taglib/include/mpeg/id3v2
  ../3rd_party/taglib/include/mpeg/id3v2/frames
  ../3rd_party/taglib/include/bindings/c
  ../3rd_party/mp4v2/include
)

if(WIN32)
  set(EXTRA_INCLUDES ${EXTRA_INCLUDES}
    ../3rd_party/zlib/include
    ../3rd_party/curl/include
    )
elseif(APPLE)
  set(EXTRA_INCLUDES
    ../3rd_party/zlib/include
  )
endif()

include_directories(${COMMON_INCLUDES} ${EXTRA_INCLUDES})

set(COMMON_SOURCES
  BinaryFileReader.cpp
  StringUtilities.cpp
  TextFileReader.cpp
  TextFileWriter.cpp
  TimeUtilities.cpp
  Application.cpp
  BasicMediaInformation.cpp
  CustomActionFactory.cpp
  CustomActionManager.cpp
  FileManager.cpp
  ImageTools.cpp
  InsertChapterMarkersAction.cpp
  InsertMediaPropertiesAction.cpp
  MP3TagWriter.cpp
  MP4TagWriter.cpp
  MP3_Interface.cpp
  NotificationWindow.cpp
  PluginVersionCheck.cpp
  Project.cpp
  ProjectManager.cpp
  ReaperEntryPoints.cpp
  ReaperVersionCheck.cpp
  SWSVersionCheck.cpp
  SaveChapterMarkersAction.cpp
  SaveChapterMarkersToProjectAction.cpp
  SoundboardVersionCheck.cpp
  SystemProperties.cpp
  ThemeVersionCheck.cpp
  UpdateCheck.cpp
  VersionHandler.cpp
  reaper_ultraschall.cpp
  ../3rd_party/zlib/src/ioapi.c
  ../3rd_party/zlib/src/unzip.c
)

if(WIN32)
  set(EXTRA_SOURCES
    reaper_ultraschall.rc
  )
elseif(APPLE)
  set(EXTRA_SOURCES NotificationPanel.mm)
endif()

add_library(reaper_ultraschall SHARED ${COMMON_SOURCES} ${EXTRA_SOURCES})

set_target_properties(reaper_ultraschall PROPERTIES PREFIX "")

if(WIN32)
  add_definitions(-DULTRASCHALL_PLATFORM_WIN32 -D_CRT_SECURE_NO_WARNINGS)
elseif(APPLE)
  add_definitions(-DULTRASCHALL_PLATFORM_MACOS)
  add_compile_options(-mmacosx-version-min=10.11)

  set_source_files_properties(
    FileManager.cpp
    NotificationWindow.cpp
    VersionHandler.cpp
    ReaperVersionCheck.cpp
    SoundboardVersionCheck.cpp
    PluginVersionCheck.cpp
    PROPERTIES COMPILE_FLAGS "-x objective-c++"
  )
endif()

if(WIN32)
  find_library(Z_LIB_DEBUG libz-static-x64-debug "../3rd_party/zlib/lib/win32/debug")
  find_library(Z_LIB_RELEASE libz-static-x64-release "../3rd_party/zlib/lib/win32/release")

  find_library(CURL_LIB_DEBUG libcurl-static-x64-debug "../3rd_party/curl/lib/win32/debug")
  find_library(CURL_LIB_RELEASE libcurl-static-x64-release "../3rd_party/curl/lib/win32/release")

  find_library(MP4V2_LIB_DEBUG libmp4v2 "../3rd_party/mp4v2/lib/win32/debug")
  find_library(MP4V2_LIB_RELEASE libmp4v2 "../3rd_party/mp4v2/lib/win32/release")

  find_library(TAG_LIB_DEBUG libtag-static-x64-debug "../3rd_party/taglib/lib/win32/debug")
  find_library(TAG_LIB_RELEASE libtag-static-x64-release "../3rd_party/taglib/lib/win32/release")

  target_link_libraries(reaper_ultraschall
    debug ${Z_LIB_DEBUG}      optimized ${Z_LIB_RELEASE}
    debug ${CURL_LIB_DEBUG}   optimized ${CURL_LIB_RELEASE}
    debug ${MP4V2_LIB_DEBUG}  optimized ${MP4V2_LIB_RELEASE}
    debug ${TAG_LIB_DEBUG}    optimized ${TAG_LIB_RELEASE}
    debug ${WXBASE_LIB_DEBUG} optimized ${WXBASE_LIB_RELEASE}
    debug ${WXCORE_LIB_DEBUG} optimized ${WXCORE_LIB_RELEASE}
    debug ${WXPNG_LIB_DEBUG} optimized ${WXPNG_LIB_RELEASE}
    debug ${WXZLIB_LIB_DEBUG} optimized ${WXZLIB_LIB_RELEASE}
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
elseif(APPLE)
  target_link_libraries(reaper_ultraschall "-framework AppKit")

  find_package(zlib)
  if(ZLIB_FOUND)
    target_link_libraries(reaper_ultraschall ${ZLIB_LIBRARIES})
  endif()

  find_package(curl)
  if(CURL_FOUND)
    target_link_libraries(reaper_ultraschall ${CURL_LIBRARIES})
  endif()

  find_library(MP4V2_LIB_DEBUG mp4v2 "../3rd_party/mp4v2/lib/macos/debug")
  find_library(MP4V2_LIB_RELEASE mp4v2 "../3rd_party/mp4v2/lib/macos/release")

  find_library(TAG_LIB_DEBUG tag "../3rd_party/taglib/lib/macos/debug")
  find_library(TAG_LIB_RELEASE tag "../3rd_party/taglib/lib/macos/release")

  target_link_libraries(reaper_ultraschall
    debug ${MP4V2_LIB_DEBUG}  optimized ${MP4V2_LIB_RELEASE}
    debug ${TAG_LIB_DEBUG}    optimized ${TAG_LIB_RELEASE}
  )
endif()
