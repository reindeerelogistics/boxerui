cmake_minimum_required(VERSION 3.16)
project(BoxerUI)

set( CMAKE_VERBOSE_MAKEFILE on )
set(WORKSPACE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/BoxerUI/")#This is the dir to the root of the project.

IF(WIN32)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/opencv/sources/out/install/x64-${CMAKE_BUILD_TYPE}/include")
    find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc)#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
ELSE()
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/opencv-build/install/include/opencv4/")

    find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc)#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
    # execute_process(COMMAND "mkdir ${CMAKE_SOURCE_DIR}/mydir")

    IF(NOT OPENCV_FOUND)
        #TODO: build opencv from source
        MESSAGE(WARNING "OPENCV NOT FOUND")
        MESSAGE(STATUS "INSTALLING COPENCV")
        
        #TODO: Clone OpenCV repo from master. execute as command

        set(BUILD_LIST "calib3d,core,features2d,flann,highgui,imgcodecs,imgproc,videoio" CACHE STRING "Build only listed modules (comma-separated, e.g. 'videoio,dnn,ts')")
        set(BUILD_TESTS OFF CACHE BOOL "" FORCE) 
        set(BUILD_opencv_python2 OFF CACHE BOOL "" FORCE)
        set(BUILD_opencv_python3 OFF CACHE BOOL "" FORCE)
        set(WITH_OPENEXR OFF CACHE BOOL "" FORCE)
        set(WITH_1394 OFF CACHE BOOL "" FORCE) 
        set(WITH_EIGEN OFF CACHE BOOL "" FORCE)
        set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
        set(WITH_FFMPEG ON CACHE BOOL "" FORCE)

        add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/opencv-master/")# Runs the CMakeLists.txt in opencv-master and places the output in binary_dir
    ENDIF()

    #Should print the include dir and link libs.
    MESSAGE(STATUS "OPENCV INCLUDE DIRS: ${OpenCV_INCLUDE_DIRS}")
    MESSAGE(STATUS "OPENCV LINK LIBRARIES ${OpenCV_LIBS}")
ENDIF()

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glfw/")# Runs the CMakeLists.txt in source_dir

# Add directories to our project and src files
add_subdirectory("${WORKSPACE_DIR}/src")
#enable_testing()
#add_subdirectory("${WORKSPACE_DIR}/tests")
#add_subdirectory(lib/googletest)


#find_package(OpenGL REQUIRED)
    # find_package(glfw3 3.3.2 REQUIRED) #for shared library linking. Use "sudo apt-get install libglfw3-dev" to download the shared lib

    #  set(THREADS_PREFER_PTHREAD_FLAG ON)
    #  find_package(Threads REQUIRED)

#The 3 following lines ask not to build glfw docs, tests, & examples
# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
# add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glfw/")# Runs the CMakeLists.txt in source_dir

