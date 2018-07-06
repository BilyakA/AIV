# prevent from running qmake three times (general, debug and release)
CONFIG -= debug_and_release

TEMPLATE = aux
TARGET = opencv

OTHER_FILES += \
    $$files(./opencv/*.h, true) \
    $$files(./opencv/*.hpp, true) \
    $$files(./opencv/*.c, true) \
    $$files(./opencv/*.cpp, true)

# Can not be avoided. See https://github.com/opencv/opencv/pull/9161
CONFIG(debug, debug|release) {
    BUILD_COMMANDS.buildtype = -DCMAKE_BUILD_TYPE=Debug
} else {
    BUILD_COMMANDS.buildtype = -DCMAKE_BUILD_TYPE=Release
}

#BUILD_COMMANDS += "$${LITERAL_HASH}!/bin/bash"
#BUILD_COMMANDS += "set -e"
#BUILD_COMMANDS += "set -x"
#BUILD_COMMANDS += "@echo off"

BUILD_COMMANDS += "cd $$shadowed($$PWD)"
BUILD_COMMANDS += "$$mkdir(opencv)"
BUILD_COMMANDS += "cd opencv"

BUILD_COMMANDS.platform_specific =
windows{
    BUILD_COMMANDS.platform_specific = "-G \"NMake Makefiles\" "
    BUILD_COMMANDS.platform_specific.CXX_FLAGS = "-EHa"
}
linux{
    BUILD_COMMANDS.platform_specific = "-G \"Unix Makefiles\" "
}

BUILD_COMMANDS += "rm -f $$OUT_PWD/opencv/CMakeCache.txt"
BUILD_COMMANDS += "$$removeDir($$OUT_PWD/opencv/CMakeFiles)"
windows{
    BUILD_COMMANDS += "patch -tNp1 --no-backup-if-mismatch -d\"$$system_path($$PWD)\" -i \"$$system_path($$PWD/opencv-clang.patch)\" --reject-file=\"$$system_path($$OUT_PWD/opencv/patch.rej)\""
    BUILD_COMMANDS += "patch -tNp1 --no-backup-if-mismatch -d\"$$system_path($$PWD)\" -i \"$$system_path($$PWD/opencv-win.patch)\" --reject-file=\"$$system_path($$OUT_PWD/opencv/patch.rej)\""
}
windows{
    BUILD_COMMANDS += "set CC=$$QMAKE_CC "
    BUILD_COMMANDS += "set CXX=$$QMAKE_CXX "
}
BUILD_COMMANDS += "cmake \
    $$BUILD_COMMANDS.buildtype \
    -DCMAKE_CXX_COMPILER=\"$$QMAKE_CXX\" \
    -DCMAKE_CXX_COMPILER_AR=\"$$QMAKE_AR_CMD\" \
    -DCMAKE_C_COMPILER=\"$$QMAKE_CC\" \
    -DCMAKE_C_COMPILER_AR=\"$$QMAKE_AR_CMD\" \
    -DCMAKE_INSTALL_LIBDIR=\"lib\" \
    -DCMAKE_INSTALL_PREFIX=$$BUILD_PWD/third_party/build/ -DOpenCV_INSTALL_BINARIES_PREFIX=\"\" \
    -DCMAKE_CXX_FLAGS=\"$$BUILD_COMMANDS.platform_specific.CXX_FLAGS -Wno-unknown-argument -Wno-unused-parameter -Wno-unused-command-line-argument -Wno-invalid-noreturn -Wno-comment -Wno-return-type-c-linkage -Wno-unused-parameter\" \
    -DCMAKE_C_FLAGS=\"-Wno-unknown-argument -Wno-unused-parameter -Wno-unused-command-line-argument -Wno-invalid-noreturn -Wno-comment -Wno-return-type-c-linkage -Wno-unused-parameter\" \
    $$PWD/opencv/ \
    -DENABLE_PRECOMPILED_HEADERS=OFF \
    -DWITH_TIFF=OFF -DWITH_1394=OFF -DWITH_DSHOW=OFF\
    -DBUILD_opencv_apps=OFF \
    -DBUILD_opencv_aruco=OFF \
    -DBUILD_opencv_bgsegm=OFF \
    -DBUILD_opencv_bioinspired=OFF \
    -DBUILD_opencv_calib3d=OFF \
    -DBUILD_opencv_ccalib=OFF \
    -DBUILD_opencv_core=OFF \
    -DBUILD_opencv_cvv=OFF \
    -DBUILD_opencv_datasets=OFF \
    -DBUILD_opencv_dnn=OFF \
    -DBUILD_opencv_dnn_objdetect=OFF \
    -DBUILD_opencv_dpm=OFF \
    -DBUILD_opencv_face=OFF \
    -DBUILD_opencv_features2d=OFF \
    -DBUILD_opencv_flann=OFF \
    -DBUILD_opencv_fuzzy=OFF \
    -DBUILD_opencv_hfs=OFF \
    -DBUILD_opencv_highgui=OFF \
    -DBUILD_opencv_img_hash=OFF \
    -DBUILD_opencv_imgcodecs=OFF \
    -DBUILD_opencv_imgproc=OFF \
    -DBUILD_opencv_java_bindings_generator=OFF \
    -DBUILD_opencv_js=OFF \
    -DBUILD_opencv_line_descriptor=OFF \
    -DBUILD_opencv_ml=OFF \
    -DBUILD_opencv_objdetect=OFF \
    -DBUILD_opencv_optflow=OFF \
    -DBUILD_opencv_phase_unwrapping=OFF \
    -DBUILD_opencv_photo=OFF \
    -DBUILD_opencv_plot=OFF \
    -DBUILD_opencv_python_bindings_generator=OFF \
    -DBUILD_opencv_reg=OFF \
    -DBUILD_opencv_rgbd=OFF \
    -DBUILD_opencv_saliency=OFF \
    -DBUILD_opencv_shape=OFF \
    -DBUILD_opencv_stereo=OFF \
    -DBUILD_opencv_stitching=OFF \
    -DBUILD_opencv_structured_light=OFF \
    -DBUILD_opencv_superres=OFF \
    -DBUILD_opencv_surface_matching=OFF \
    -DBUILD_opencv_text=OFF \
    -DBUILD_opencv_tracking=OFF \
    -DBUILD_opencv_ts=OFF \
    -DBUILD_opencv_video=OFF \
    -DBUILD_opencv_videoio=OFF \
    -DBUILD_opencv_videostab=OFF \
    -DBUILD_opencv_world=OFF \
    -DBUILD_opencv_xfeatures2d=OFF \
    -DBUILD_opencv_ximgproc=OFF \
    -DBUILD_opencv_xobjdetect=OFF \
    -DBUILD_opencv_xphoto=OFF \
    -DBUILD_opencv_core=ON \
    -DBUILD_opencv_videoio=ON -DBUILD_opencv_imgproc=ON -DBUILD_opencv_imgcodecs=ON \
    -DBUILD_opencv_tracking=ON -DBUILD_opencv_video=ON -DBUILD_opencv_plot=ON \
    -DBUILD_opencv_videostab=ON -DBUILD_opencv_features2d=ON -DBUILD_opencv_flann=ON -DBUILD_opencv_photo=ON -DBUILD_opencv_calib3d=ON \
    -DBUILD_opencv_saliency=ON -DBUILD_opencv_imgproc=ON -DBUILD_opencv_core=ON -DBUILD_opencv_features2d=ON -DBUILD_opencv_imgproc=ON -DBUILD_opencv_imgproc=ON \
    -DWITH_ffmpeg=ON -DWITH_QT=ON -DCMAKE_VERBOSE_MAKEFILE=ON \
    -DOPENCV_EXTRA_MODULES_PATH=\"$$PWD/opencv_contrib/modules\" \
    -DWITH_MATLAB=OFF -DWITH_VTK=OFF -DWITH_WEBP=OFF -DWITH_OPENEXR=OFF -DWITH_IPP=OFF \
    $$BUILD_COMMANDS.platform_specific "
windows{
    BUILD_COMMANDS += "nmake"
    BUILD_COMMANDS += "nmake install"
}else{
    BUILD_COMMANDS += "make -j$$num_add($$QMAKE_HOST.cpu_count, 1)"
    BUILD_COMMANDS += "make install"
}

BUILD_COMMANDS += "xcopy /Y /E $$system_path($$BUILD_PWD/third_party/build/bin/*.dll) $$system_path($$BUILD_PWD/AIV/)"

buildFileCached($$BUILD_COMMANDS)
