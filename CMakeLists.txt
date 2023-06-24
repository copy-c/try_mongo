cmake_minimum_required(VERSION 3.28.1)
project(try_mongo)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json 3.11.2 REQUIRED)
find_package(mongocxx 3.10.1 REQUIRED)
find_package(absl REQUIRED)
find_package(fmt REQUIRED)

add_executable(try_mongo main.cpp mongo.cpp mongo.h
        exception_backoff.h)
target_link_libraries(try_mongo PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(try_mongo PRIVATE mongo::mongocxx_shared)
target_link_libraries(try_mongo PRIVATE absl::strings absl::status)
target_link_libraries(try_mongo PRIVATE fmt::fmt)