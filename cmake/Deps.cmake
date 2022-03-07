find_package(OpenGL REQUIRED)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    add_compile_definitions(HAVE_OPENMP=\"${OpenMP_CXX_FOUND}\")
endif(OpenMP_CXX_FOUND)

IF(OpenGL_FOUND)
    MESSAGE(STATUS "OPENGL FOUND!!")
ELSE()
    MESSAGE(STATUS "OPENGL NOT FOUND")
ENDIF()

if(NOT glfw_FOUND)    
            set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE) 
            set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
            set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
            set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
            FETCH_PROJECT_DEP("glfw" "https://github.com/glfw/glfw.git" "master")
            message("GLFW DIR: ${glfw_SRC_DIR}, ${glfw_BINARY_DIR}")
            add_subdirectory("${glfw_SRC_DIR}" ${glfw_BINARY_DIR})

endif(NOT glfw_FOUND)

## IMGUI SETUP
    FETCH_PROJECT_DEP("imgui" "git@github.com:reindeererobotics/imgui.git" "docking" )

    #aux_source_directory("${imgui_SRC_DIR}" ${IMGUI_SOURCES})

    file(GLOB IMGUI_SOURCES  "${imgui_SRC_DIR}/*.cpp" "${imgui_SRC_DIR}/*.h")
    #message(${IMGUI_SOURCES})
    set(IMGUI_BACKENDS_SOURCES "${imgui_SRC_DIR}/backends/imgui_impl_glfw.cpp" "${imgui_SRC_DIR}/backends/imgui_impl_opengl3.cpp")
    add_library(imgui_lib OBJECT ${IMGUI_SOURCES}
                                # ${IMGUI_BACKENDS_SOURCES}
                                ${imgui_SRC_DIR}/imgui.cpp
                                ${imgui_SRC_DIR}/imgui_draw.cpp
                                ${imgui_SRC_DIR}/imgui_demo.cpp
                                ${imgui_SRC_DIR}/imgui_tables.cpp
                                ${imgui_SRC_DIR}/imgui_widgets.cpp
                                "${imgui_SRC_DIR}/imconfig.h"
                                "${imgui_SRC_DIR}/imgui.h"
                                "${imgui_SRC_DIR}/imgui_internal.h")
                                #"${imgui_SRC_DIR}/examples/libs/gl3w.GL/gl3w.h"
                                #"${imgui_SRC_DIR}/examples/libs/gl3w.GL/gl3w.c")
    target_include_directories(imgui_lib PUBLIC ${IMGUI_SOURCES} ${IMGUI_BACKENDS_SOURCES} "${glfw_SRC_DIR}/deps")
    target_link_libraries(imgui_lib PUBLIC OpenGL::GL glfw glad opengl32)
    target_compile_definitions(imgui_lib PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
    #include(CMakePrintHelpers)
    #cmake_print_properties(imgui_lib)

# OpenCV set up
    # set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/opencv/sources/out/install/x64-${CMAKE_BUILD_TYPE}/include")
    message(CHECK_START "Finding BoxerUI Dependencies")
    list(APPEND CMAKE_MESSAGE_INDENT ">>")

    message(CHECK_START "Finding OpenCV")

    #set(OpenCV_DIR "${CMAKE_CURRENT_SOURCE_DIR}/BoxerUI/libs/opencv/sources/out/install/x64-${CMAKE_BUILD_TYPE}")
    #message("OpenCV_DIR: ${OpenCV_DIR}")
     #find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc)#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
    message(CHECK_PASS "found")

    IF(NOT OPENCV_FOUND)
        #WIP: build opencv from source if not found
        message(CHECK_FAIL "not found: Proceeding to build from source...")

        if(BUILD_OPENCV_BASIC)
            message("BUILD_OPENCV_BASIC Selected")
            include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/opencv_setup/opencv_basic.cmake")
        endif(BUILD_OPENCV_BASIC)

        if(BUILD_OPENCV_CUDA)
        message("BUILD_OPENCV_CUDA Selected")
        include(opencv_setup/opencv_cuda.cmake)
        endif(BUILD_OPENCV_CUDA)

        if(BUILD_OPENCV_ADVANCED)
        message("BUILD_OPENCV_ADVANCED Selected")
            include(opencv_setup/opencv_advanced.cmake)
        endif(BUILD_OPENCV_ADVANCED)

    ENDIF()

    list(POP_BACK CMAKE_MESSAGE_INDENT)

IF(BOXERUI_LOGGING)
     #include(FetchContent)
     #FetchContent_GetProperties(spdlog)

     FETCH_PROJECT_DEP("spdlog" "https://github.com/gabime/spdlog.git" "v1.x" )
     
    #find_package(spdlog REQUIRED)
    include_directories("${spdlog_SRC_DIR}/include")
    #message("Here is spdlog dir: ${spdlog_SOURCE_DIR}")
    add_subdirectory(${spdlog_SRC_DIR} ${spdlog_BINARY_DIR})


     #FetchContent_MakeAvailable(spdlog)
     #find_package(spdlog REQUIRED)
    # TODO: set type of logging based on build type
ENDIF()