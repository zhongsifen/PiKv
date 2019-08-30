mkdir -p build_m

cmake \
-D CMAKE_BUILD_TYPE=RELEASE \
-D CMAKE_INSTALL_PREFIX=./install \
-D CMAKE_CXX_FLAGS="-std=c++11" \
\
-H. \
-Bbuild_m
