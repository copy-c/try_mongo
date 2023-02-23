cmake_minimum_required(VERSION 3.19)
project(try_mongo)

set(CMAKE_CXX_STANDARD 17)

#find_package(libmongocxx REQUIRED)

include_directories(/usr/local/include/ /usr/local/include/mongocxx/v_noabi /usr/local/include/bsoncxx/v_noabi)
link_directories(/usr/local/lib/)

add_executable(try_mongo main.cpp)
target_link_libraries(try_mongo libmongocxx.dylib libbsoncxx.dylib)
