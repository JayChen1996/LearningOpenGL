
cmake_minimum_required(VERSION 3.20)
project(test)


# MACRO predefine the system, used in code to determine
if(WIN32)
    add_compile_definitions(SYSTEM_WINDOWS)
elseif(UNIX)
    add_compile_definitions(SYSTEM_LINUX)
endif()

set(M_SOURCES main.cpp ./glad/src/glad.c)
set(M_HEADERS)



set(OpenCV_DIR /opt/opencv/4.5.5_vino_ex/lib/cmake/opencv4)
set(Pangolin_DIR /opt/pangolin/0.6/lib/cmake/Pangolin)
set(realsense2_DIR /usr/local/lib/cmake/realsense2)



find_package(Eigen3 REQUIRED)
find_package(OpenCV)
find_package(Pangolin REQUIRED)
find_package(realsense2)
find_package(GLEW REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${realsense2_INCLUDE_DIRS})
include_directories(${Eigen3_INCLUDE_DIRS})
include_directories(${Pangolin_INCLUDE_DIRS})
include_directories(./glad/include)


add_executable(imagedemo ${M_SOURCES})
link_libraries(imagedemo ${GLEW_LIBRARIES})

target_link_libraries(imagedemo ${OpenCV_LIBS})
target_link_libraries(imagedemo realsense2)
# target_link_libraries(imagedemo Eigen3:Eigen)
target_link_libraries(imagedemo glfw3 glut GL OpenGL GLX GLEW dl)
target_link_libraries(imagedemo ${Pangolin_LIBRARIES})

















