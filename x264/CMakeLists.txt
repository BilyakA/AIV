cmake_minimum_required(VERSION 3.13.1 FATAL_ERROR)

project(x264 VERSION 4.0.0 LANGUAGES CXX)

include(ExternalProject)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../../)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../../)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/../../)

# actual build script
## header
file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/configure.sh
"
#!/bin/bash
set -e
set -x
"
)
## toolkit settings
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/configure.sh
"
#export CC=$(basename \"${CMAKE_C_COMPILER}\")
export CC=cl
#export CFLAGS=`echo \"${CMAKE_C_FLAGS}\" | sed 's/\\//-/g'`
#export AS=yasm
"
)
## actual config script
set (X264_CONFIGURE "")
string (APPEND X264_CONFIGURE "\
${CMAKE_CURRENT_SOURCE_DIR}/x264/configure \
--enable-static --disable-cli \
--host=x86_64-w64-mingw32 \
--prefix=\"${CMAKE_CURRENT_BINARY_DIR}/x264-prefix/build\" \
")

file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/configure.sh ${X264_CONFIGURE})

# actual build command
ProcessorCount(PROC_COUNT)
math(EXPR PROC_COUNT_PLUS_1 "${PROC_COUNT} + 1")
ExternalProject_Add(x264-build
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/x264-prefix
    CONFIGURE_COMMAND sh ${CMAKE_CURRENT_BINARY_DIR}/configure.sh
    BUILD_COMMAND make -j${PROC_COUNT_PLUS_1} V=1
    INSTALL_COMMAND make install -j${PROC_COUNT_PLUS_1} V=1
)

# on build finished - copy pkg-config to plugin dir
add_custom_command(TARGET x264-build POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_BINARY_DIR}/x264-prefix/build/lib/pkgconfig/x264.pc
            ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/x264.pc
)

add_library(x264 INTERFACE)
add_dependencies(x264 x264-build)

