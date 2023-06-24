git clone https://github.com/abseil/abseil-cpp.git

cd abseil-cpp
mkdir build && cd build

cmake -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_CXX_STANDARD=17 -DABSL_PROPAGATE_CXX_STD=ON ..
cmake --build . --target install
