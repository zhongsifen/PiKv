add_library(PiDl SHARED
	PiDl.cpp
	PiDlConfig.hpp
	PiDl.hpp
	_PiDl.hpp
	dlib_anet.hpp
	../PiCim/PiCim.cpp
	../PiCim/PiCim.hpp
)
set_target_properties(PiDl PROPERTIES
    SUFFIX .so
)

target_include_directories(PiDl PUBLIC
	${CMAKE_SOURCE_DIR}
	${OPENCV_DIR}/include/opencv4
	${DLIB_DIR}/include
)

target_link_libraries(PiDl LINK_PUBLIC
	# PiCim
	${DLIB_DIR}/lib/libdlib.a
	libblas.dylib
	liblapack.dylib
)
