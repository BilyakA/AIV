prefix=@CMAKE_CURRENT_BINARY_DIR@
exec_prefix=${prefix}
libdir=${prefix}/lib
includedir=${prefix}/include

Name: libmfx
Description: Intel Media SDK Dispatched static library (@MFX_BUILD_TYPE@ @CMAKE_BUILD_TYPE@)
Version: 2013
Requires:
Requires.private:
Conflicts:
Libs: -L${libdir} -llibmfx @MFX_PRIVATE_LIBS@
Libs.private: @MFX_PRIVATE_LIBS@
Cflags: -I${includedir} -DMFX_DISPATCHER_LOG