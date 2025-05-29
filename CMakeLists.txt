cmake_minimum_required(VERSION 3.16)
project(FaceDetectionCpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "-g")

# Add OpenCV
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include)

# Workaround for Iconv target error
find_package(Iconv)
if(NOT TARGET Iconv::Iconv)
    add_library(Iconv::Iconv INTERFACE IMPORTED)
endif()

# Automatically collect all .cpp files in the src directory
file(GLOB SRC_FILES "src/*.cpp")

# Add your main file and the collected source files
add_executable(FaceDetectionCpp main.cpp ${SRC_FILES})

target_link_libraries(FaceDetectionCpp ${OpenCV_LIBS})
