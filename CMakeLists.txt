cmake_minimum_required(VERSION 3.16)
project(BoxerUI)


IF (WIN32)
  # set stuff for windows
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/opencv/sources/out/install/x64-Release/include")
ELSE()
# set stuff for other systems
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/opencv-build/install/include/opencv4/")
#find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc)#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
 
find_package(OpenGL REQUIRED)
    # find_package(glfw3 3.3.2 REQUIRED) #for shared library linking. Use "sudo apt-get install libglfw3-dev" to download the shared lib

    #  set(THREADS_PREFER_PTHREAD_FLAG ON)
    #  find_package(Threads REQUIRED)

#The 3 following lines ask not to build glfw docs, tests, & examples
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
 add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glfw/" "${CMAKE_CURRENT_SOURCE_DIR}/glfw-build/")# Runs the CMakeLists.txt in source_dir and places the output in binary_dir
ENDIF()

#Source dir and files variables
set(WORKSPACE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/BoxerUI/")#This is the dir to the root of the project. !Important

add_subdirectory("${WORKSPACE_DIR}/src")
#enable_testing()
#add_subdirectory("${WORKSPACE_DIR}/tests")
#add_subdirectory(lib/googletest)

#Note: Shared/dynamic libraries are linked at runtime (must be included with obj/binary file), static are linked at compile time (larger file size).

#To link glfw statically:
    #1. clone the repo into a directory <glfw_dir>: "git clone https://github.com/glfw/glfw.git"
    #2. make & select a build dir: "mkdir ./glfw-build/;cd glfw-build; cmake ../<glfw_dir>/"
    #3. !!WARNING!!. sudo make install will globally. add_subdirectory() command line 38 should avoid this.

#To link opencv statically: (For reference on configuring your build: https://docs.opencv.org/master/db/d05/tutorial_config_reference.html)
    #1. Get and unzip opencv: "wget -O opencv.zip https://github.com/opencv/opencv/archive/master.zip; unzip opencv.zip"
    #2. Build opencv: "cmake ../opencv-master/ -DBUILD_TESTS=OFF -DBUILD_opencv_python2=OFF -DBUILD_opencv_python3=OFF
                        # -DWITH_OPENEXR=OFF -DWITH_1394=OFF -DWITH_EIGEN=OFF -DWITH_OPENGL=ON
                        # -DBUILD_SHARED_LIBS=OFF -DWITH_FFMPEG=OFF ." FFMPEG could be useful: Investigate
        #2-a. More modifiable values can be found: "cmake -LH" or "cmake -L"
        #2-b. "sudo make install" will install globally. i.e. in /usr/... "make -j2" to compile in parallel (Faster install)
        #2-c. You can indicate specific modules you'll like to build e.g. "-DBUILD_opencv_python2=OFF"
    #3. Visit "cat OpenCVConfig.cmake" to view settings and variables as well as tips on including opencv to your project.
    #4. "opencv_version" to find version.
    #5. By default OpenCV will be installed to the /usr/local directory, all files will be copied to following locations:
        # /usr/local/bin - executable files
        # /usr/local/lib - libraries (.so)
        # /usr/local/cmake/opencv4 - cmake package
        # /usr/local/include/opencv4 - headers
        # /usr/local/share/opencv4 - other files (e.g. trained cascades in XML format)
