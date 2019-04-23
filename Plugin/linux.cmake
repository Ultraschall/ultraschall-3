
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "$ENV{HOME}/.config/REAPER/UserPlugins")

include(ExternalProject)

# configure zlib

set(CURRENT_EXTERNAL_PROJECT zlib)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring ...")

find_package(ZLIB)
if(ZLIB_FOUND)
	message(STATUS "Found zlib version " ${ZLIB_VERSION_STRING})

	find_package(PkgConfig)
	pkg_check_modules(UNZIP minizip)
        find_library(minizip_LIBRARY minizip)
	set(LIBZ_INCLUDE_PATH ${ZLIB_INCLUDE_DIRS} ${UNZIP_INCLUDEDIR})
	set(LIBZ_LIBRARY_PATH ${ZLIB_LIBRARIES} ${minizip_LIBRARY})
endif()

message(STATUS "LIBZ_INCLUDE_PATH = ${LIBZ_INCLUDE_PATH}")
message(STATUS "LIBZ_LIBRARY_PATH = ${LIBZ_LIBRARY_PATH}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure curl

set(CURRENT_EXTERNAL_PROJECT curl)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring ...")

find_package(CURL)
if(CURL_FOUND)
	message(STATUS "Found curl version " ${CURL_VERSION_STRING})
	set(LIBCURL_INCLUDE_PATH ${CURL_INCLUDE_DIRS})
	set(LIBCURL_LIBRARY_PATH ${CURL_LIBRARIES})
endif()

message(STATUS "LIBCURL_INCLUDE_PATH = ${LIBCURL_INCLUDE_PATH}")
message(STATUS "LIBCURL_LIBRARY_PATH = ${LIBCURL_LIBRARY_PATH}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure taglib

set(CURRENT_EXTERNAL_PROJECT taglib)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring ...")

find_package(PkgConfig)
pkg_check_modules(LIBTAG taglib)
find_library(taglib_LIBRARY tag)
set(LIBTAG_INCLUDE_PATH ${LIBTAG_INCLUDEDIR})
set(LIBTAG_LIBRARY_PATH ${taglib_LIBRARY})

message(STATUS "LIBTAG_INCLUDE_PATH = ${LIBTAG_INCLUDE_PATH}")
message(STATUS "LIBTAG_LIBRARY_PATH = ${LIBTAG_LIBRARY_PATH}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure mp4v2

set(CURRENT_EXTERNAL_PROJECT mp4v2)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring...")

find_package(PkgConfig)
find_library(mp4v2_LIBRARY mp4v2)
set(LIBMP4V2_INCLUDE_PATH /usr/include)
set(LIBMP4V2_LIBRARY_PATH ${mp4v2_LIBRARY})

message(STATUS "LIBMP4V2_INCLUDE_PATH = ${LIBMP4V2_INCLUDE_PATH}")
message(STATUS "LIBMP4V2_LIBRARY_PATH = ${LIBMP4V2_LIBRARY_PATH}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure wxwidgets

set(CURRENT_EXTERNAL_PROJECT wxwidgets)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring ...")

set(wxWidgets_CONFIG_EXECUTABLE wx-config-gtk3)
#set(wxWidgets_CONFIG_OPTIONS --toolkit=core --toolkit=base --prefix=/usr)
find_package(wxWidgets REQUIRED core base)
if(wxWidgets_FOUND)
	include(${wxWidgets_USE_FILE})
	message(STATUS "Found wxwidgets version " ${wxWidgets_VERSION_STRING})
	set(LIBWXWIDGETS_INCLUDE_PATH ${wxWidgets_INCLUDE_DIRS})
	set(LIBWXWIDGETS_LIBRARY_PATH ${wxWidgets_LIBRARIES})
endif()

message(STATUS "LIBWXWIDGETS_INCLUDE_PATH = ${LIBWXWIDGETS_INCLUDE_PATH}")
message(STATUS "LIBWXWIDGETS_LIBRARY_PATH = ${LIBWXWIDGETS_LIBRARY_PATH}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

add_definitions(-D__WXGTK3__ -D__WXGTK__)

