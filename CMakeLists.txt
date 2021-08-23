cmake_minimum_required(VERSION 3.16)
project(BoxerUI)

# set( CMAKE_VERBOSE_MAKEFILE on )
set(WORKSPACE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/BoxerUI/")#This is the dir to the root of the project.
find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc )
IF(WIN32)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/opencv/sources/out/install/x64-${CMAKE_BUILD_TYPE}/include")
    find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc)#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
ELSE()

    # set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build")
    find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc )#CONFIG NAMES OpenCV PATHS "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build/" )#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
    
    IF(NOT OPENCV_FOUND)
        #WIP: build opencv from source if not found 
        MESSAGE(WARNING "OPENCV NOT FOUND")
        MESSAGE(STATUS "INSTALLING OPENCV")

        include(FetchContent)
        execute_process(COMMAND nproc 
                                OUTPUT_VARIABLE NUM_PROC)
        set(CMAKE_BUILD_PARALLEL_LEVEL ${NUM_PROC})
        # MATH(EXPR VAR "${VAR}+1") To increment a variable value

        set(OPENCV_CACHE_ARGS 
                            -DBUILD_LIST=core,imgproc,imgcodecs,videoio
                            -DBUILD_TESTS=OFF 
                            -DBUILD_opencv_python2=OFF
                            -DBUILD_opencv_python3=OFF
                            -DWITH_OPENEXR=OFF
                            -DWITH_1394=OFF
                            -DWITH_EIGEN=OFF
                            -DWITH_OPENGL=ON
                            -DBUILD_SHARED_LIBS=OFF
                            -DWITH_FFMPEG=OFF
                            -DBUILD_EXAMPLES=OFF
                            -DBUILD_TESTS=OFF
                            -DBUILD_opencv_python_tests=OFF
                            -DBUILD_JAVA=OFF
        )
        set(OPENCV_CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/opencv-install
                              -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        )

        FetchContent_Declare(opencv)               
        # FetchContent_MakeAvailable(opencv)
        
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
            INSTALL_DIR         "${CMAKE_CURRENT_SOURCE_DIR}/opencv-install"
            )

                # foreach(opencv_cache_arg opencv_cmake_arg IN ZIP_LISTS OPENCV_CACHE_ARGS OPENCV_CMAKE_ARGS)
                #     message(STATUS "cache=${opencv_cache_arg}, opencv_cmake_arg=${opencv_cmake_arg}")
                # endforeach()

            
            message("OPENCV Cache args: ${OPENCV_CACHE_ARGS}")
            message("OPENCV cmake args: ${OPENCV_CMAKE_ARGS}")
            execute_process(COMMAND ${CMAKE_COMMAND} -S "${CMAKE_CURRENT_SOURCE_DIR}/opencv-master" ${OPENCV_CACHE_ARGS} ${OPENCV_CMAKE_ARGS} -B "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build")
            execute_process(COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build" --parallel 3 -- -j4)#make -j4)
            execute_process(COMMAND ${CMAKE_COMMAND} --install "${CMAKE_CURRENT_SOURCE_DIR}/opencv-install" )
            # add_subdirectory(${opencv_SOURCE_DIR} ${opencv_BINARY_DIR})
            set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build")
            find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc CONFIG NAMES OpenCV PATHS "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build/" )#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
        endif()


    ENDIF()


    #Should print the include dir and link libs.
    MESSAGE(STATUS "OPENCV INCLUDE DIRS: ${OpenCV_INCLUDE_DIRS}")
    MESSAGE(STATUS "OPENCV LINK LIBRARIES ${OpenCV_LIBS}")
ENDIF()

# Add directories to our project and src files
add_subdirectory("${WORKSPACE_DIR}/src")

enable_testing()
add_subdirectory("${WORKSPACE_DIR}/tests")


