cmake_minimum_required(VERSION 3.16)

#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Networking")
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RoboCMD")

#Source dir and files variables
set(HEADERS_DIR "${PROJECT_SOURCE_DIR}/BoxerUI/header")
set(LIBS_DIR "${PROJECT_SOURCE_DIR}/BoxerUI/libs")

# message(STATUS "HEADERS_DIR: ${HEADERS_DIR}")
message(STATUS "Cmake build type: ${CMAKE_BUILD_TYPE}")

IF (WIN32)
    set(OPENCV_DIR "${PROJECT_SOURCE_DIR}/opencv/sources/out/install/x64-Release/x64/vc16/lib/")
ENDIF()


# Set path variable to sources that will be used rather than collecting all the backend sources including ones not in use
set(IMGUI_BACKENDS_DIR "${LIBS_DIR}/imgui/backends/")
set(IMGUI_BACKENDS_SOURCES "${IMGUI_BACKENDS_DIR}imgui_impl_glfw.cpp" "${IMGUI_BACKENDS_DIR}imgui_impl_opengl3.cpp")
set(GL_DIR "${LIBS_DIR}/imgui/examples/libs/gl3w/")
set(GLFW_DIR "${LIBS_DIR}/imgui/examples/libs/glfw/include")

# Use aux_source_directory() to get all source files in the specified directory and apply to a variable. 
# Does not easily reflect new files. Requires further investigation
aux_source_directory("${HEADERS_DIR}" BOXERUI_HEADERS) # collects all src files in the header dir
aux_source_directory("${LIBS_DIR}/imgui" IMGUI_SOURCES)# collects all src files in the libs/imgui dir. Cannot be impl for backends dir, would attempt at compiling non required
aux_source_directory("${LIBS_DIR}/imgui/examples/libs/gl3w/GL" GL_SOURCES)
aux_source_directory("${LIBS_DIR}/imgui/examples/libs/glfw/include" GLFW_SOURCES)
aux_source_directory("${LIBS_DIR}/implot" IMPLOT_SOURCES)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" BOXERUI_SOURCES)

set(SOURCES 
    "${BOXERUI_HEADERS}" 
    "${BOXERUI_SOURCES}"
    "${IMGUI_SOURCES}" 
    "${IMGUI_BACKENDS_SOURCES}"
    "${GL_SOURCES}"
    "${GLFW_SOURCES}"
    "${IMPLOT_SOURCES}"
    )

include_directories("${HEADERS_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}"  "${GL_DIR}" "${GLFW_DIR}")

#Executable target name and src files
add_executable(BoxerUI_app "${SOURCES}")

#adds the dir for src files when compiling. Allows cmake to find where header files are located
target_include_directories(BoxerUI_app PUBLIC 
    "${HEADERS_DIR}/"
    "${LIBS_DIR}/imgui/"
    "${IMGUI_BACKENDS_DIR}"
    "${GL_DIR}"
    "${GLFW_DIR}"
    "${LIBS_DIR}/implot/"
    "${OPENCV_LIBS_DIR}")

    
IF (WIN32)
    IF(OpenGL_FOUND)
        MESSAGE(STATUS "OPENGL FOUND!!")
    ELSE()
        MESSAGE(STATUS "OPENGL NOT FOUND")
    ENDIF()

    MESSAGE(STATUS "GL DIR: ${GL_DIR}GL/gl3w.h")
    target_link_libraries(BoxerUI_app OpenGL::GL "${OPENCV_DIR}opencv_world453.lib"  "${PROJECT_SOURCE_DIR}/BoxerUI/libs/imgui/examples/libs/glfw/lib-vc2010-64/glfw3.lib" )
ELSE()
    #Links the libraries to build target set in add_executable command
    find_package(OpenGL REQUIRED)
    
    if(NOT glfw_FOUND)    
        include(FetchContent)
            FetchContent_Declare(
                glfw
                GIT_REPOSITORY https://github.com/glfw/glfw.git            
            )
            # For Windows: Prevent overriding the parent project's compiler/linker settings
            set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
            set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
            set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
            set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
            FetchContent_MakeAvailable(glfw)
    endif(NOT glfw_FOUND)
    
    add_library(opengl32 STATIC "${GL_DIR}GL/gl3w.h" "${GL_DIR}GL/gl3w.c" "${GL_DIR}GL/glcorearb.h")
    # add_library(glfw3 STATIC  "${GLFW_DIR}/GLFW/glfw3.h" "${GLFW_DIR}/GLFW/glfw3native.h" )
    target_link_libraries(BoxerUI_app PUBLIC OpenGL::GL glfw opengl32 ${OpenCV_LIBS} )# Threads::Threads )


    set_target_properties(BoxerUI_app PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/BoxerUI/bin/debug"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/BoxerUI/bin/release"
    )
    # install(TARGETS BoxerUI_app DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

ENDIF()
