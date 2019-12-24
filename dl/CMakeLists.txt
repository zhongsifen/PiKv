add_library(dl SHARED
	dl.cpp
	dl.hpp
	dl_anet.hpp
	dl_config.hpp
)
set_target_properties(dl PROPERTIES
    SUFFIX .so
)

target_include_directories(dl PUBLIC
	${CMAKE_SOURCE_DIR}
	${DLIB_DIR}/include
)

target_link_libraries(dl LINK_PUBLIC
	${DLIB_DIR}/lib/libdlib.a
	libblas.dylib
	liblapack.dylib
)
