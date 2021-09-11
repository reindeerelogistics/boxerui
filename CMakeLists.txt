cmake_minimum_required(VERSION 3.16)
project(BoxerUI 
                VERSION 0.0.0 
                DESCRIPTION "A GUI and analytics component to the Boxer Robot"
                LANGUAGES CXX C
                HOMEPAGE_URL https://github.com/reindeererobotics)

# enable_language(CUDA)
# set( CMAKE_VERBOSE_MAKEFILE on )

message(STATUS "BoxerUI version: ${PROJECT_VERSION}")
# add_definitions ( -DBOXERUI_VERSION=${PROJECT_VERSION})

set(WORKSPACE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/BoxerUI/")#This is the dir to the root of the project.

option (BOXERUI_TESTS "Build BoxerUI tests" OFF)
option (BOXERUI_SHARED_LIBS "Builds BoxerUI with shared libraries. Turned off by default" OFF)

option (BUILD_OPENCV_BASIC "Build the SDL implementation (only if supported)" ON)
option (BUILD_OPENCV_CUDA "Build OpenCV with CUDA (only if the CUDA-toolkit is available)" OFF)
option (BUILD_OPENCV_ADVANCED "Build OpenCV with advanced features)" OFF)
# option (IMGUI_IMPL_METAL "Build the Metal implementation (only if supported)" ${APPLE})
# option (IMGUI_IMPL_OSX "Build the OSX implementation (only if supported)" ${APPLE})
# option (IMGUI_IMPL_WIN32 "Build the Win32 (native winapi) implementation (only if supported)" ${WIN32})
# option (IMGUI_IMPL_GLFW "Build the GLFW implementation (only if supported)" ON)

IF(WIN32)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/opencv/sources/out/install/x64-${CMAKE_BUILD_TYPE}/include")
    find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc)#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
ELSE()

    message(CHECK_START "Finding BoxerUI Dependencies")
    list(APPEND CMAKE_MESSAGE_INDENT ">>")
    
    message(CHECK_START "Finding OpenCV")
    # OpenCV found. Including OpenCV variables...
    set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build")
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

# Add directories to our project and src files
add_subdirectory("${WORKSPACE_DIR}/src")

if(BOXERUI_TESTS)
    include(cmake/boxerui_tests.cmake)
endif(BOXERUI_TESTS)
