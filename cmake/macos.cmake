
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "$ENV{HOME}/Library/Application\ Support/REAPER/UserPlugins")

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

set(LIBZ_LIBRARY_PATH ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/libz.a)
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
	CMAKE_ARGS -DBUILD_CURL_EXE=OFF -DBUILD_SHARED_LIBS=OFF -DHTTP_ONLY=ON -DENABLE_IPV6=ON -DCMAKE_USE_DARWINSSL=ON -DCMAKE_USE_OPENSSL=OFF -DCMAKE_USE_LIBSSH2=OFF -DCURL_CA_PATH=none -DBUILD_TESTING=OFF
)

ExternalProject_Get_Property(curl SOURCE_DIR)
ExternalProject_Get_Property(curl BINARY_DIR)

set(LIBCURL_INCLUDE_PATH ${SOURCE_DIR}/include)

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(LIBCURL_LIBRARY_PATH ${BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/libcurl-d.a)
else()
    set(LIBCURL_LIBRARY_PATH ${BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/libcurl.a)
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
	GIT_TAG v2.1.0
    STEP_TARGETS build
    EXCLUDE_FROM_ALL TRUE
	CMAKE_ARGS -DBUILD_SHARED_LIBS=OFF -DMP4V2_EXPORTS=0 -DMP4V2_NO_STDINT_DEFS=1
)

ExternalProject_Get_Property(mp4v2 SOURCE_DIR)
ExternalProject_Get_Property(mp4v2 BINARY_DIR)

set(LIBMP4V2_INCLUDE_PATH ${SOURCE_DIR}/include)
set(LIBMP4V2_LIBRARY_PATH ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/libmp4v2.a)

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

set(LIBTAG_LIBRARY_PATH   ${BINARY_DIR}/taglib/${CMAKE_BUILD_TYPE}/libtag.a)

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
set(LIBJSON11_LIBRARY_PATH ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/libjson11.a)

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
set(LIBEXPAT_LIBRARY_PATH ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/libexpat.a)

message(STATUS "LIBEXPAT_INCLUDE_PATH = ${LIBEXPAT_INCLUDE_PATH}")
message(STATUS "LIBEXPAT_LIBRARY_PATH = ${LIBEXPAT_LIBRARY_PATH}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")

# configure wdl

set(CURRENT_EXTERNAL_PROJECT wdl)
message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Configuring ...")

ExternalProject_Add(wdl
    PREFIX libwdl
    SOURCE_SUBDIR wdl
	GIT_REPOSITORY https://github.com/justinfrankel/WDL.git
    STEP_TARGETS build
    EXCLUDE_FROM_ALL TRUE
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
)

ExternalProject_Get_Property(wdl SOURCE_DIR)
# ExternalProject_Get_Property(wdl BINARY_DIR)

set(LIBWDL_INCLUDE_PATH ${SOURCE_DIR})
# set(LIBWDL_LIBRARY_PATH ${BINARY_DIR}/${CMAKE_BUILD_TYPE}/libwdl.a)

message(STATUS "LIBWDL_INCLUDE_PATH = ${LIBWDL_INCLUDE_PATH}")
message(STATUS "LIBWDL_LIBRARY_PATH = ${LIBWDL_LIBRARY_PATH}")

message(STATUS "${CURRENT_EXTERNAL_PROJECT}<${CMAKE_BUILD_TYPE}>: Done.")
