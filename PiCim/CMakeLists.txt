add_library(PiCim SHARED
	PiCim.cpp
	PiCim.hpp
)
set_target_properties(PiCim PROPERTIES
    SUFFIX .so
)

target_include_directories(PiCim PUBLIC
	${CMAKE_SOURCE_DIR}
)

target_link_libraries(PiCim LINK_PUBLIC
)
