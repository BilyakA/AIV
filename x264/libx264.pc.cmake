prefix=@CMAKE_LIBRARY_OUTPUT_DIRECTORY@
exec_prefix=${prefix}
libdir=${prefix}
includedir=${prefix}/third_party/libmfx/include

Name: libmfx
Description: Intel Media SDK Dispatched static library
Version: 2013
Requires:
Requires.private:
Conflicts:
Libs: -L${libdir} -lScreenDVR_MFX @MFX_PRIVATE_LIBS@
Libs.private: @MFX_PRIVATE_LIBS@
Cflags: -I${includedir}