cmake_minimum_required(VERSION 3.16)


#Source dir and files variables
set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../header")
set(LIBS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../libs")

#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/Networking")
#add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RoboCMD")

# Set path variable to sources that will be used rather than collecting all the backend sources including ones not in use
set(IMGUI_BACKENDS_DIR "${LIBS_DIR}/imgui/backends/")
    set(IMGUI_BACKENDS_SOURCES "${IMGUI_BACKENDS_DIR}imgui_impl_glfw.cpp" "${IMGUI_BACKENDS_DIR}imgui_impl_opengl3.cpp")
    set(GL_DIR "${LIBS_DIR}/imgui/examples/libs/gl3w/")
    set(GLFW_DIR "${LIBS_DIR}/imgui/examples/libs/glfw/include")
# Use aux_source_directory() to get all source files in the specified directory and apply to a variable. 
    # Does not easily reflect new files. Requires further investigation
aux_source_directory("${HEADERS_DIR}/" BOXERUI_HEADERS) # collects all src files in the header dir
aux_source_directory("${LIBS_DIR}/imgui/" IMGUI_SOURCES)# collects all src files in the libs/imgui dir. Cannot be impl for backends dir, would attempt at compiling non required
aux_source_directory("${LIBS_DIR}/imgui/examples/libs/gl3w/" GL)
aux_source_directory("${LIBS_DIR}/imgui/examples/libs/glfw/include" GLFW)
aux_source_directory("${LIBS_DIR}/implot/" IMPLOT_SOURCES)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" BOXERUI_SOURCES)

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
IF (WIN32)
  # set stuff for windows
target_link_libraries(BoxerUI_app opencv_world453 opengl3 "${GLFW_DIR}/lib-vc2010-64/glfw3")
ELSE()
  # set stuff for other systems
target_link_libraries(BoxerUI_app OpenGL::GL glfw "${OpenCV_LIBS}")# Threads::Threads )
ENDIF()