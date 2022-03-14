include(FetchContent)
execute_process(COMMAND nproc 
                        OUTPUT_VARIABLE NUM_PROC)
set(CMAKE_BUILD_PARALLEL_LEVEL ${NUM_PROC})
# MATH(EXPR VAR "${VAR}+1") To increment a variable value

include(../find_cuda.cmake)         # Download the cuda toolkit
include(../fetch_xfeatures.cmake)   # Get opencv_contrib from source

set(OPENCV_CACHE_ARGS   -DBUILD_LIST=core,imgproc,imgcodecs,videoio
                        -DBUILD_TESTS=OFF 
                        -DBUILD_PERF_TESTS=OFF
                        -DBUILD_opencv_python2=OFF
                        -DBUILD_opencv_python3=OFF
                        -DWITH_OPENEXR=OFF
                        -DWITH_1394=OFF
                        -DWITH_EIGEN=OFF
                        -DWITH_OPENGL=ON
                        -DBUILD_SHARED_LIBS=ON
                        -DWITH_FFMPEG=OFF
                        -DBUILD_EXAMPLES=OFF
                        -DBUILD_opencv_python_tests=OFF
                        -DOPENCV_EXTRA_MODULES_PATH=${CMAKE_CURRENT_SOURCE_DIR}/opencv_contrib-master/modules
                        -DWITH-CUDA=ON
                        -DBUILD_JAVA=OFF)

set(OPENCV_CMAKE_ARGS   -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/opencv-install
                        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE})

# Check if population has already been performed
FetchContent_GetProperties(opencv)
if(NOT opencv_POPULATED)
# Fetch the content using previously declared details
    
    FetchContent_Populate(opencv
    GIT_REPOSITORY      https://github.com/opencv/opencv.git
    GIT_TAG             master
    GIT_PROGRESS        ON
    DOWNLOAD_DIR        "${CMAKE_CURRENT_SOURCE_DIR}"
    SOURCE_DIR          "${CMAKE_CURRENT_SOURCE_DIR}/opencv-master"
    BINARY_DIR          "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build"
    INSTALL_DIR         "${CMAKE_CURRENT_SOURCE_DIR}/opencv-install")
        
    message("OPENCV Cache args: ${OPENCV_CACHE_ARGS}")
    message("OPENCV cmake args: ${OPENCV_CMAKE_ARGS}")
    execute_process(COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/opencv-master" ${OPENCV_CACHE_ARGS} ${OPENCV_CMAKE_ARGS} -B "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build")
    execute_process(COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build" --parallel 3)# -- -j4)#make -j4)
    execute_process(COMMAND ${CMAKE_COMMAND} --install "${CMAKE_CURRENT_SOURCE_DIR}/opencv-install" )
    # add_subdirectory(${opencv_SOURCE_DIR} ${opencv_BINARY_DIR})
    set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build")
    find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc CONFIG NAMES OpenCV PATHS "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build/" )#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
endif()