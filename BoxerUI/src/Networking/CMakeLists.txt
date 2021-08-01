cmake_minimum_required(VERSION 3.16)
project(Networking)

find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc)#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
    set(BUILD_SHARED_LIBS OFF)
    set(OpenCV_STATIC ON)
    
    
add_executable(Networking_Target "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(Networking_Target  OpenGL "${OpenCV_LIBS}"  )