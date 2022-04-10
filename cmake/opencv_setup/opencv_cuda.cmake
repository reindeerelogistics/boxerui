#include(FetchContent)
#execute_process(COMMAND nproc 
#                        OUTPUT_VARIABLE NUM_PROC)
#set(CMAKE_BUILD_PARALLEL_LEVEL ${NUM_PROC})
## MATH(EXPR VAR "${VAR}+1") To increment a variable value
include("${CMAKE_SOURCE_DIR}/cmake/find_cuda.cmake")         # Download the cuda toolkit
include("${CMAKE_SOURCE_DIR}/cmake/opencv_setup/fetch_xfeatures.cmake")   # Get opencv_contrib from source

set(OPENCV_CACHE_ARGS   -DBUILD_LIST=core,imgproc,imgcodecs,videoio,calib3d,stitching,cudev,
                        -DBUILD_opencv_python2=OFF
                        -DBUILD_opencv_python3=OFF
                        -DWITH_OPENEXR=OFF
                        -DWITH_CUDA=ON
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
                        -DOPENCV_EXTRA_MODULES_PATH=${CMAKE_BINARY_DIR}/opencv_contrib/modules
                        -DWITH-CUDA=ON
                        -DWITH-GSTREAMER=ON
                        -DBUILD_JAVA=OFF)

set(OPENCV_CMAKE_ARGS   -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/opencv-install
                        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})
                        message("OPencv build type is: ${CMAKE_BUILD_TYPE}")

set(FETCHCONTENT_UPDATES_DISCONNECTED_OPENCV ON)
FetchContent_Declare(opencv
                                GIT_REPOSITORY      https://github.com/opencv/opencv.git
                                GIT_TAG             master
                                GIT_PROGRESS        ON
                                # DOWNLOAD_DIR        "${CMAKE_CURRENT_SOURCE_DIR}"
                                SOURCE_DIR          "${CMAKE_CURRENT_BINARY_DIR}/opencv-master"
                                BINARY_DIR          "${CMAKE_CURRENT_BINARY_DIR}/opencv-build"
                                INSTALL_DIR         "${CMAKE_CURRENT_BINARY_DIR}/opencv-install")
# Check if population has already been performed
FetchContent_GetProperties(opencv)
if(NOT opencv_POPULATED)
    # Fetch the content using previously declared details
    
    FetchContent_Populate(opencv)
        
    message("OPENCV Cache args: ${OPENCV_CACHE_ARGS}")
    message("OPENCV cmake args: ${OPENCV_CMAKE_ARGS}")
    #execute_process(COMMAND ${CMAKE_COMMAND} ${OPENCV_CACHE_ARGS} ${OPENCV_CMAKE_ARGS} -DCMAKE_BUILD_TYPE=Release  -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -S "${CMAKE_CURRENT_BINARY_DIR}/opencv-master"  -B "${CMAKE_CURRENT_BINARY_DIR}/opencv-build")
    #execute_process(COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_BINARY_DIR}/opencv-build" --config Release --parallel 3)# -- -j4)#make -j4)
    execute_process(COMMAND ${CMAKE_COMMAND} ${OPENCV_CACHE_ARGS} ${OPENCV_CMAKE_ARGS} -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -S "${CMAKE_CURRENT_BINARY_DIR}/opencv-master"  -B "${CMAKE_CURRENT_BINARY_DIR}/opencv-build")
    execute_process(COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_BINARY_DIR}/opencv-build" --parallel 3)# -- -j4)#make -j4)
    #execute_process(COMMAND ${CMAKE_COMMAND} --install "${CMAKE_CURRENT_BINARY_DIR}")
    find_package(OpenCV REQUIRED core videoio stitching OPTIONAL_COMPONENTS highgui imgproc CONFIG NAMES OpenCV PATHS "${CMAKE_CURRENT_BINARY_DIR}/opencv-build/" )#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
    install(DIRECTORY  "${OpenCV_DIR}/bin/${CMAKE_BUILD_TYPE}/" DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})# FILES_MATCHING PATTERN "*.dll")
    
    FetchContent_MakeAvailable(opencv_contrib opencv)
    else()
        find_package(OpenCV REQUIRED core videoio calib3d stitching cudev OPTIONAL_COMPONENTS highgui imgproc  CONFIG NAMES OpenCV PATHS "${CMAKE_CURRENT_BINARY_DIR}/opencv-build/" )#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
    
endif()

#include(ExternalProject)
#ExternalProject_Add(opencv
#							GIT_REPOSITORY      https://github.com/opencv/opencv.git
#							GIT_TAG             master
#							GIT_PROGRESS        ON
#							#INACTIVITY_TIMEOUT  "20" # in seconds
#							UPDATE_DISCONNECTED  ON
#							# DOWNLOAD_DIR        "${CMAKE_CURRENT_SOURCE_DIR}"
#							SOURCE_DIR          "${CMAKE_CURRENT_BINARY_DIR}/opencv-master"
#							BINARY_DIR          "${CMAKE_CURRENT_BINARY_DIR}/opencv-build"
#							INSTALL_DIR         "${CMAKE_CURRENT_BINARY_DIR}/opencv-install"
#                            CMAKE_CACHE_ARGS    ${OPENCV_CACHE_ARGS}
#                            CMAKE_ARGS          ${OPENCV_CMAKE_ARGS}
#                            LOG_CONFIGURE ON
#                            LOG_BUILD ON
#                            LOG_OUTPUT_ON_FAILURE ON)
#							#CONFIGURE_COMMAND  "")



include(CMakePrintHelpers)
cmake_print_variables(${OpenCV_INCLUDE_DIRS} ${OpenCV_LIBS})
message("OPencv libs: ${OpenCV_LIBS}")