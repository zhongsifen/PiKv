add_library(PiMien SHARED
	PiMien.cpp
	PiMien.hpp
)
set_target_properties(PiMien PROPERTIES
    SUFFIX .so
)

target_include_directories(PiMien PUBLIC
	${CMAKE_SOURCE_DIR}
	${DLIB_DIR}/include
)

target_link_libraries(PiMien LINK_PUBLIC
	dl
	${DLIB_DIR}/lib/libdlib.a
	libblas.dylib
	liblapack.dylib
)
