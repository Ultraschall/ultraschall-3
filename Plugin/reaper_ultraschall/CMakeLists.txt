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
    find_library(zlib_LIBRARIES libz
        "../3rd_party/zlib/lib/win32/debug"
    )
    find_library(curl_LIBRARIES libcurl
        "../3rd_party/curl/lib/win32/debug"
    )
    find_library(mp4v2_LIBRARIES libmp4v2
        "../3rd_party/mp4v2/lib/win32/debug"
    )
    find_library(taglib_LIBRARIES libtag
        "../3rd_party/taglib/lib/win32/debug"
    )
    find_library(wxWidgets_LIBRARIES libwxwidgets
        "../3rd_party/wxwidgets/lib/win32/debug"
    )
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG
        "$ENV{USERPROFILE}/AppData/Roaming/REAPER/UserPlugins"
    )
elseif(APPLE)
    find_package(zlib)
    find_package(curl)

    find_package(wxWidgets COMPONENTS core base REQUIRED)
    include("${wxWidgets_USE_FILE}")

    if(CMAKE_BUILD_TYPE MATCHES DEBUG)
        set(mp4v2_LIBRARY_PATH
            "../3rd_party/mp4v2/lib/macos/debug"
        )
        set(taglib_LIBRARY_PATH
            "../3rd_party/taglib/lib/macos/debug"
        )
    else()
        set(mp4v2_LIBRARY_PATH
            "../3rd_party/mp4v2/lib/macos/release"
        )
        set(taglib_LIBRARY_PATH
            "../3rd_party/taglib/lib/macos/release"
        )
    endif()

    find_library(mp4v2_LIBRARIES mp4v2
        ${mp4v2_LIBRARY_PATH}
    )
    find_library(taglib_LIBRARIES tag
        ${taglib_LIBRARY_PATH}
    )
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG
        "$ENV{HOME}/Library/Application\ Support/REAPER/UserPlugins"
    )
elseif(UNIX)
    find_package(zlib)
    find_package(curl)

    find_package(wxWidgets COMPONENTS core base REQUIRED)
    include("${wxWidgets_USE_FILE}")

    find_library(mp4v2_LIBRARIES mp4v2
        "../3rd_party/mp4v2/lib/linux"
    )
    find_library(taglib_LIBRARIES tag
        "../3rd_party/taglib/lib/linux"
    )
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG
        "$ENV{HOME}/.config/REAPER/UserPlugins"
    )
endif()

set(ultraschall_INCLUDE_DIRS
    ./
)
set(reaper_INCLUDE_DIRS
    ../reaper_extension_sdk/jmde
)
set(mp4v2_INCLUDE_DIRS
    ../3rd_party/mp4v2/include
)
set(taglib_INCLUDE_DIRS
    ../3rd_party/taglib/include
    ../3rd_party/taglib/include/toolkit
    ../3rd_party/taglib/include/mpeg
    ../3rd_party/taglib/include/mpeg/id3v2
    ../3rd_party/taglib/include/mpeg/id3v2/frames
    ../3rd_party/taglib/include/bindings/c
)

if(WIN32)
    set(zlib_INCLUDE_DIRS
        ../3rd_party/zlib/include
    )
    set(curl_INCLUDE_DIRS
        ../3rd_party/curl/include
    )
    set(wxWidgest_INCLUDE_DIRS
        ../3rd_party/wxwidgets/include
    )
endif()

include_directories(
    ${ultraschall_INCLUDE_DIRS}
    ${reaper_INCLUDE_DIRS}
    ${mp4v2_INCLUDE_DIRS}
    ${taglib_INCLUDE_DIRS}
    ${zlib_INCLUDE_DIRS}
    ${curl_INCLUDE_DIRS}
    ${wxWidgest_INCLUDE_DIRS}
)

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
    add_definitions(
        -DULTRASCHALL_PLATFORM_WIN32
        -D_CRT_SECURE_NO_WARNINGS
    )
elseif(APPLE)
    set(EXTRA_SOURCES
        NotificationPanel.mm
    )
    add_definitions(
        -DULTRASCHALL_PLATFORM_MACOS
    )
    add_compile_options(
        -mmacosx-version-min=10.11
    )
    set_source_files_properties(
        FileManager.cpp
        NotificationWindow.cpp
        VersionHandler.cpp
        ReaperVersionCheck.cpp
        SoundboardVersionCheck.cpp
        PluginVersionCheck.cpp
        PROPERTIES COMPILE_FLAGS "-x objective-c++"
    )
elseif(UNIX)
    add_definitions(
        -DULTRASCHALL_PLATFORM_UNIX
    )
endif()

add_library(reaper_ultraschall SHARED
    ${COMMON_SOURCES}
    ${EXTRA_SOURCES}
)

set(COMMON_LIBRARIES
    ${zlib_LIBRARIES}
    ${curl_LIBRARIES}
    ${wxwidgets_LIBRARIES}
    ${taglib_LIBRARIES}
    ${mp4v2_LIBRARIES}
)

if(WIN32)
    set(WIN32_LIBRARIES
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
    target_link_libraries(reaper_ultraschall
        ${COMMON_LIBRARIES}
        ${WIN32_LIBRARIES}
    )
elseif(APPLE)
    target_link_libraries(reaper_ultraschall
        "-framework AppKit"
        ${COMMON_LIBRARIES}
    )
elseif(UNIX)
    target_link_libraries(reaper_ultraschall
        ${COMMON_LIBRARIES}
    )
endif()

set_target_properties(reaper_ultraschall PROPERTIES PREFIX "")
