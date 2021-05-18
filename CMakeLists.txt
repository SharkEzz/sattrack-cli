cmake_minimum_required(VERSION 3.2)

project(sattrack-cli)

file(GLOB_RECURSE SATTRACK_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(sattrack-cli ${SATTRACK_SOURCES})

target_compile_features(sattrack-cli PRIVATE cxx_std_17)
target_compile_options(sattrack-cli PRIVATE -Wall -Wextra -Werror -O2)
target_include_directories(sattrack-cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(sattrack-cli sgp4s jsoncpp curl)