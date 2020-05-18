cmake_minimum_required(VERSION 3.16)
project(OPERATION_UNDERWHELM)

set(CMAKE_CXX_STANDARD 17)

set(MBGL_INCL_PATH ../MBGL/cmake-build-debug/include/)
find_library(MBGL_LIB MBGL ../MBGL/cmake-build-debug/ REQUIRED)


file(COPY ../MBGL/cmake-build-debug/openal32.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ../MBGL/cmake-build-debug/libMBGL.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY ../MBGL/cmake-build-debug/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include_directories(${MBGL_INCL_PATH})

add_executable(OPERTATION_UNDERWHELM main.cpp)

target_link_libraries(OPERTATION_UNDERWHELM ${MBGL_LIB})