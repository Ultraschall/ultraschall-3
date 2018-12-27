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

set(ultraschall_INCLUDE_DIRS ${ULTRASCHALL_SRC_PATH})
set(reaper_INCLUDE_DIRS ${ULTRASCHALL_EXT_PATH}/reaper_extension_sdk/jmde)

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
    ${ULTRASCHALL_EXT_PATH}/zlib/contrib/minizip/ioapi.c
    ${ULTRASCHALL_EXT_PATH}/zlib/contrib/minizip/unzip.c
)

if(WIN32)
    set(EXTRA_SOURCES reaper_ultraschall.rc)
    add_definitions(-DULTRASCHALL_PLATFORM_WIN32 -D_CRT_SECURE_NO_WARNINGS)
elseif(APPLE)
    set(EXTRA_SOURCES NotificationPanel.mm)
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
elseif(UNIX)
    add_definitions(-DULTRASCHALL_PLATFORM_UNIX)
endif()

add_library(reaper_ultraschall SHARED ${COMMON_SOURCES} ${EXTRA_SOURCES})

set(COMMON_LIBRARIES
    ${zlib_LIBRARIES}
    ${curl_LIBRARIES}
    ${wxwidgets_LIBRARIES}
    ${taglib_LIBRARIES}
    ${mp4v2_LIBRARIES}
)

message(STATUS "COMMON_LIBRARIES = ${COMMON_LIBRARIES}")

target_link_libraries(reaper_ultraschall ${COMMON_LIBRARIES} ${EXTRA_LIBRARIES})

set_target_properties(reaper_ultraschall PROPERTIES PREFIX "")
