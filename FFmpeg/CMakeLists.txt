cmake_minimum_required(VERSION 3.13.1 FATAL_ERROR)

project(FFMPEG VERSION 4.0.0 LANGUAGES CXX)

include(ExternalProject)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

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
C_COMPILER=$(basename \"${CMAKE_C_COMPILER}\")
CXX_COMPILER=$(basename \"${CMAKE_CXX_COMPILER}\")
C_FLAGS=$(echo \"${CMAKE_C_FLAGS} -Wno-deprecated-declarations -Wno-unknown-argument \" | sed 's/\\//-/g')
CXX_FLAGS=$(echo \"${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations -Wno-unknown-argument \" | sed 's/\\//-/g')
"
)
## windows-only msys2 fix
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/configure.sh
"
function pwd () { command pwd -W \"$\@\"; }; export -f pwd
"
)
## windows-only add pkg-config path
file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/configure.sh
"
export PKG_CONFIG_PATH=`cygpath -u \"${CMAKE_CURRENT_BINARY_DIR}/../\"`
echo $PKG_CONFIG_PATH
echo $PATH
pkg-config --list-all
"
)
## actual config script
set (FFMPEG_CONFIGURE "")
string (APPEND FFMPEG_CONFIGURE "\
${CMAKE_CURRENT_SOURCE_DIR}/ffmpeg/configure \
--cc=\"$\{C_COMPILER}\" --cxx=\"$\{CXX_COMPILER}\" \
--objcc=\"$\{C_COMPILER}\" --dep-cc=\"$\{C_COMPILER}\" --ld=\"lld-link\" \
--extra-cflags=\"$\{C_FLAGS}\" \
--extra-cxxflags=\"$\{CXX_FLAGS}\" \
--disable-everything \
--disable-everything \
--enable-ffmpeg --enable-ffplay --enable-ffprobe \
--enable-filter=scale \
--enable-muxer=mpegts --enable-demuxer=mpegts \
--enable-parser=h264 \
--enable-protocol=file \
--enable-shared --disable-static \
--disable-doc --prefix=\"${CMAKE_CURRENT_BINARY_DIR}/ffmpeg-prefix/build\" \
--toolchain=msvc --extra-libs=ole32.lib \
")
## INTEL:
string (APPEND FFMPEG_CONFIGURE "\
--enable-libmfx --enable-filter=scale_qsv --enable-encoder=h264_qsv \
")
### NVIDIA:
#string (APPEND FFMPEG_CONFIGURE "\
#--enable-ffnvcodec --enable-nvenc --enable-encoder=h264_nvenc \
#")
### AMD:
#string (APPEND FFMPEG_CONFIGURE "\
#--enable-amf --enable-encoder=h264_amf --extra-cflags=-I${CMAKE_CURRENT_BINARY_DIR}/../amf/include/ \
#")
### x264:
#string (APPEND FFMPEG_CONFIGURE "\
#--enable-gpl --enable-libx264 --enable-encoder=libx264 \
#")
## Debug:
string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_lower)
if(CMAKE_BUILD_TYPE_lower MATCHES "debug")
string (APPEND FFMPEG_CONFIGURE "\
--enable-debug --disable-stripping --disable-optimizations \
")
else(CMAKE_BUILD_TYPE_lower MATCHES "debug")
string (APPEND FFMPEG_CONFIGURE "\
--disable-debug --enable-stripping --enable-optimizations \
")
endif(CMAKE_BUILD_TYPE_lower MATCHES "debug")


file(APPEND ${CMAKE_CURRENT_BINARY_DIR}/configure.sh ${FFMPEG_CONFIGURE})

# actual build command
ProcessorCount(PROC_COUNT)
math(EXPR PROC_COUNT_PLUS_1 "${PROC_COUNT} + 1")
ExternalProject_Add(ffmpeg-build
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/ffmpeg-prefix
    CONFIGURE_COMMAND sh ${CMAKE_CURRENT_BINARY_DIR}/configure.sh
    BUILD_COMMAND make -j${PROC_COUNT_PLUS_1} V=1
    INSTALL_COMMAND make install -j${PROC_COUNT_PLUS_1} V=1
)

#add_dependencies(ffmpeg-build x264)
add_dependencies(ffmpeg-build libmfx)

# on build finished - copy all bins to plugin dir
add_custom_command(TARGET ffmpeg-build POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_BINARY_DIR}/ffmpeg-prefix/build/bin
            ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/../bin/
)

add_library(FFmpeg INTERFACE)
target_include_directories(FFmpeg
    INTERFACE
        ${CMAKE_CURRENT_BINARY_DIR}/ffmpeg-prefix/build/include
)
target_link_libraries(FFmpeg
    INTERFACE avdevice avfilter swscale avformat avcodec swresample avutil
)
target_link_directories(FFmpeg
    INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/ffmpeg-prefix/build/bin
)
add_dependencies(FFmpeg ffmpeg-build)
