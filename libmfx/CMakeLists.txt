cmake_minimum_required(VERSION 3.13.1 FATAL_ERROR)

project(libmfx VERSION 4.0.0 LANGUAGES CXX)

if(USE_PREBUILT_LIBMFX)
    set (MFX_PRIVATE_LIBS "")
    string(REGEX MATCHALL "(([^\" ]+|\"[^\"]+\")|[^\" ]+\\.(a|so|dll|lib))" MY_PRIVATE_LIBS ${CMAKE_CXX_STANDARD_LIBRARIES})
    foreach(lib ${MY_PRIVATE_LIBS})
        string(REGEX REPLACE ".lib" "" _lib ${lib})
        string(PREPEND _lib "-l")
        string (APPEND MFX_PRIVATE_LIBS ${_lib} " ")
    endforeach(lib)
    string (APPEND MFX_PRIVATE_LIBS " -llegacy_stdio_definitions")
    ## Debug:
    string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_lower)
    if (CMAKE_BUILD_TYPE_lower MATCHES "debug" OR CMAKE_BUILD_TYPE_lower MATCHES "relwithdebinfo")
        string (APPEND MFX_PRIVATE_LIBS " -lmsvcrtd")
    else(CMAKE_BUILD_TYPE_lower MATCHES "debug" OR CMAKE_BUILD_TYPE_lower MATCHES "relwithdebinfo")
        string (APPEND MFX_PRIVATE_LIBS " -lmsvcrt")
    endif(CMAKE_BUILD_TYPE_lower MATCHES "debug" OR CMAKE_BUILD_TYPE_lower MATCHES "relwithdebinfo")

    set(MFX_BUILD_TYPE "SDK prebuilt dispatcher")
    configure_file (${CMAKE_CURRENT_SOURCE_DIR}/libmfx.pc.cmake ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libmfx.pc @ONLY)

    file(TO_CMAKE_PATH "$ENV{INTELMEDIASDKROOT}" INTELMEDIASDK_PATH)
    add_custom_target(MFX_COPY_LIB
        COMMAND ${CMAKE_COMMAND} -E copy
                ${INTELMEDIASDK_PATH}/lib/x64/libmfx.lib
                ${CMAKE_CURRENT_BINARY_DIR}/lib/libmfx.lib
    )
    add_custom_target(MFX_COPY_INCLUDE
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${INTELMEDIASDK_PATH}/include
                ${CMAKE_CURRENT_BINARY_DIR}/include/mfx
    )

    add_library(libmfx INTERFACE)
    add_dependencies(libmfx MFX_COPY_LIB MFX_COPY_INCLUDE)
else(USE_PREBUILT_LIBMFX)

    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib/)

    add_compile_definitions(MFX_DISPATCHER_LOG)

    file(TO_CMAKE_PATH "$ENV{INTELMEDIASDKROOT}" INTELMEDIASDK_PATH)
    file(GLOB INTELMEDIASDK_SRC
        "${INTELMEDIASDK_PATH}/opensource/mfx_dispatch/src/*.c"
        "${INTELMEDIASDK_PATH}/opensource/mfx_dispatch/src/*.cpp"
    )

    # intel's mfx_load_dll adds _d suffix to every dll
    # so we need to exclude it from sources, make a copy of it,
    # repalce all *_d.dll with *.dll and add resulting file to sources
    list(REMOVE_ITEM INTELMEDIASDK_SRC "${INTELMEDIASDK_PATH}/opensource/mfx_dispatch/src/mfx_load_dll.cpp")
    file(READ "${INTELMEDIASDK_PATH}/opensource/mfx_dispatch/src/mfx_load_dll.cpp" _MFX_LOAD_DLL)
    string(REPLACE "_d.dll" ".dll" _MFX_LOAD_DLL "${_MFX_LOAD_DLL}")
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/mfx_load_dll.cpp" "${_MFX_LOAD_DLL}")
    list(APPEND INTELMEDIASDK_SRC "${CMAKE_CURRENT_BINARY_DIR}/mfx_load_dll.cpp")

    add_library(libmfx STATIC
        ${INTELMEDIASDK_SRC}
    )
    target_include_directories(libmfx
        PRIVATE
            ${INTELMEDIASDK_PATH}/opensource/mfx_dispatch/include
            ${INTELMEDIASDK_PATH}/include
    )
    add_custom_target(MFX_COPY_INCLUDE
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${INTELMEDIASDK_PATH}/include
                ${CMAKE_CURRENT_BINARY_DIR}/include/mfx
    )
    add_dependencies(libmfx MFX_COPY_INCLUDE)

    set (MFX_PRIVATE_LIBS "")
    string(REGEX MATCHALL "(([^\" ]+|\"[^\"]+\")|[^\" ]+\\.(a|so|dll|lib))" MY_PRIVATE_LIBS ${CMAKE_CXX_STANDARD_LIBRARIES})
    foreach(lib ${MY_PRIVATE_LIBS})
        string(REGEX REPLACE ".lib" "" _lib ${lib})
        string(PREPEND _lib "-l")
        string (APPEND MFX_PRIVATE_LIBS ${_lib} " ")
    endforeach(lib)
    string (APPEND MFX_PRIVATE_LIBS " -llegacy_stdio_definitions")

    ## Debug:
    string(TOLOWER ${CMAKE_BUILD_TYPE} CMAKE_BUILD_TYPE_lower)
    if (CMAKE_BUILD_TYPE_lower MATCHES "debug" OR CMAKE_BUILD_TYPE_lower MATCHES "relwithdebinfo")
        string (APPEND MFX_PRIVATE_LIBS " -lmsvcrtd")
    else(CMAKE_BUILD_TYPE_lower MATCHES "debug" OR CMAKE_BUILD_TYPE_lower MATCHES "relwithdebinfo")
        string (APPEND MFX_PRIVATE_LIBS " -lmsvcrt")
    endif(CMAKE_BUILD_TYPE_lower MATCHES "debug" OR CMAKE_BUILD_TYPE_lower MATCHES "relwithdebinfo")

    set(MFX_BUILD_TYPE "SDK opensource dispatcher")
    configure_file (${CMAKE_CURRENT_SOURCE_DIR}/libmfx.pc.cmake ${CMAKE_CURRENT_BINARY_DIR}/../libmfx.pc @ONLY)
endif(USE_PREBUILT_LIBMFX)
