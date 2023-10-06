cmake_minimum_required(VERSION 3.14)
project(caches)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(SRC_LIST main.cpp src/cache.cpp src/ui.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)