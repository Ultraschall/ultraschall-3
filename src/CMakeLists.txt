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

set(REAPER_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../include/reaper)

include_directories(
  ${LIBZ_INCLUDE_PATH}
  ${LIBCURL_INCLUDE_PATH}
  ${LIBTAG_INCLUDE_PATH}
  ${LIBMP4V2_INCLUDE_PATH}
  ${LIBJSON11_INCLUDE_PATH}
  ${LIBEXPAT_INCLUDE_PATH}
  ${LIBWDL_INCLUDE_PATH}
  ${REAPER_INCLUDE_PATH}
)

set(COMMON_INCLUDES
  Application.h
  BinaryStream.h
  Common.h
  CustomAction.h
  CustomActionFactory.h
  CustomActionManager.h
  FileManager.h
  ICommand.h
  ICustomAction.h
  ID3V2.h
  ID3V2Context.h
  ID3V2Writer.h
  InsertChapterMarkersAction.h
  InsertMediaPropertiesAction.h
  ISOBMFF.h
  ISOBMFFContext.h
  ISOBMFFWriter.h
  ITagWriter.h
  SharedObject.h
  Malloc.h
  Marker.h
  MediaProperties.h
  PictureUtilities.h
  ReaperProject.h
  ReaperProjectManager.h
  reaper_plugin_functions.h
  ReaperEntryPoints.h
  ReaperGateway.h
  resource.h
  SaveChapterMarkersAction.h
  SaveChapterMarkersToProjectAction.h
  ServiceStatus.h
  StringUtilities.h
  SystemProperties.h
  taglib_include.h
  TagWriterFactory.h
  UpdateCheck.h
  UIFileDialog.h
  UIMessage.h
  UIMessageClass.h
  UIMessageDialog.h
  UIMessageQueue.h
  UIMessageSupervisor.h
  UnicodeString.h
  VersionHandler.h
)

set(COMMON_SOURCES
  Application.cpp
  BinaryStream.cpp
  CustomAction.cpp
  CustomActionFactory.cpp
  CustomActionManager.cpp
  FileManager.cpp
  ID3V2.cpp
  ID3V2Context.cpp
  ID3V2Writer.cpp
  InsertChapterMarkersAction.cpp
  InsertMediaPropertiesAction.cpp
  ISOBMFF.cpp
  ISOBMFFContext.cpp
  ISOBMFFWriter.cpp
  MediaProperties.cpp
  PictureUtilities.cpp
  ReaperProject.cpp
  ReaperProjectManager.cpp
  ReaperEntryPoints.cpp
  ReaperGateway.cpp
  SaveChapterMarkersAction.cpp
  SaveChapterMarkersToProjectAction.cpp
  StringUtilities.cpp
  SystemProperties.cpp
  TagWriterFactory.cpp
  UpdateCheck.cpp
  UIFileDialog.cpp
  UIMessage.cpp
  UIMessageDialog.cpp
  UIMessageQueue.cpp
  UIMessageSupervisor.cpp
  UnicodeString.cpp
  VersionHandler.cpp
  reaper_ultraschall.cpp
)

if(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "win32")
  set(EXTERNAL_SOURCES
    ${LIBZ_SOURCE_PATH}/contrib/minizip/ioapi.c
    ${LIBZ_SOURCE_PATH}/contrib/minizip/unzip.c
  )
  set_source_files_properties(${LIBZ_SOURCE_PATH}/contrib/minizip/ioapi.c PROPERTIES GENERATED TRUE)
  set_source_files_properties(${LIBZ_SOURCE_PATH}/contrib/minizip/unzip.c PROPERTIES GENERATED TRUE)
elseif(${ULTRASCHALL_TARGET_SYSTEM} STREQUAL "macos")
  set(EXTERNAL_SOURCES
    ${LIBZ_SOURCE_PATH}/contrib/minizip/ioapi.c
    ${LIBZ_SOURCE_PATH}/contrib/minizip/unzip.c
  )
  set_source_files_properties(${LIBZ_SOURCE_PATH}/contrib/minizip/ioapi.c PROPERTIES GENERATED TRUE)
  set_source_files_properties(${LIBZ_SOURCE_PATH}/contrib/minizip/unzip.c PROPERTIES GENERATED TRUE)
endif()

include_directories(${CMAKE_CURRENT_LIST_DIR})

set(PLATFORM_INLUDES Platform.h)

if(WIN32)
  include_directories(win32)
  set(PLATFORM_SOURCES win32/Platform.cpp)
elseif(APPLE)
  include_directories(macos)
  set(PLATFORM_SOURCES macos/Platform.cpp)
elseif(UNIX)
  include_directories(linux)
  set(PLATFORM_SOURCES linux/Platform.cpp)
endif()

if(WIN32)
  set(EXTRA_SOURCES reaper_ultraschall.rc)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS)
elseif(APPLE)
  add_compile_options(-mmacosx-version-min=10.11)
  set_source_files_properties(
    FileManager.cpp
    VersionHandler.cpp
    PluginVersionCheck.cpp
    macos/Platform.cpp
    PROPERTIES COMPILE_FLAGS "-x objective-c++"
  )
endif()

source_group("Header Files" FILES
  ${COMMON_INCLUDES}
  ${PLATFORM_INCLUDES}
)
source_group("Source Files" FILES
  ${COMMON_SOURCES}
  ${PLATFORM_SOURCES}
  ${EXTRA_SOURCES}
)

source_group("External Files" FILES
  ${EXTERNAL_SOURCES}
)

message(STATUS "COMMON_INCLUDES   = ${COMMON_INCLUDES}")
message(STATUS "COMMON_SOURCES    = ${COMMON_SOURCES}")
message(STATUS "PLATFORM_INCLUDES = ${PLATFORM_INCLUDES}")
message(STATUS "PLATFORM_SOURCES  = ${PLATFORM_SOURCES}")
message(STATUS "EXTERNAL_SOURCES  = ${EXTERNAL_SOURCES}")
message(STATUS "EXTRA_SOURCES     = ${EXTRA_SOURCES}")

add_library(reaper_ultraschall SHARED
  ${COMMON_INCLUDES}
  ${COMMON_SOURCES}
  ${PLATFORM_INCLUDES}
  ${PLATFORM_SOURCES}
  ${EXTERNAL_SOURCES}
  ${EXTRA_SOURCES}
)

if(WIN32)
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
elseif(APPLE)
  set(EXTRA_LIBRARIES
    "-framework AppKit"
    "-framework Carbon"
    "-framework IOKit"
    "-framework Security")
endif()

add_dependencies(reaper_ultraschall zlib-build)
add_dependencies(reaper_ultraschall curl-build)
add_dependencies(reaper_ultraschall taglib-build)
add_dependencies(reaper_ultraschall mp4v2-build)
add_dependencies(reaper_ultraschall json11-build)
add_dependencies(reaper_ultraschall expat-build)
add_dependencies(reaper_ultraschall wdl-build)

target_link_libraries(reaper_ultraschall
  ${LIBZ_LIBRARY_PATH}
  ${LIBCURL_LIBRARY_PATH}
  ${LIBTAG_LIBRARY_PATH}
  ${LIBMP4V2_LIBRARY_PATH}
  ${LIBJSON11_LIBRARY_PATH}
  ${LIBEXPAT_LIBRARY_PATH}
  ${EXTRA_LIBRARIES}
)


set_target_properties(reaper_ultraschall PROPERTIES PREFIX "")
