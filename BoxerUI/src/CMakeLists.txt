cmake_minimum_required(VERSION 3.16)

#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Networking")
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RoboCMD")

#Source dir and files variables
set(HEADERS_DIR "${PROJECT_SOURCE_DIR}/BoxerUI/header")
set(LIBS_DIR "${PROJECT_SOURCE_DIR}/BoxerUI/libs")

IF (WIN32)
set(OPENCV_DIR "${PROJECT_SOURCE_DIR}/opencv/sources/out/install/x64-Release/x64/vc16/lib/")
ELSE()
set(OPENCV_DIR "${PROJECT_SOURCE_DIR}/opencv-build/install/include/opencv4/")
ENDIF()

# find_package(OpenGL REQUIRED)
# #The 3 following lines ask not to build glfw docs, tests, & examples
# set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
# set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
# set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Set path variable to sources that will be used rather than collecting all the backend sources including ones not in use
set(IMGUI_BACKENDS_DIR "${LIBS_DIR}/imgui/backends/")
    set(IMGUI_BACKENDS_SOURCES "${IMGUI_BACKENDS_DIR}imgui_impl_glfw.cpp" "${IMGUI_BACKENDS_DIR}imgui_impl_opengl3.cpp")
    set(GL_DIR "${LIBS_DIR}/imgui/examples/libs/gl3w/")
    set(GLFW_DIR "${LIBS_DIR}/imgui/examples/libs/glfw/include")
# Use aux_source_directory() to get all source files in the specified directory and apply to a variable. 
    # Does not easily reflect new files. Requires further investigation
aux_source_directory("${HEADERS_DIR}/" BOXERUI_HEADERS) # collects all src files in the header dir
aux_source_directory("${LIBS_DIR}/imgui/" IMGUI_SOURCES)# collects all src files in the libs/imgui dir. Cannot be impl for backends dir, would attempt at compiling non required
aux_source_directory("${LIBS_DIR}/imgui/examples/libs/gl3w/GL" GL)
aux_source_directory("${LIBS_DIR}/imgui/examples/libs/glfw/include" GLFW)
aux_source_directory("${LIBS_DIR}/implot/" IMPLOT_SOURCES)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" BOXERUI_SOURCES)

MESSAGE(STATUS "BOXERUI_HEADERS: ${BOXERUI_HEADERS}" )
set(SOURCES 
    "${BOXERUI_HEADERS}" 
    "${BOXERUI_SOURCES}"
    "${IMGUI_SOURCES}" 
    "${IMGUI_BACKENDS_SOURCES}"
    "${GL_DIR}"
    "${GLFW_DIR}"
    "${GL}"
    "${GLFW}"
    "${IMPLOT_SOURCES}"
    #"RoboCMD/RoboCMD.cpp"
    )

#Should print the include dir and link libs.
MESSAGE(STATUS "Include dirs ${OpenCV_INCLUDE_DIRS}")
MESSAGE(STATUS "LINK LIBRARIES ${OpenCV_LIBS}")

#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/glfw/" "${CMAKE_CURRENT_SOURCE_DIR}/glfw-build/")# Runs the CMakeLists.txt in source_dir and places the output in binary_dir
include_directories("${HEADERS_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" "${GL_DIR}" "${GLFW_DIR}")

#Executable target name and src files
add_executable(BoxerUI_app "${SOURCES}")

#adds the dir for src files when compiling. Allows cmake to find where header files are located
target_include_directories(BoxerUI_app PUBLIC 
    "${HEADERS_DIR}/" 
    "${LIBS_DIR}/imgui/"
    "${IMGUI_BACKENDS_DIR}"
    "${GL_DIR}" 
    "${GLFW_DIR}" 
    "${LIBS_DIR}/implot/")

#Links the libraries to build target set in add_executable command
    find_package(OpenGL REQUIRED)
IF (WIN32)
  # set stuff for windows
    IF(OpenGL_FOUND)
    MESSAGE(STATUS "OPENGL FOUND!!")
    ELSE()
    MESSAGE(STATUS "OPENGL NOT FOUND")
    ENDIF()

    MESSAGE(STATUS "${GL_DIR}GL/gl3w.h")
    target_link_libraries(BoxerUI_app OpenGL::GL "${OPENCV_DIR}opencv_world453.lib"  "${PROJECT_SOURCE_DIR}/BoxerUI/libs/imgui/examples/libs/glfw/lib-vc2010-64/glfw3.lib" )
ELSE()
    add_library(opengl32 STATIC "${GL_DIR}GL/gl3w.h" "${GL_DIR}GL/gl3w.c" "${GL_DIR}GL/glcorearb.h")
  # set stuff for other systems
    find_package(OpenGL REQUIRED)
    link_directories("${OPENCV_DIR}/install/lib")

    IF(OPENCV_FOUND)
    target_link_libraries(BoxerUI_app OpenGL::GL glfw  opencv_calib3d;opencv_core;opencv_features2d;opencv_flann;opencv_highgui;opencv_imgcodecs;opencv_imgproc;opencv_video;opencv_videoio )#Threads::Threads)#"${OpenCV_LIBS}" )# Threads::Threads )
    ELSE()
    target_link_libraries(BoxerUI_app OpenGL::GL glfw  "${OpenCV_LIBS}")
    ENDIF()

ENDIF()