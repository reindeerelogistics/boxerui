
find_package(OpenGL REQUIRED)
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    #add_compile_definitions(HAVE_OPENMP=\"${OpenMP_CXX_FOUND}\")
endif(OpenMP_CXX_FOUND)

IF(OpenGL_FOUND)
        MESSAGE(STATUS "OPENGL FOUND!!")
    ELSE()
        MESSAGE(STATUS "OPENGL NOT FOUND")
ENDIF()

if(NOT glfw_FOUND)
            set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
            set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
            set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
            FETCH_PROJECT_DEP("glfw" "https://github.com/glfw/glfw.git" "master" "ON")
            message("GLFW DIR: ${glfw_SRC_DIR}, ${glfw_BINARY_DIR}")
endif(NOT glfw_FOUND)


# IMGUI SETUP 
    FETCH_PROJECT_DEP("imgui" "git@github.com:reindeererobotics/imgui.git" "docking" "ON")
    message("IMgui SOURCE DIR: ${imgui_SRC_DIR}")
    set(IMGUI_BACKENDS_SOURCES "${imgui_SRC_DIR}/backends/imgui_impl_glfw.cpp" 
                                "${imgui_SRC_DIR}/backends/imgui_impl_glfw.h"
                                "${imgui_SRC_DIR}/backends/imgui_impl_opengl3.h"
                                "${imgui_SRC_DIR}/backends/imgui_impl_opengl3.cpp" )
    add_library(imgui OBJECT
                                ${IMGUI_BACKENDS_SOURCES}
                                "${imgui_SRC_DIR}/examples/libs/gl3w/GL/gl3w.h" 
                                "${imgui_SRC_DIR}/examples/libs/gl3w/GL/gl3w.c"
                                "${imgui_SRC_DIR}/examples/libs/gl3w/GL/glcorearb.h"
                                "${imgui_SRC_DIR}/imconfig.h"
                                "${imgui_SRC_DIR}/imgui.h"
                                "${imgui_SRC_DIR}/imgui_internal.h"
                                "${imgui_SRC_DIR}/imstb_truetype.h"
                                "${imgui_SRC_DIR}/imstb_textedit.h"
                                "${imgui_SRC_DIR}/imstb_rectpack.h"
                                "${imgui_SRC_DIR}/imgui.cpp"
                                "${imgui_SRC_DIR}/imgui_draw.cpp"
                                "${imgui_SRC_DIR}/imgui_demo.cpp"
                                "${imgui_SRC_DIR}/imgui_tables.cpp"
                                "${imgui_SRC_DIR}/imgui_widgets.cpp"
                                )
    target_include_directories(imgui PUBLIC ${imgui_SRC_DIR} 
                                               "${imgui_SRC_DIR}/backends" 
                                               "${imgui_SRC_DIR}/examples/libs/gl3w"
                                               "${glfw_SRC_DIR}/include")
    target_link_libraries(imgui PUBLIC OpenGL::GL glfw  opengl32)

    install(
    TARGETS ${imgui}
    RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
    ARCHIVE DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
)

## IMPLOT SETUP
    FETCH_PROJECT_DEP("implot" "git@github.com:epezent/implot.git" "master" "ON")
    message("IMPLOT SOURCE DIR: ${implot_SRC_DIR}")
    add_library(implot_lib  OBJECT
                                    "${implot_SRC_DIR}/implot.cpp"
                                    "${implot_SRC_DIR}/implot_internal.h"
                                    "${implot_SRC_DIR}/implot_demo.cpp"
                                    "${implot_SRC_DIR}/implot_items.cpp"
                                    #"${imgui_SRC_DIR}/imgui.h"
                                    "${implot_SRC_DIR}/implot.h")
    target_include_directories(implot_lib PUBLIC "${imgui_SRC_DIR}/" ${implot_SRC_DIR})

# OpenCV set up
    # set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SRC_DIR}/opencv/sources/out/install/x64-${CMAKE_BUILD_TYPE}/include")
    message(CHECK_START "Finding ${TARGET_NAME} Dependencies")
    list(APPEND CMAKE_MESSAGE_INDENT ">>")

    message(CHECK_START "Finding OpenCV")

    IF(NOT OpenCV_FOUND)
        #WIP: build opencv from source if not found
        message(CHECK_FAIL "not found: Proceeding to build from source...")

        if(BUILD_OPENCV_CUDA)
            message("BUILD_OPENCV_CUDA Selected")
            include("${CMAKE_SOURCE_DIR}/cmake/opencv_setup/opencv_cuda.cmake")

        elseif(BUILD_OPENCV_ADVANCED)
            message("BUILD_OPENCV_ADVANCED Selected")
            include(opencv_setup/opencv_advanced.cmake)

        else()
            message("BUILD_OPENCV_BASIC Selected")
            include("${CMAKE_SOURCE_DIR}/cmake/opencv_setup/opencv_basic.cmake")
            #find_package(OpenCV)
            message(CHECK_PASS "found")
        
        endif(BUILD_OPENCV_CUDA)
    ENDIF()

    list(POP_BACK CMAKE_MESSAGE_INDENT)
    #find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc)#optionally include highgui & imgproc modules. Each module corresponds to a directory as indicated in the header.
    #find_package(OpenCV REQUIRED core videoio OPTIONAL_COMPONENTS highgui imgproc CONFIG NAMES OpenCV PATHS "${CMAKE_CURRENT_BINARY_DIR}/opencv-build/" )

## Logging
    IF(${TARGET_NAME}_LOGGING)
        FETCH_PROJECT_DEP("spdlog" "https://github.com/gabime/spdlog.git" "v1.x" )
        include_directories("${spdlog_SRC_DIR}/include")
         #find_package(spdlog REQUIRED)
        # TODO: set type of logging based on build type
    ENDIF()