# IMPORTANT REFERENCE. DONT DELETE: https://docs.opencv.org/4.x/db/d05/tutorial_config_reference.html

include(FetchContent)
execute_process(COMMAND nproc 
                        OUTPUT_VARIABLE NUM_PROC)
set(CMAKE_BUILD_PARALLEL_LEVEL ${NUM_PROC})
# MATH(EXPR VAR "${VAR}+1") To increment a variable value

set(OPENCV_CACHE_ARGS   -DBUILD_LIST=core,imgproc,imgcodecs,videoio
                        -DBUILD_TESTS=OFF 
                        -DBUILD_opencv_python2=OFF
                        -DBUILD_opencv_python3=OFF
                        -DWITH_OPENEXR=OFF
                        -DWITH_1394=OFF
                        -DWITH_EIGEN=OFF
                        -DWITH_OPENGL=ON
                        -DWITH_OPENMP=ON
                        -DBUILD_SHARED_LIBS=ON
                        -DWITH_FFMPEG=OFF
                        -DBUILD_EXAMPLES=OFF
                        -DBUILD_TESTS=OFF
                        -DBUILD_PERF_TESTS=OFF
                        -DBUILD_opencv_python_tests=OFF
                        -DBUILD_JAVA=OFF)

set(OPENCV_CMAKE_ARGS   -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/opencv-install
                        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

#FetchContent_Declare(opencv)    

    #set(FETCHCONTENT_UPDATES_DISCONNECTED_OPENCV ON)
# Check if population has already been performed
FetchContent_GetProperties(opencv)
if(NOT opencv_POPULATED)
# Fetch the content using previously declared details
    #set(OPENCV_BIN_INSTALL_PATH ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

    FetchContent_Populate(opencv
    GIT_REPOSITORY      https://github.com/opencv/opencv.git
    GIT_TAG             master
    GIT_PROGRESS        ON
    #DOWNLOAD_DIR        "${CMAKE_CURRENT_BINARY_DIR}"
    SOURCE_DIR          "${CMAKE_CURRENT_BINARY_DIR}/opencv-master"
    BINARY_DIR          "${CMAKE_CURRENT_BINARY_DIR}/opencv-build"
    INSTALL_DIR         "${CMAKE_CURRENT_BINARY_DIR}/opencv-install")

        # foreach(opencv_cache_arg opencv_cmake_arg IN ZIP_LISTS OPENCV_CACHE_ARGS OPENCV_CMAKE_ARGS)
        #     message(STATUS "cache=${opencv_cache_arg}, opencv_cmake_arg=${opencv_cmake_arg}")
        # endforeach()

    
    message("OPENCV Cache args: ${OPENCV_CACHE_ARGS}")
    message("OPENCV cmake args: ${OPENCV_CMAKE_ARGS}")
    execute_process(COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_BINARY_DIR}/opencv-master" ${OPENCV_CACHE_ARGS} ${OPENCV_CMAKE_ARGS} -B "${CMAKE_CURRENT_BINARY_DIR}/opencv-build")
    execute_process(COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_BINARY_DIR}/opencv-build" --parallel 3)# -- -j4)#make -j4)
    execute_process(COMMAND ${CMAKE_COMMAND} --install "${CMAKE_CURRENT_BINARY_DIR}" )
    #set_target_properties(${OpenCV_LIBS} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin")
     #add_subdirectory(${opencv_SOURCE_DIR} ${opencv_BINARY_DIR})
    install(DIRECTORY  "${OpenCV_DIR}/bin/Debug" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc CONFIG NAMES OpenCV PATHS "${CMAKE_CURRENT_BINARY_DIR}/opencv-build/" )#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
    #set(OpenCV_DIR "${CMAKE_CURRENT_BINARY_DIR}/opencv-build")

    else()
     message("Source & BIN dir: ${opencv_SOURCE_DIR} ${opencv_BINARY_DIR} \n ${CMAKE_CURRENT_BINARY_DIR}")

endif()
include(CMakePrintHelpers)
cmake_print_variables(OpenCV_LIBS OpenCV_DIR opencv_SOURCE_DIR opencv_BINARY_DIR OpenCV_INCLUDE_DIRS)