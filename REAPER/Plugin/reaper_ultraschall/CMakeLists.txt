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
  framework/BinaryFileReader.cpp
  framework/StringUtilities.cpp
  framework/TextFileReader.cpp
  framework/TextFileWriter.cpp
  framework/TimeUtilities.cpp
  reaper/Application.cpp
  reaper/BasicMediaInformation.cpp
  reaper/CustomActionFactory.cpp
  reaper/CustomActionManager.cpp
  reaper/FileManager.cpp
  reaper/ImageTools.cpp
  reaper/InsertChapterMarkersAction.cpp
  reaper/InsertMediaPropertiesAction.cpp
  reaper/MP3TagWriter.cpp
  reaper/MP3_Interface.cpp
  reaper/MP4TagWriter.cpp
  reaper/NotificationPanel.mm
  reaper/NotificationWindow.cpp
  reaper/PluginVersionCheck.cpp
  reaper/Project.cpp
  reaper/ProjectManager.cpp
  reaper/ReaperEntryPoints.cpp
  reaper/ReaperVersionCheck.cpp
  reaper/SWSVersionCheck.cpp
  reaper/SaveChapterMarkersAction.cpp
  reaper/SaveChapterMarkersToProjectAction.cpp
  reaper/SoundboardVersionCheck.cpp
  reaper/SystemProperties.cpp
  reaper/ThemeVersionCheck.cpp
  reaper/UpdateCheck.cpp
  reaper/VersionHandler.cpp
  reaper/reaper_ultraschall.cpp
  ../3rd_party/zlib/src/ioapi.c
  ../3rd_party/zlib/src/unzip.c
)

if(WIN32)
  set(ADDITIONAL_SOURCES reaper_ultraschall.rc)
elseif(APPLE)
  set(ADDITIONAL_SOURCES reaper/NotificationPanel.mm)
endif()

add_library(reaper_ultraschall SHARED ${SOURCES} ${ADDITIONAL_SOURCES})

if(WIN32)
  add_definitions(-DULTRASCHALL_PLATFORM_WIN32)
elseif(APPLE)

  add_definitions(-DULTRASCHALL_PLATFORM_MACOS)
  add_compile_options(-mmacosx-version-min=10.11)

  set_source_files_properties(
    reaper/FileManager.cpp
    reaper/NotificationWindow.cpp
    reaper/VersionHandler.cpp
    reaper/ReaperVersionCheck.cpp
    reaper/SoundboardVersionCheck.cpp
    reaper/PluginVersionCheck.cpp
    PROPERTIES COMPILE_FLAGS "-x objective-c++"
  )
endif()

if(WIN32)
  find_library(Z_LIB_DEBUG z-static-x64-debug "../3rd_party/zlib/lib/win32/debug")
  find_library(Z_LIB_RELEASE z-static-x64-debug "../3rd_party/zlib/lib/win32/release")

  find_library(CURL_LIB_DEBUG curl-static-x64-debug "../3rd_party/curl/lib/win32/debug")
  find_library(CURL_LIB_RELEASE curl-static-x64-debug "../3rd_party/curl/lib/win32/release")

  find_library(MP4V2_LIB_DEBUG libmp4v2 "../3rd_party/mp4v2/lib/win32/debug")
  find_library(MP4V2_LIB_RELEASE libmp4v2 "../3rd_party/mp4v2/lib/win32/release")

  find_library(TAG_LIB_DEBUG tag-static-x64-debug "../3rd_party/taglib/lib/win32/debug")
  find_library(TAG_LIB_RELEASE tag-static-x64-debug "../3rd_party/taglib/lib/win32/release")

  target_link_libraries(reaper_ultraschall
    debug ${Z_LIB_DEBUG}     optimized ${Z_LIB_RELEASe}
    debug ${CURL_LIB_DEBUG}  optimized ${CURL_LIB_RELEASE}
    debug ${MP4V2_LIB_DEBUG} optimized ${MP4V2_LIB_RELEASE}
    debug ${TAG_LIB_DEBUG}   optimized ${TAG_LIB_RELEASE}
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

  find_library(TAG_LIB_DEBUG tag-static-x64-debug "../3rd_party/taglib/lib/macos/debug")
  find_library(TAG_LIB_RELEASE tag-static-x64-release "../3rd_party/taglib/lib/macos/release")

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
