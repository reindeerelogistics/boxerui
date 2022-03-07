cmake_minimum_required(VERSION 3.20)

include(CMakePrintHelpers)
cmake_print_variables(CMAKE_BINARY_DIR CMAKE_SOURCE_DIR CMAKE_CURRENT_BINARY_DIR CMAKE_CURRENT_SOURCE_DIR)

#Source dir and files variables
#set(HEADERS_DIR "${PROJECT_SOURCE_DIR}/BoxerUI/header")
#set(LIBS_DIR "${PROJECT_SOURCE_DIR}/BoxerUI/libs")

message(STATUS "Cmake build type: ${CMAKE_BUILD_TYPE}")

IF (WIN32)
     #set(OPENCV_DIR "${PROJECT_SOURCE_DIR}/BoxerUI/libs/opencv/sources/out/install/x64-${CMAKE_BUILD_TYPE}/x64/vc16/lib/")
    #set(OpenCV_DIR "${PROJECT_SOURCE_DIR}/BoxerUI/libs/opencv-build/lib/")
    message("OPENCV INCLUDE: ${OpenCV_DIR}")
    message("OPENCV_DIR: ${OpenCV_DIR}")
ENDIF()

# Set path variable to sources that will be used rather than collecting all the backend sources including ones not in use
#set(IMGUI_BACKENDS_DIR "${LIBS_DIR}/imgui/backends/")
#set(IMGUI_BACKENDS_SOURCES "${IMGUI_BACKENDS_DIR}imgui_impl_glfw.cpp" "${IMGUI_BACKENDS_DIR}imgui_impl_opengl3.cpp")
#set(GL_DIR "${LIBS_DIR}/imgui/examples/libs/gl3w/")
#set(GLFW_DIR "${LIBS_DIR}/imgui/examples/libs/glfw/include")

# Use aux_source_directory() to get all source files in the specified directory and apply to a variable. 
# Does not easily reflect new files. Requires further investigation
aux_source_directory("${HEADERS_DIR}" ${TARGET_NAME}_HEADERS) # collects all src files in the header dir
#aux_source_directory("${LIBS_DIR}/imgui" IMGUI_SOURCES)# collects all src files in the libs/imgui dir. Cannot be impl for backends dir, would attempt at compiling non required
#aux_source_directory("${LIBS_DIR}/imgui/examples/libs/gl3w/GL" GL_SOURCES)
#aux_source_directory("${LIBS_DIR}/imgui/examples/libs/glfw/include" GLFW_SOURCES)
#aux_source_directory("${LIBS_DIR}/implot" IMPLOT_SOURCES)
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" ${TARGET_NAME}_SOURCES)

set(SOURCES 
    "${${TARGET_NAME}_HEADERS}" 
    "${${TARGET_NAME}_SOURCES}")

include_directories("${HEADERS_DIR}" ${OpenCV_DIR} "${imgui_SRC_DIR}/backends/" 
                        ${imgui_SRC_DIR} "${CMAKE_CURRENT_SOURCE_DIR}")
                            message("SOURCE DIRECTORY: ${imgui_SRC_DIR}/imgui.h")

#Executable target name and src files
add_executable(${TARGET_NAME} "${SOURCES}")

#adds the dir for src files when compiling. Allows cmake to find where header files are located
target_include_directories(${TARGET_NAME} PUBLIC 
    "${HEADERS_DIR}/"
    #"${imgui_SRC_DIR}"
    #"${IMGUI_BACKENDS_SOURCES}"
    #"${LIBS_DIR}/implot/"
    ${glfw_SRC_DIR}/include
    ${OpenCV_DIR}
    "${OpenCV_INCLUDE_DIRS}")

