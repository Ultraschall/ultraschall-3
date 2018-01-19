cmake_minimum_required(VERSION 3.0.0)
project(reaper_ultraschall VERSION 3.1.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
  framework
  ../reaper_extension_sdk/jmde
  ../3rd_party/zlib/include
  ../3rd_party/taglib/include
  ../3rd_party/taglib/include/toolkit
  ../3rd_party/taglib/include/mpeg
  ../3rd_party/taglib/include/mpeg/id3v2
  ../3rd_party/taglib/include/mpeg/id3v2/frames
  ../3rd_party/taglib/include/bindings/c
  ../3rd_party/mp4v2/include
)

if(WIN32)
  include_directories(../3rd_party/curl/include)
endif()

set(SOURCES
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
  MP3_Interface.cpp
  MP4TagWriter.cpp
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
  set(ADDITIONAL_SOURCES reaper_ultraschall.rc)
elseif(APPLE)
  set(ADDITIONAL_SOURCES NotificationPanel.mm)
endif()

add_library(reaper_ultraschall SHARED ${SOURCES} ${ADDITIONAL_SOURCES})

if(WIN32)
  add_definitions(-DULTRASCHALL_PLATFORM_WIN32)
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
    debug ${Z_LIB_DEBUG}     optimized ${Z_LIB_RELEASE}
    debug ${CURL_LIB_DEBUG}  optimized ${CURL_LIB_RELEASE}
    debug ${MP4V2_LIB_DEBUG} optimized ${MP4V2_LIB_RELEASE}
    debug ${TAG_LIB_DEBUG}   optimized ${TAG_LIB_RELEASE}
    version.lib ws2_32.lib crypt32.lib wldap32.lib
)
else()
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
    debug ${MP4V2_LIB_DEBUG} optimized ${MP4V2_LIB_RELEASE}
    debug ${TAG_LIB_DEBUG}   optimized ${TAG_LIB_RELEASE}
  )
endif()

#set_target_properties(reaper_ultraschall PROPERTIES PREFIX "")
set_target_properties(reaper_ultraschall PROPERTIES VERSION ${PROJECT_VERSION})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
