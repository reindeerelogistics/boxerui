cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME Astrolabe)
set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/header/")#This is the dir to the root of the project.

project("${TARGET_NAME}" 
        VERSION 0.0.0
        DESCRIPTION "GUI and analytics component to the Boxer Robot"
        LANGUAGES CXX C
        HOMEPAGE_URL https://github.com/reindeererobotics)
                
                include(CMakePrintHelpers)
               cmake_print_variables(CMAKE_BINARY_DIR CMAKE_SOURCE_DIR CMAKE_CURRENT_BINARY_DIR CMAKE_CURRENT_SOURCE_DIR)
                

option (BOXERUI_TESTS "Build BoxerUI tests" OFF)
option (BUILD_SHARED_LIBS "Builds BoxerUI with shared libraries. Turned off by default" ON)
option (BOXERUI_LOGGING "Build BoxerUI with logging" ON)

option (BUILD_OPENCV_BASIC "Build the SDL implementation (only if supported)" ON)
option (BUILD_OPENCV_CUDA "Build OpenCV with CUDA (only if the CUDA-toolkit is available)" OFF)
option (BUILD_OPENCV_ADVANCED "Build OpenCV with advanced features)" OFF)


set(CMAKE_DEBUG_POSTFIX d)

include(FetchContent)
function(fetch_project_dep depName depRepo depTag)

    if (DEFINED ARGV3)
        message("ARGV0 defined value=${ARGV3}")
        set(SRC_DEST ${ARGV3})
    else()
        message("ARGV3 not defined")
        set(SRC_DEST "${CMAKE_CURRENT_BINARY_DIR}/${depName}")
    endif()
    
    # Check if population has been done
    FetchContent_GetProperties(${depName})
	
    if(NOT ${depName})
         # Fetch content
        FetchContent_Populate(${depName}
        GIT_REPOSITORY ${depRepo}
        GIT_TAG ${depTag}
        GIT_PROGRESS        ON
        #DOWNLOAD_DIR        "${CMAKE_CURRENT_BINARY_DIR}"
        SOURCE_DIR          "${SRC_DEST}")
        #BINARY_DIR          "${CMAKE_CURRENT_BINARY_DIR}/${depName}-build")
    endif()

   # foreach(arg IN LISTS ARGN)
    #    message("address parts: ${arg}")
    #endforeach()
    set("${depName}_SRC_DIR" ${CMAKE_CURRENT_BINARY_DIR}/${depName} PARENT_SCOPE) # Parent scope sets scope of variable in scope of calling function.
    #include_directories("${spdlog_SOURCE_DIR}/include")
    #message("Here is spdlog dir: ${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR}")
    # add_subdirectory("${depName}_SOURCE_DIR" "${depName}_BINARY_DIR")

endfunction()

include(${CMAKE_SOURCE_DIR}/cmake/Deps.cmake)

# Add directories to our project and src files
add_subdirectory("src")

if(BOXERUI_TESTS)
    include(cmake/boxerui_tests.cmake)
endif(BOXERUI_TESTS)

#include(InstallRequiredSyatemLibraries)
#    set(CPACK_RESOURCE_FILE_lICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
#    set(CPACK_PACKAGE_VERSION_MAJOR "${${TARGET_NAME}_VERSION_MAJOR}")
#    set(CPACK_PACKAGE_VERSION_MINOR "${${TARGET_NAME}_VERSION_MINOR}")
#    Include(CPack)
#    SET(CPACK_INSTALL_CMAKE_PROJECTS  "SubProject;MySub;ALL;/")
#    
#    # set the install/uninstall icon used for the installer itself
#    set (CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/resource/app.ico")
#    set (CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/resource/app.ico")
#     #set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
#
#     # set the add/remove programs icon using an installed executable
#     SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\cmake-gui.exe")
#
#     set (CPACK_PACKAGE_INSTALL_DIRECTORY "${TARGET_NAME} ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
#
#     set (CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/release/app_bmp.bmp")
#     set (CPACK_CREATE_DESKTOP_LINKS Astrolabe)
#     set (CPACK_PACKAGE_EXECUTABLES "Astrolabe")