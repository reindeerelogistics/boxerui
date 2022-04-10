cmake_minimum_required(VERSION 3.20)

set(TARGET_NAME Astrolabe)

project("${TARGET_NAME}" 
                        VERSION 0.0.0
                        DESCRIPTION "GUI and analytics component to the Boxer Robot"
                        LANGUAGES CXX C
                        HOMEPAGE_URL https://github.com/reindeererobotics)
                
message(STATUS "${TARGET_NAME} version: ${PROJECT_VERSION}") # Project version

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/header/")#This is the dir to the root of the project.
set(CMAKE_PCH_WARN_INVALID ON)
set(CMAKE_DEBUG_POSTFIX d)
option(${TARGET_NAME}_BUILD_USING_PCH "Build using pre-compile header support" ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
#set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug )
set_property(GLOBAL PROPERTY USE_FOLDERS ON RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time") # Set global property (all targets are impacted)
set(CMAKE_CXX_STANDARD 17)
# TODO: Use CMAKE_SIZEOF_VOID_P to check for arch type. https://stackoverflow.com/questions/39258250/how-to-detect-if-64-bit-msvc-with-cmake
                

option (${TARGET_NAME}_TESTS "Build ${TARGET_NAME} tests" OFF)
option (${TARGET_NAME}_BUILD_USING_PCH "Build ${TARGET_NAME} tests" ON)
option (BUILD_SHARED_LIBS "Builds ${TARGET_NAME} with shared libraries. Turned ON by default" ON)
option (${TARGET_NAME}_LOGGING "Build ${TARGET_NAME} with logging" ON)
option(${TARGET_NAME}_BUILD_USING_PCH "Build using pre-compile header support" ON)

option (BUILD_OPENCV_BASIC "Build the SDL implementation (only if supported)" OFF)
option (BUILD_OPENCV_CUDA "Build OpenCV with CUDA (only if the CUDA-toolkit is available)" ON)
option (BUILD_OPENCV_ADVANCED "Build OpenCV with advanced features)" OFF)



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
    #FetchContent_MakeAvailable(${depName})
    endif()    
    set("${depName}_SRC_DIR" ${CMAKE_BINARY_DIR}/${depName} PARENT_SCOPE) # Parent scope sets scope of variable in scope of calling function.
endfunction()

include(${CMAKE_SOURCE_DIR}/cmake/Deps.cmake)

# Add directories to our project and src files. Our project target is here. 
add_subdirectory("src")

if(${TARGET_NAME}_TESTS)
    include(cmake/boxerui_tests.cmake)
endif(${TARGET_NAME}_TESTS)

include(InstallRequiredSystemLibraries)
    install(FILES "LICENSE" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    install(FILES "${CMAKE_SOURCE_DIR}/resource/images/boxer.jpg" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    install(FILES "${CMAKE_SOURCE_DIR}/resource/images/app.ico" DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    # Resource: https://cmake.org/cmake/help/latest/guide/tutorial/Packaging%20an%20Installer.html
    # Resource: https://cmake.org/cmake/help/book/mastering-cmake/chapter/Packaging%20With%20CPack.html#figure-addorremoveprogramsentry
    # Resource: https://cmake.org/cmake/help/latest/module/CPack.html#variable:CPACK_GENERATOR
     set(CPACK_PACKAGE_NAME ${TARGET_NAME})
     set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
     set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
     set(CPACK_PACKAGE_VERSION_MAJOR "${${TARGET_NAME}_VERSION_MAJOR}")
     set(CPACK_PACKAGE_VERSION_MINOR "${${TARGET_NAME}_VERSION_MINOR}")
     #SET(CPACK_INSTALL_CMAKE_PROJECTS  "Release;${CPACK_PACKAGE_NAME};ALL;/")
     SET(CPACK_INSTALL_CMAKE_PROJECTS  "Release")
     set(CPACK_PACKAGE_DESCRIPTION ${PROJECT_DESCRIPTION})# can also use CPACK_PACKAGE_DESCRIPTION_FILE.
     set(CPACK_PACKAGE_HOMEPAGE_URL ${PROJECT_HOMEPAGE_URL})
     set(CPACK_PACKAGE_DESCRIPTION_SUMMARY ${PROJECT_DESCRIPTION})
     set(CPACK_PACKAGE_FILE_NAME "${CPACK_SYSTEM_NAME}-${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
     set(CPACK_SOURCE_GENERATOR "NSIS64;TGZ;ZIP")
     
    set(CPACK_SOURCE_IGNORE_FILES       # Resource: https://cmake.org/pipermail/cmake/2006-July/010039.html
        "/.git"
        "/.vs"
        "/.github"
        "/dist/"
        "/.*build.*"
        "/libs/"
        "/header/"
        "/cmake/"
        "/src/"
        "/out/"
        "/\\\\.DS_Store"
        #"/resource/images/"
        "/tests/"
        "/bin/Debug/"
    )
      #set the install/uninstall icon used for the installer itself
     set(CPACK_NSIS_MUI_ICON "resource/images/app.ico")
     set(CPACK_NSIS_MUI_UNIICON "resource/images/app.ico")
     
      # set the add/remove programs icon using an installed executable
      #SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\cmake-gui.exe")
     
      #cpack_add_component(libraries)
      #cpack_add_component(applications DISPLAY_NAME "Astrolabe Application"
      #                                                              DESCRIPTION
      #                                                              "${CPACK_PACKAGE_DESCRIPTION}"
      #                                                              DEPENDS libraries)

     set(CPACK_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")   
     set (CPACK_PACKAGE_INSTALL_DIRECTORY "${TARGET_NAME} ${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MAJOR}")
     set(CPACK_THREADS 2)
     set(CPACK_NSIS_ENABLE_UNINSTALL_BEFORE_INSTALL ON)
     set(CPACK_NSIS_DISPLAY_NAME ${CPACK_PACKAGE_NAME})
     set(CPACK_NSIS_EXECUTABLES_DIRECTORY "bin")
     set(CPACK_PACKAGE_ICON "resource/images/boxer.jpg")
     set(CPACK_PACKAGE_EXECUTABLES "${CPACK_PACKAGE_NAME}" "${CPACK_PACKAGE_NAME}")
     set(CPACK_CREATE_DESKTOP_LINKS "Astrolabe")

     set(CPACK_POST_BUILD_SCRIPTS "${CMAKE_SOURCE_DIR}/cmake/PostPackageScripts.cmake")
    
     message("CPACK_SOURCE_IGNORE_FILES = ${CPACK_SOURCE_IGNORE_FILES}")
     Include(CPack)