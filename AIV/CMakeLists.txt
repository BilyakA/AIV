cmake_minimum_required(VERSION 3.9 FATAL_ERROR)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5
    REQUIRED
    COMPONENTS Core Gui Quick
)

add_executable(Engine
    main.cpp
    CameraReader.cpp
    VideoItem.cpp
    FrameProvider.cpp
    VideoPreprocessor.cpp
    VideoFilter.cpp
    VideoProcessor.cpp
    preprocessors/homography.cpp
    preprocessors/grayscale.cpp
    filters/panoramastitcher.cpp
    filters/stabilizationfeatures.cpp
    processors/peopledetect.cpp
    CameraRreader.h
    VideoItem.h
    FrameProvider.h
    VideoPreprocessor.h
    VideoFilter.h
    VideoProcessor.h
    preprocessors/homography.h
    preprocessors/grayscale.h
    filters/panoramastitcher.h
    filters/stabilizationfeatures.h
    processors/peopledetect.h
    qml.qrc
)

target_link_libraries(Engine
    PRIVATE
        Qt5::Core Qt5::Gui Qt5::Quick
        opencv_core opencv_videoio opencv_imgproc opencv_video opencv_tracking opencv_videostab opencv_features2d opencv_saliency opencv_calib3d opencv_objdetect
        FFmpeg
        #live555
)

target_include_directories(Engine BEFORE
    PUBLIC
        ${CMAKE_BINARY_DIR}/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/calib3d/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/core/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/dnn/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/features2d/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/flann/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/gapi/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/highgui/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/imgcodecs/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/imgproc/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/java/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/js/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/ml/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/objdetect/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/photo/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/python/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/stitching/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/ts/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/video/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/videoio/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv/modules/world/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/aruco/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/bgsegm/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/bioinspired/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/ccalib/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cnn_3dobj/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cudaarithm/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cudabgsegm/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cudacodec/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cudafeatures2d/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cudafilters/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cudaimgproc/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cudalegacy/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cudaobjdetect/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cudaoptflow/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cudastereo/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cudawarping/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cudev/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/cvv/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/datasets/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/dnn_objdetect/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/dnns_easily_fooled/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/dpm/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/face/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/freetype/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/fuzzy/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/hdf/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/hfs/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/img_hash/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/line_descriptor/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/matlab/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/optflowv/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/ovis/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/phase_unwrapping/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/plot/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/reg/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/rgbd/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/saliency/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/sfm/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/shape/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/stereo/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/structured_light/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/superres/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/surface_matching/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/text/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/tracking/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/videostab/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/viz/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/xfeatures2d/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/ximgproc/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/xobjdetect/include/
        ${CMAKE_SOURCE_DIR}/opencv/opencv_contrib/modules/xphoto/include/
)

add_custom_command(TARGET Engine POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy
       ${CMAKE_SOURCE_DIR}/opencv/opencv/samples/data/vtest.avi $<TARGET_FILE_DIR:Engine>)
