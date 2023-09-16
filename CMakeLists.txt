project(caches)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O2")

set(SRC_LIST main.cpp src/cache.cpp src/ui.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})