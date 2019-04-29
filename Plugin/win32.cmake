
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "$ENV{USERPROFILE}/AppData/Roaming/REAPER/UserPlugins")

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

set(LIBZ_INCLUDE_PATH ${BINARY_DIR} ${SOURCE_DIR} ${SOURCE_DIR}/contrib/minizip)
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(LIBZ_LIBRARY_PATH ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/zlibstaticd.lib)
else()
    set(LIBZ_LIBRARY_PATH ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/zlibstatic.lib)
endif()

set(LIBZ_SOURCE_PATH ${SOURCE_DIR})

message(STATUS "LIBZ_INCLUDE_PATH = ${LIBZ_INCLUDE_PATH}")
message(STATUS "LIBZ_LIBRARY_PATH = ${LIBZ_LIBRARY_PATH}")
message(STATUS "LIBZ_SOURCE_PATH  = ${LIBZ_SOURCE_PATH}")

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
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(LIBCURL_LIBRARY_PATH ${BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/libcurl-d.lib)
else()
    set(LIBCURL_LIBRARY_PATH ${BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/libcurl.lib)
endif()

message(STATUS "LIBCURL_INCLUDE_PATH = ${LIBCURL_INCLUDE_PATH}")
message(STATUS "LIBCURL_LIBRARY_PATH = ${LIBCURL_LIBRARY_PATH}")

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
set(LIBMP4V2_LIBRARY_PATH ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/mp4v2.lib)

message(STATUS "LIBMP4V2_INCLUDE_PATH = ${LIBMP4V2_INCLUDE_PATH}")
message(STATUS "LIBMP4V2_LIBRARY_PATH = ${LIBMP4V2_LIBRARY_PATH}")

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

set(LIBTAG_LIBRARY_PATH ${BINARY_DIR}/taglib/${CMAKE_BUILD_TYPE}/tag.lib)

message(STATUS "LIBTAG_INCLUDE_PATH = ${LIBTAG_INCLUDE_PATH}")
message(STATUS "LIBTAG_LIBRARY_PATH = ${LIBTAG_LIBRARY_PATH}")

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
set(LIBJSON11_LIBRARY_PATH ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/json11.lib)

message(STATUS "LIBJSON11_INCLUDE_PATH = ${LIBJSON11_INCLUDE_PATH}")
message(STATUS "LIBJSON11_LIBRARY_PATH = ${LIBJSON11_LIBRARY_PATH}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure expat

set(CURRENT_EXTERNAL_PROJECT expat)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring ...")

ExternalProject_Add(expat
    PREFIX libexpat
    SOURCE_SUBDIR expat
	GIT_REPOSITORY https://github.com/libexpat/libexpat.git
    GIT_TAG R_2_2_6
    STEP_TARGETS build
    EXCLUDE_FROM_ALL TRUE
    CMAKE_ARGS -DBUILD_tools=OFF -DBUILD_examples=OFF -DBUILD_tests=OFF -DBUILD_shared=OFF -DBUILD_doc=OFF -DINSTALL=OFF -DXML_DTD=OFF -DXML_NS=ON
)

ExternalProject_Get_Property(expat SOURCE_DIR)
ExternalProject_Get_Property(expat BINARY_DIR)

set(LIBEXPAT_INCLUDE_PATH ${SOURCE_DIR})
if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(LIBEXPAT_LIBRARY_PATH ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/expatd.lib)
else()
    set(LIBEXPAT_LIBRARY_PATH ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/expat.lib)
endif()

message(STATUS "LIBEXPAT_INCLUDE_PATH = ${LIBEXPAT_INCLUDE_PATH}")
message(STATUS "LIBEXPAT_LIBRARY_PATH = ${LIBEXPAT_LIBRARY_PATH}")

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

set(LIBWXWIDGETS_INCLUDE_PATH
    ${BINARY_DIR}/lib/vc_x64_lib/mswud
    ${SOURCE_DIR}/include
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(LIBWXWIDGETS_LIBRARY_PATH
        ${BINARY_DIR}/lib/vc_x64_lib/wxbase31ud.lib
        ${BINARY_DIR}/lib/vc_x64_lib/wxmsw31ud_core.lib
        ${BINARY_DIR}/lib/vc_x64_lib/wxpngd.lib
        ${BINARY_DIR}/lib/vc_x64_lib/wxzlibd.lib
    )
else()
    set(LIBWXWIDGETS_LIBRARY_PATH
        ${BINARY_DIR}/lib/vc_x64_lib/wxbase31u.lib
        ${BINARY_DIR}/lib/vc_x64_lib/wxmsw31u_core.lib
        ${BINARY_DIR}/lib/vc_x64_lib/wxpng.lib
        ${BINARY_DIR}/lib/vc_x64_lib/wxzlib.lib
    )
endif()

message(STATUS "LIBWXWIDGETS_INCLUDE_PATH = ${LIBWXWIDGETS_INCLUDE_PATH}")
message(STATUS "LIBWXWIDGETS_LIBRARY_PATH = ${LIBWXWIDGETS_LIBRARY_PATH}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")
