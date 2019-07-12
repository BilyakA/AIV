cmake_minimum_required(VERSION 3.13.1 FATAL_ERROR)

project(QtHttpServer VERSION 4.0.0 LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}../../bin/)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}../../bin/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}../../bin/)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5
    REQUIRED
    COMPONENTS Core Network
)

add_library(QtHttpServer SHARED
    qthttpserver/src/httpserver/qabstracthttpserver.cpp
    qthttpserver/src/httpserver/qhttpserver.cpp
    qthttpserver/src/httpserver/qhttpserverrequest.cpp
    qthttpserver/src/httpserver/qhttpserverresponder.cpp
    qthttpserver/src/httpserver/qhttpserverresponse.cpp
    qthttpserver/src/httpserver/qhttpserverrouter.cpp
    qthttpserver/src/httpserver/qhttpserverrouterrule.cpp
    qthttpserver/src/3rdparty/http-parser/http_parser.c
)
set_target_properties(QtHttpServer
    PROPERTIES
    DEFINE_SYMBOL "QT_BUILD_HTTPSERVER_LIB"
)

target_link_libraries(QtHttpServer
    PUBLIC Qt5::Core Qt5::Network Qt5::CorePrivate
)

target_include_directories(QtHttpServer
    PUBLIC
        qthttpserver/src/httpserver/
        qthttpserver/src/3rdparty/http-parser/
    PRIVATE
        ${CMAKE_CURRENT_BINARY_DIR}
)

file(GLOB QtHttpServer_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/qthttpserver/src/httpserver/*.h"
)
list(FILTER QtHttpServer_HEADERS EXCLUDE REGEX "_p.h")

file(GLOB QtHttpServer_private_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/qthttpserver/src/httpserver/*_p.h"
)

file(
    COPY ${QtHttpServer_HEADERS}
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/QtHttpServer/"
)
file(
    COPY ${QtHttpServer_private_HEADERS}
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/private/"
)
file(
    COPY "${CMAKE_CURRENT_SOURCE_DIR}/headers/QtHttpServer"
    DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/QtHttpServer/"
)

add_executable(QtHttpServerExample
    qthttpserver/examples/httpserver/simple/assets.qrc
    qthttpserver/examples/httpserver/simple/main.cpp
)
target_link_libraries(QtHttpServerExample
    PUBLIC QtHttpServer Qt5::Core
)
target_include_directories(QtHttpServerExample
    PUBLIC
        "${CMAKE_CURRENT_BINARY_DIR}/QtHttpServer/"
)

