#include(FetchContent)
#execute_process(COMMAND nproc 
#                        OUTPUT_VARIABLE NUM_PROC)
#set(CMAKE_BUILD_PARALLEL_LEVEL ${NUM_PROC})
## MATH(EXPR VAR "${VAR}+1") To increment a variable value
##set(FETCHCONTENT_UPDATES_DISCONNECTED_OPENCV ON)
include("${CMAKE_SOURCE_DIR}/cmake/find_cuda.cmake")         # Download the cuda toolkit
include("${CMAKE_SOURCE_DIR}/cmake/opencv_setup/fetch_xfeatures.cmake")   # Get opencv_contrib from source

#set(OPENCV_CACHE_ARGS   -DBUILD_LIST=core,imgproc,imgcodecs,videoio,calib3d,stitching,cudev
#                        -DBUILD_opencv_python2=OFF
#                        -DBUILD_opencv_python3=OFF
#                        -DWITH_OPENEXR=OFF
#                        -DWITH_CUDA=ON
#                        -DWITH_1394=OFF
#                        -DWITH_EIGEN=OFF
#                        -DWITH_OPENGL=ON
#                        -DWITH_OPENMP=ON
#                        -DBUILD_SHARED_LIBS=ON
#                        -DWITH_FFMPEG=OFF
#                        -DBUILD_EXAMPLES=OFF
#                        -DBUILD_TESTS=OFF 
#                        -DBUILD_PERF_TESTS=OFF
#                        -DBUILD_opencv_python_tests=OFF
#                        -DOPENCV_EXTRA_MODULES_PATH=${CMAKE_BINARY_DIR}/opencv_contrib/modules
#                        -DWITH-CUDA=ON
#                        -DWITH-GSTREAMER=ON
#                        -DBUILD_JAVA=OFF)
#
#set(OPENCV_CMAKE_ARGS   -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/opencv-install
#                        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
#                        message("OPencv build type is: ${CMAKE_BUILD_TYPE}")

## Check if population has already been performed
#FetchContent_GetProperties(opencv)
#if(NOT opencv_POPULATED)
#    # Fetch the content using previously declared details
#    
#    FetchContent_Populate(opencv
#    GIT_REPOSITORY      https://github.com/opencv/opencv.git
#    GIT_TAG             master
#    GIT_PROGRESS        ON
#    # DOWNLOAD_DIR        "${CMAKE_CURRENT_SOURCE_DIR}"
#    SOURCE_DIR          "${CMAKE_CURRENT_BINARY_DIR}/opencv-master"
#    BINARY_DIR          "${CMAKE_CURRENT_BINARY_DIR}/opencv-build"
#    INSTALL_DIR         "${CMAKE_CURRENT_BINARY_DIR}/opencv-install")
#        
#    message("OPENCV Cache args: ${OPENCV_CACHE_ARGS}")
#    message("OPENCV cmake args: ${OPENCV_CMAKE_ARGS}")
#    execute_process(COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_BINARY_DIR}/opencv-master" ${OPENCV_CACHE_ARGS} ${OPENCV_CMAKE_ARGS} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -B "${CMAKE_CURRENT_BINARY_DIR}/opencv-build")
#    execute_process(COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_BINARY_DIR}/opencv-build" --parallel 3)# -- -j4)#make -j4)
#    execute_process(COMMAND ${CMAKE_COMMAND} --install "${CMAKE_CURRENT_BINARY_DIR}")
#    install(DIRECTORY  "${OpenCV_DIR}/bin/Debug/" DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})# FILES_MATCHING PATTERN "*.dll")
#    find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc CONFIG NAMES OpenCV PATHS "${CMAKE_CURRENT_BINARY_DIR}/opencv-build/" )#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
#    
#endif()

set(OPENCV_CACHE_ARGS   -DBUILD_LIST:STRING=core,imgproc,imgcodecs,videoio,calib3d,stitching,cudev,
                        -DBUILD_opencv_python2:BOOL=OFF,
                        -DBUILD_opencv_python3:BOOL=OFF,
                        -DWITH_OPENEXR:BOOL=OFF,
                        -DWITH_CUDA:BOOL=ON,
                        -DWITH_1394:BOOL=OFF,
                        -DWITH_EIGEN:BOOL=OFF,
                        -DWITH_OPENGL:BOOL=ON,
                        -DWITH_OPENMP:BOOL=ON,
                        -DBUILD_SHARED_LIBS:BOOL=ON,
                        -DWITH_FFMPEG:BOOL=OFF,
                        -DBUILD_EXAMPLES:BOOL=OFF,
                        -DBUILD_TESTS:BOOL=OFF ,
                        -DBUILD_PERF_TESTS:BOOL=OFF,
                        -DBUILD_opencv_python_tests:BOOL=OFF,
                        -DOPENCV_EXTRA_MODULES_PATH:BOOL=${CMAKE_BINARY_DIR}/opencv_contrib/modules,
                        -DWITH-CUDA:BOOL=ON,
                        -DWITH-GSTREAMER:BOOL=ON,
                        -DBUILD_JAVA:BOOL=OFF)

set(OPENCV_CMAKE_ARGS   -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/opencv-install
                        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
                        message("OPencv build type is: ${CMAKE_BUILD_TYPE}")
include(ExternalProject)
ExternalProject_Add(opencv
							GIT_REPOSITORY      https://github.com/opencv/opencv.git
							GIT_TAG             master
							GIT_PROGRESS        ON
							INACTIVITY_TIMEOUT  "20" # in seconds
							UPDATE_DISCONNECTED  ON
							# DOWNLOAD_DIR        "${CMAKE_CURRENT_SOURCE_DIR}"
							SOURCE_DIR          "${CMAKE_CURRENT_BINARY_DIR}/opencv-master"
							BINARY_DIR          "${CMAKE_CURRENT_BINARY_DIR}/opencv-build"
							INSTALL_DIR         "${CMAKE_CURRENT_BINARY_DIR}/opencv-install"
                            CMAKE_CACHE_ARGS    ${OPENCV_CACHE_ARGS}
                            CMAKE_ARGS          ${OPENCV_CMAKE_ARGS}
                            LOG_CONFIGURE ON
                            LOG_BUILD ON
                            LOG_OUTPUT_ON_FAILURE ON)
							#CONFIGURE_COMMAND  "")