cmake_minimum_required(VERSION 3.14)
project(MockSPForLLVMOptimization)
find_package( OpenCV REQUIRED )


set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)


link_directories(
        /usr/local/lib
)

add_executable(MockSPForLLVMOptimization main.cpp ThreadPool.cpp ThreadPool.h Task.cpp Task.h )
target_link_libraries( MockSPForLLVMOptimization ${OpenCV_LIBS} )