IF (WIN32)
    

    #MESSAGE(STATUS "GL DIR: ${GL_DIR}GL/gl3w.h")
    # add_library(OpenCV_SHARED SHARED "" )
    target_link_libraries(${TARGET_NAME} PUBLIC  ${OpenCV_LIBS} OpenMP::OpenMP_CXX spdlog::spdlog imgui_lib)
    target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)
    target_compile_definitions(${TARGET_NAME} PUBLIC   ${TARGET_NAME}_VERSION=\"${PROJECT_VERSION}\" 
                                                    BOXERUI_BIN_DIR=\"${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}\"
                                                    BOXERUI_ROOT_DIR="${PROJECT_SOURCE_DIR}"
                                                    BOXERUI_APP_NAME=\"${CMAKE_PROJECT_NAME}\"
                                                    BOXERUI_ASSERT_ENABLED) #TODO set path slashes properly. i.e. // : https://cmake.org/cmake/help/v3.21/command/cmake_path.html

    set_target_properties(${TARGET_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG    "${PROJECT_SOURCE_DIR}/bin/debug"
                      DEBUG_POSTFIX                     "${CMAKE_DEBUG_POSTFIX}"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE  "${PROJECT_SOURCE_DIR}/bin/release"
                      VERSION                           "${PROJECT_VERSION}")

    install(FILES "${CMAKE_BINARY_DIR}/opencv/sources/out/install/x64-${CMAKE_BUILD_TYPE}/x64/vc16/lib/opencv_world453d.lib" DESTINATION "${PROJECT_SOURCE_DIR}/bin/debug")
    install(FILES "${CMAKE_BINARY_DIR}/opencv/sources/out/install/x64-${CMAKE_BUILD_TYPE}/x64/vc16/lib/opencv_world453.lib" DESTINATION "${PROJECT_SOURCE_DIR}/bin/release")

    #install(TARGETS ${TARGET_NAME} DESTINATION "${PROJECT_SOURCE_DIR}/BoxerUI/bin/debug")
    #include(InstallRequiredSyatemLibraries)
    #set(CPACK_RESOURCE_FILE_lICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
    #set(CPACK_PACKAGE_VERSION_MAJOR "${${TARGET_NAME}_VERSION_MAJOR}")
    #set(CPACK_PACKAGE_VERSION_MINOR "${${TARGET_NAME}_VERSION_MINOR}")
    #Include(CPack)
    #SET(CPACK_INSTALL_CMAKE_PROJECTS  "SubProject;MySub;ALL;/")
    #
    ## set the install/uninstall icon used for the installer itself
    #set (CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/resource/app.ico")
    #set (CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/resource/app.ico")
    # #set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    #
    # # set the add/remove programs icon using an installed executable
    # SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\cmake-gui.exe")
    #
    # set (CPACK_PACKAGE_INSTALL_DIRECTORY "${TARGET_NAME} ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
    #
    # set (CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/release/app_bmp.bmp")
    # set (CPACK_CREATE_DESKTOP_LINKS Astrolabe)
    # set (CPACK_PACKAGE_EXECUTABLES "Astrolabe")
ELSE()
    #Links the libraries to build target set in add_executable command
    find_package(OpenGL REQUIRED)
    find_package(OpenMP)
    if(OpenMP_FOUND)
        add_compile_definitions(HAVE_OPENMP=\"${OpenMP_FOUND}\")
    endif(OpenMP_FOUND)
    

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
    target_link_libraries(${TARGET_NAME} PUBLIC ${OpenCV_LIBS} spdlog::spdlog )# Threads::Threads )

    target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17)
    target_compile_definitions(${TARGET_NAME} PUBLIC   ${TARGET_NAME}_VERSION=\"${PROJECT_VERSION}\" 
                                                    ${TARGET_NAME}_BIN_DIR=\"${PROJECT_SOURCE_DIR}/BoxerUI/bin/${CMAKE_BUILD_TYPE}\"
                                                    ${TARGET_NAME}_ROOT_DIR=\"${PROJECT_SOURCE_DIR}\BoxerUI\")

    set_target_properties(${TARGET_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/BoxerUI/bin/debug"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/BoxerUI/bin/release"
    )
    # install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

ENDIF()
