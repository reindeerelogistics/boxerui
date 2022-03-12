
include(CMakePrintHelpers)
cmake_print_variables(CMAKE_BINARY_DIR CMAKE_SOURCE_DIR CMAKE_CURRENT_BINARY_DIR CMAKE_CURRENT_SOURCE_DIR)

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
            #set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE) 
            set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE) 
            set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
            set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
            FETCH_PROJECT_DEP("glfw" "https://github.com/glfw/glfw.git" "master")
            message("GLFW DIR: ${glfw_SRC_DIR}, ${glfw_BINARY_DIR}")
            add_subdirectory("${glfw_SRC_DIR}" "${glfw_BINARY_DIR}")
endif(NOT glfw_FOUND)


## IMGUI SETUP 
    FETCH_PROJECT_DEP("imgui" "git@github.com:reindeererobotics/imgui.git" "docking" )

    #aux_source_directory("${imgui_SRC_DIR}" ${IMGUI_SOURCES})
    #file(GLOB IMGUI_SOURCES  "${imgui_SRC_DIR}/*.cpp" "${imgui_SRC_DIR}/*.h")
    #message(${IMGUI_SOURCES})
    
    set(IMGUI_BACKENDS_SOURCES "${imgui_SRC_DIR}/backends/imgui_impl_glfw.cpp" 
                                "${imgui_SRC_DIR}/backends/imgui_impl_glfw.h"
                                "${imgui_SRC_DIR}/backends/imgui_impl_opengl3.h"
                                "${imgui_SRC_DIR}/backends/imgui_impl_opengl3.cpp" )
    add_library(imgui OBJECT
                                #${IMGUI_SOURCES}
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
     #message("WHERE IS MY DLL: ${CMAKE_SOURCE_DIR}/bin/imgui_lib.dll")
    #set_target_properties(imgui_lib PROPERTIES IMPORTED_LOCATION "C:/Users/Shenanigans/Documents/BoxerUI Project/BoxerUI/bin/imgui_lib.dll")
    #install(TARGETS imgui_lib DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

    #target_compile_definitions(imgui_lib PUBLIC IMGUI_IMPL_OPENGL_LOADER_GL3W)
    
    #include(CMakePrintHelpers)
    #cmake_print_properties(imgui_lib)
    

## IMPLOT SETUP
     FETCH_PROJECT_DEP("implot" "git@github.com:epezent/implot.git" "master" )
    add_library(implot_lib  OBJECT
                                    "${implot_SRC_DIR}/implot.cpp"
                                    "${implot_SRC_DIR}/implot_internal.h"
                                    "${implot_SRC_DIR}/implot_demo.cpp"
                                    "${implot_SRC_DIR}/implot_items.cpp"
                                    "${imgui_SRC_DIR}/imgui.h"
                                    "${implot_SRC_DIR}/implot.h")
    target_include_directories(implot_lib PUBLIC "${imgui_SRC_DIR}/" ${implot_SRC_DIR})

    #set_target_properties(implot_lib PROPERTIES IMPORTED_LOCATION "${CMAKE_BINARY_DIR}/imgui_lib.dll")
    #target_link_libraries(implot_lib PUBLIC $<TARGET_OBJECTS:imgui_lib>)

#install(TARGETS imgui_lib implot_lib DESTINATION "${CMAKE_SOURCE_DIR}/bin/debug")
#install(TARGETS imgui_lib implot_lib DESTINATION "${CMAKE_SOURCE_DIR}/bin/debug")

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
            include("${CMAKE_SOURCE_DIR}/cmake/opencv_setup/opencv_basic.cmake")
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

## Logging
    IF(BOXERUI_LOGGING)
        FETCH_PROJECT_DEP("spdlog" "https://github.com/gabime/spdlog.git" "v1.x" )
        #find_package(spdlog REQUIRED)
        include_directories("${spdlog_SRC_DIR}/include")
        add_subdirectory(${spdlog_SRC_DIR} ${spdlog_BINARY_DIR})
         #FetchContent_MakeAvailable(spdlog)
         #find_package(spdlog REQUIRED)
        # TODO: set type of logging based on build type
    ENDIF()