cmake_minimum_required(VERSION 3.16)
project("Reindeere Technologies - BoxerUI"
                VERSION 0.0.0
                DESCRIPTION "GUI and analytics component to the Boxer Robot"
                LANGUAGES CXX C
                HOMEPAGE_URL https://github.com/reindeererobotics)

# enable_language(CUDA)
# set( CMAKE_VERBOSE_MAKEFILE on )

message(STATUS "BoxerUI version: ${PROJECT_VERSION}")

set(WORKSPACE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/BoxerUI/")#This is the dir to the root of the project.

#set(CMAKE_DEBUG_POSTFIX d)
#set(CMAKE_DEBUG_POSTFIX d)

option (BOXERUI_TESTS "Build BoxerUI tests" OFF)
option (BOXERUI_SHARED_LIBS "Builds BoxerUI with shared libraries. Turned off by default" OFF)
option (BOXERUI_LOGGING "Build BoxerUI with logging" ON)

option (BUILD_OPENCV_BASIC "Build the SDL implementation (only if supported)" ON)
option (BUILD_OPENCV_CUDA "Build OpenCV with CUDA (only if the CUDA-toolkit is available)" OFF)
option (BUILD_OPENCV_ADVANCED "Build OpenCV with advanced features)" OFF)

IF(WIN32)
    # set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/opencv/sources/out/install/x64-${CMAKE_BUILD_TYPE}/include")
    message(CHECK_START "Finding BoxerUI Dependencies")
    list(APPEND CMAKE_MESSAGE_INDENT ">>")

    message(CHECK_START "Finding OpenCV")

    set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/BoxerUI/libs/opencv/sources/out/install/x64-${CMAKE_BUILD_TYPE}")
    message("OpenCV_DIR: ${OpenCV_DIR}")
    find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc)#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
    message(CHECK_PASS "found")

    IF(NOT OPENCV_FOUND)
        #WIP: build opencv from source if not found
        message(CHECK_FAIL "not found: Proceeding to build from source...")

        if(BUILD_OPENCV_BASIC)
        include(BoxerUI/cmake/opencv_basic.cmake)
        endif(BUILD_OPENCV_BASIC)

        if(BUILD_OPENCV_CUDA)
        include(BoxerUI/cmake/opencv_cuda.cmake)
        endif(BUILD_OPENCV_CUDA)

        if(BUILD_OPENCV_ADVANCED)
            include(BoxerUI/cmake/opencv_advanced.cmake)
        endif(BUILD_OPENCV_ADVANCED)

    ENDIF()

    list(POP_BACK CMAKE_MESSAGE_INDENT)
ELSE()

    message(CHECK_START "Finding BoxerUI Dependencies")
    list(APPEND CMAKE_MESSAGE_INDENT ">>")

    message(CHECK_START "Finding OpenCV")
    # OpenCV found. Including OpenCV variables...
    set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/BoxerUI/libs/opencv-build")
    find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc )#CONFIG NAMES OpenCV PATHS "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build/" )#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
    message(CHECK_PASS "found")

    IF(NOT OPENCV_FOUND)
        #WIP: build opencv from source if not found
        message(CHECK_FAIL "not found: Proceeding to build from source...")

        if(BUILD_OPENCV_BASIC)
        include(BoxerUI/cmake/opencv_basic.cmake)
        endif(BUILD_OPENCV_BASIC)

        if(BUILD_OPENCV_CUDA)
        include(BoxerUI/cmake/opencv_cuda.cmake)
        endif(BUILD_OPENCV_CUDA)

        if(BUILD_OPENCV_ADVANCED)
            include(BoxerUI/cmake/opencv_advanced.cmake)
        endif(BUILD_OPENCV_ADVANCED)

    ENDIF()

    list(POP_BACK CMAKE_MESSAGE_INDENT)
    #Should print the include dir and link libs.
    MESSAGE(STATUS "OPENCV INCLUDE DIRS: ${OpenCV_INCLUDE_DIRS}")
    MESSAGE(STATUS "OPENCV LINK LIBRARIES ${OpenCV_LIBS}")
ENDIF()

IF(BOXERUI_LOGGING)
    add_subdirectory("BoxerUI/libs/spdlog")
    # TODO: set type of logging based on build type
ENDIF()

# Add directories to our project and src files
add_subdirectory("${WORKSPACE_DIR}/src")

if(BOXERUI_TESTS)
    include(cmake/boxerui_tests.cmake)
endif(BOXERUI_TESTS)


#find_package(PkgConfig) #finding pkg-config is a helper tool

#using pkg-config to getting Gstreamer
#pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

#including GStreamer header files directory
#include_directories(
 #       ${GLIB_INCLUDE_DIRS}
 #       ${GSTREAMER_INCLUDE_DIRS}
#)

#linking GStreamer library directory
#link_directories(
 #       ${GLIB_LIBRARY_DIRS}
  #      ${GSTREAMER_LIBRARY_DIRS}
#)

#building target executable
#add_executable(${PROJECT_NAME} main.cpp)

#linking Gstreamer library with target executable
#target_link_libraries(${PROJECT_NAME} ${GSTREAMER_LIBRARIES})