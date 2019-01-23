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

# configure plugin build

set(COMMON_INCLUDES
    Application.h
    BasicMediaInformation.h
    BinaryFileReader.h
    ByteStream.h
    CustomActionFactory.h
    CustomActionManager.h
    FileManager.h
    Framework.h
    ICommand.h
    ICustomAction.h
    ImageTools.h
    InsertChapterMarkersAction.h
    InsertMediaPropertiesAction.h
    ITagWriter.h
    IUnknown.h
    Marker.h
    MessageDialog.h
    MP3_Interface.h
    MP3TagWriter.h
    MP4TagWriter.h
    Platform.h
    PluginVersionCheck.h
    Project.h
    ProjectManager.h
    reaper_plugin_functions.h
    ReaperEntryPoints.h
    ReaperVersionCheck.h
    resource.h
    SaveChapterMarkersAction.h
    SaveChapterMarkersToProjectAction.h
    ServiceStatus.h
    SoundboardVersionCheck.h
    StringUtilities.h
    SWSVersionCheck.h
    SystemProperties.h
    taglib_include.h
    TextFileReader.h
    TextFileWriter.h
    ThemeVersionCheck.h
    TimeUtilities.h
    UpdateCheck.h
    UIDialog.h
    UIFileDialog.h
    UIMessageDialog.h
    VersionHandler.h
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
    UIDialog.cpp
    UIFileDialog.cpp
    UIMessageDialog.cpp
    VersionHandler.cpp
    reaper_ultraschall.cpp
    ${LIBZ_LIBRARY_SOURCE_PATH}/contrib/minizip/ioapi.c
    ${LIBZ_LIBRARY_SOURCE_PATH}/contrib/minizip/unzip.c
)

set_source_files_properties(${LIBZ_LIBRARY_SOURCE_PATH}/contrib/minizip/ioapi.c PROPERTIES GENERATED TRUE)
set_source_files_properties(${LIBZ_LIBRARY_SOURCE_PATH}/contrib/minizip/unzip.c PROPERTIES GENERATED TRUE)

if(WIN32)
    set(EXTRA_SOURCES reaper_ultraschall.rc)
    add_definitions(-DULTRASCHALL_PLATFORM_WIN32 -D_CRT_SECURE_NO_WARNINGS)
elseif(APPLE)
    set(EXTRA_SOURCES NotificationPanel.mm)
    add_definitions(-DULTRASCHALL_PLATFORM_MACOS)
    add_compile_options(-mmacosx-version-min=10.11)
    set_source_files_properties(
        FileManager.cpp
        VersionHandler.cpp
        ReaperVersionCheck.cpp
        SoundboardVersionCheck.cpp
        PluginVersionCheck.cpp
        PROPERTIES COMPILE_FLAGS "-x objective-c++"
    )
elseif(UNIX)
    add_definitions(-DULTRASCHALL_PLATFORM_UNIX)
endif()

add_library(reaper_ultraschall SHARED ${COMMON_INCLUDES} ${COMMON_SOURCES} ${EXTRA_SOURCES})

add_dependencies(${PROJECT_NAME} zlib-build)
add_dependencies(${PROJECT_NAME} curl-build)
add_dependencies(${PROJECT_NAME} mp4v2-build)
add_dependencies(${PROJECT_NAME} taglib-build)
add_dependencies(${PROJECT_NAME} json11-build)
add_dependencies(${PROJECT_NAME} wxwidgets-build)

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
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG"$ENV{USERPROFILE}/AppData/Roaming/REAPER/UserPlugins")
elseif(APPLE)
    set(EXTRA_LIBRARIES "-framework AppKit")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "$ENV{HOME}/Library/Application\ Support/REAPER/UserPlugins")
elseif(UNIX)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "ENV{HOME}/.config/REAPER/UserPlugins")
endif()

if(CMAKE_BUILD_TYPE MATCHES "Debug")
    set(LIBZ_LIBRARY ${LIBZ_LIBRARY_DEBUG})
    set(LIBCURL_LIBRARY ${LIBCURL_LIBRARY_DEBUG})
    set(LIBMP4V2_LIBRARY ${LIBMP4V2_LIBRARY_DEBUG})
    set(LIBTAG_LIBRARY ${LIBTAG_LIBRARY_DEBUG})
    set(LIBJSON11_LIBRARY ${LIBJSON11_LIBRARY_DEBUG})
    set(LIBWXWIDGETS_LIBRARY ${LIBWXWIDGETS_LIBRARY_DEBUG})
else()
    set(LIBZ_LIBRARY ${LIBZ_LIBRARY_RELEASE})
    set(LIBCURL_LIBRARY ${LIBCURL_LIBRARY_RELEASE})
    set(LIBMP4V2_LIBRARY ${LIBMP4V2_LIBRARY_RELEASE})
    set(LIBTAG_LIBRARY ${LIBTAG_LIBRARY_RELEASE})
    set(LIBJSON11_LIBRARY ${LIBJSON11_LIBRARY_RELEASE})
    set(LIBWXWIDGETS_LIBRARY ${LIBWXWIDGETS_LIBRARY_RELEASE})
endif()

target_link_libraries(reaper_ultraschall
    ${LIBZ_LIBRARY}
    ${LIBCURL_LIBRARY}
    ${LIBMP4V2_LIBRARY}
    ${LIBTAG_LIBRARY}
    ${LIBJSON11_LIBRARY}
    ${LIBWXWIDGETS_LIBRARY}
    ${EXTRA_LIBRARIES}
)

set_target_properties(reaper_ultraschall PROPERTIES PREFIX "")

source_group("Header Files" ${COMMON_INCLUDES})
source_group("Source Files" ${COMMON_SOURCES} ${EXTRA_SOURCES})
