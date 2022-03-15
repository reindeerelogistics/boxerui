# Use aux_source_directory() to get all source files in the specified directory and apply to a variable. 
# Does not easily reflect new files. Requires further investigation
aux_source_directory("${HEADERS_DIR}" "${TARGET_NAME}_HEADERS") # collects all src files in the header dir
aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" ${TARGET_NAME}_SOURCES)

message("Headers: ${TARGET_NAME}_HEADERS")
set(SOURCES 
            "${${TARGET_NAME}_HEADERS}" 
            "${${TARGET_NAME}_SOURCES}")
       # message("SOURCE DIRECTORY: ${imgui_SRC_DIR}/imgui.h")

#Executable target name and src files
add_executable(${TARGET_NAME} "${SOURCES}" )

# PCH support
    if (CMAKE_VERSION VERSION_GREATER_EQUAL 3.19 AND ${TARGET_NAME}_BUILD_USING_PCH) # support for PCHs in CMake was added in 3.16
        message(STATUS "Compiling using pre-compiled header support")
        target_precompile_headers(${TARGET_NAME} PUBLIC "${HEADERS_DIR}Boxerpch.h") # With PUBLIC they will be used by targets using this target
        set(CMAKE_PCH_INSTANTIATE_TEMPLATES ON)
    else()
        message(STATUS "Disabled pre-compiled header support")
    endif()


#adds the dir for src files when compiling. Allows cmake to find where header files are located
target_include_directories(${TARGET_NAME} PUBLIC 
    "${HEADERS_DIR}/"
    "${imgui_SRC_DIR}/backends/"
    ${imgui_SRC_DIR}
    #${implot_SRC_DIR}/
    "${imgui_SRC_DIR}/examples/libs/gl3w/"
    "${glfw_SRC_DIR}/include"
    "${OpenCV_INCLUDE_DIRS}")

IF (WIN32)
    message("BUILD_LIBRARIES ARE: ${BUILD_SHARED_LIBS}")
    target_link_libraries(${TARGET_NAME} PUBLIC  ${OpenCV_LIBS} OpenMP::OpenMP_CXX $<TARGET_OBJECTS:imgui> OpenGL::GL glfw)
    #target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17) # This has been set globally
    target_compile_definitions(${TARGET_NAME} PUBLIC   BOXERUI_VERSION=\"${PROJECT_VERSION}\" 
                                                    BOXERUI_BIN_DIR=\"${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}\"
                                                    BOXERUI_ROOT_DIR="${PROJECT_SOURCE_DIR}"
                                                    BOXERUI_APP_NAME=\"${CMAKE_PROJECT_NAME}\"
                                                    BOXERUI_ASSERT_ENABLED) #TODO set path slashes properly. i.e. // : https://cmake.org/cmake/help/v3.21/command/cmake_path.html

    set_target_properties(${TARGET_NAME} PROPERTIES
                      #RUNTIME_OUTPUT_DIRECTORY_DEBUG    "${PROJECT_SOURCE_DIR}/bin/debug"
                      DEBUG_POSTFIX                     "${CMAKE_DEBUG_POSTFIX}"
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE  "${PROJECT_SOURCE_DIR}/bin/release"
                      VERSION                           "${PROJECT_VERSION}")
    
    # Set compile time property for target only
    #set_property(TARGET ${TARGET_NAME} PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")
    


include(CMakePrintHelpers)
cmake_print_variables(${TARGET_NAME}_BUILD_USING_PCH )
cmake_print_properties(TARGETS ${TARGET_NAME} PROPERTIES PRECOMPILE_HEADERS)
    #install(DIRECTORY "${CMAKE_BINARY_DIR}/opencv-build/libs/debug/" DESTINATION "${PROJECT_SOURCE_DIR}/bin/debug" FILES_MATCHING PATTERN "*.dll")
    #install(FILES "${CMAKE_BINARY_DIR}/opencv-build/libs/${CMAKE_BUILD_TYPE}/*.lib" DESTINATION "${PROJECT_SOURCE_DIR}/bin/release")

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

    #set_target_properties(${TARGET_NAME} PROPERTIES
    #                  RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/BoxerUI/bin/debug"
    #                  RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/BoxerUI/bin/release"
    #)
    # install(TARGETS ${TARGET_NAME} DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)

ENDIF()
