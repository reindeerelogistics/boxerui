cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME Astrolabe)
set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/header/")#This is the dir to the root of the project.

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug )

project("${TARGET_NAME}" 
        VERSION 0.0.0
        DESCRIPTION "GUI and analytics component to the Boxer Robot"
        LANGUAGES CXX C
        HOMEPAGE_URL https://github.com/reindeererobotics)
                
    include(CMakePrintHelpers)
    cmake_print_variables(CMAKE_BINARY_DIR CMAKE_SOURCE_DIR CMAKE_CURRENT_BINARY_DIR CMAKE_CURRENT_SOURCE_DIR)
                

option (BOXERUI_TESTS "Build BoxerUI tests" OFF)
option (${TARGET_NAME}_BUILD_USING_PCH "Build BoxerUI tests" ON)
option (BUILD_SHARED_LIBS "Builds BoxerUI with shared libraries. Turned ON by default" ON)
option (BOXERUI_LOGGING "Build BoxerUI with logging" ON)

option (BUILD_OPENCV_BASIC "Build the SDL implementation (only if supported)" OFF)
option (BUILD_OPENCV_CUDA "Build OpenCV with CUDA (only if the CUDA-toolkit is available)" ON)
option (BUILD_OPENCV_ADVANCED "Build OpenCV with advanced features)" OFF)


set(CMAKE_DEBUG_POSTFIX d)

function(fetch_project_dep depName depRepo depTag)
    include(FetchContent)

    string(TOUPPER ${depName} DEPNAME_UPPERCASE)
    if (DEFINED ARGV3)
        #This is the per-content equivalent of FETCHCONTENT_UPDATES_DISCONNECTED. If the global option or this option is ON, then updates will be disabled for the named content
        set(FETCHCONTENT_UPDATES_DISCONNECTED_${DEPNAME_UPPERCASE} ${ARGV3})
        message("${depName} disconnected update value=${ARGV3}")
    else()
        message("ARGV3 not defined. FETCHCONTENT_UPDATES_DISCONNECTED_${DEPNAME_UPPERCASE} is OFF")
    endif()

    set(BIN_DEST "${CMAKE_BINARY_DIR}/${depName}-build" PARENT_SCOPE)
    set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE) 
    set(${depName}_SHARED_LIBS ON CACHE BOOL "" FORCE) 
    
    # Check if population has been done
    if(NOT ${depName}_POPULATED)
         # Fetch content
        FetchContent_Declare(${depName}
                                        GIT_REPOSITORY ${depRepo}
                                        GIT_TAG ${depTag}
                                        GIT_PROGRESS        ON
                                        SOURCE_DIR          "${CMAKE_BINARY_DIR}/${depName}")
    # SET ${depName} variables and other required properties here
    FetchContent_MakeAvailable(${depName})
    endif()    
    set("${depName}_SRC_DIR" ${CMAKE_BINARY_DIR}/${depName} PARENT_SCOPE) # Parent scope sets scope of variable in scope of calling function.
endfunction()

include(${CMAKE_SOURCE_DIR}/cmake/Deps.cmake)

# Add directories to our project and src files
add_subdirectory("src")

if(BOXERUI_TESTS)
    include(cmake/boxerui_tests.cmake)
endif(BOXERUI_TESTS)

#include(InstallRequiredSyatemLibraries)
    # set(CPACK_RESOURCE_FILE_lICENSE "${PROJECT_SOURCE_DIR}/LICENSE")
    # set(CPACK_PACKAGE_VERSION_MAJOR "${${TARGET_NAME}_VERSION_MAJOR}")
    # set(CPACK_PACKAGE_VERSION_MINOR "${${TARGET_NAME}_VERSION_MINOR}")
    # Include(CPack)
    # SET(CPACK_INSTALL_CMAKE_PROJECTS  "SubProject;MySub;ALL;/")
    # 
    # # set the install/uninstall icon used for the installer itself
    # set (CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/resource/app.ico")
    # set (CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/resource/app.ico")
    #  #set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    # 
    #  # set the add/remove programs icon using an installed executable
    #  SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\cmake-gui.exe")
    # 
    #  set (CPACK_PACKAGE_INSTALL_DIRECTORY "${TARGET_NAME} ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}")
    # 
    #  set (CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/release/app_bmp.bmp")
    #  set (CPACK_CREATE_DESKTOP_LINKS Astrolabe)
    #  set (CPACK_PACKAGE_EXECUTABLES "Astrolabe")