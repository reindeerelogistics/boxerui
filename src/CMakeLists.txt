# Use aux_source_directory() to get all source files in the specified directory and apply to a variable. 
# Does not easily reflect new files. Requires further investigation
include("../header/PopulateHeaders.cmake")
message("Headers: ${TARGET_NAME}_HEADERS")

aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}" ${TARGET_NAME}_SOURCES)

if (WIN32)
	set(PLATFORM_SRC_FILES 
								"${CMAKE_CURRENT_SOURCE_DIR}/platform/opengl/OpenglWindow.cpp")
elseif (UNIX)
	set(PLATFORM_SRC_FILES 
								"${CMAKE_CURRENT_SOURCE_DIR}/platform/directx11/Directx11Window.cpp")
else ()
    message(FATAL_ERROR "Unknown OS '${CMAKE_SYSTEM_NAME}'")
endif ()

set(SRC_FILES   "${${TARGET_NAME}_SOURCES}" 
				"${PLATFORM_SRC_FILES}")

set(SOURCES 
            #"${${TARGET_NAME}_HEADERS}" 
            ${HEADER_SRC_FILES}
            ${SRC_FILES})
            #"${${TARGET_NAME}_SOURCES}")


#GatherProjectFiles ( ${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR} "${${TARGET_NAME}_SOURCES}") # WIP
#message("Contents of my lib sources: ${MyLibSources}")

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
target_include_directories(${TARGET_NAME} PRIVATE 
    "${HEADERS_DIR}"
    "${imgui_SRC_DIR}/backends/"
    ${imgui_SRC_DIR}
    #${implot_SRC_DIR}/
    "${imgui_SRC_DIR}/examples/libs/gl3w/"
    "${glfw_SRC_DIR}/include"
    "${OpenCV_INCLUDE_DIRS}")


    
    target_link_libraries(${TARGET_NAME} PRIVATE  ${OpenCV_LIBS} OpenMP::OpenMP_CXX $<TARGET_OBJECTS:imgui> OpenGL::GL glfw)
    #target_compile_features(${TARGET_NAME} PRIVATE cxx_std_17) # This has been set globally
    target_compile_definitions(${TARGET_NAME} PRIVATE   BOXERUI_VERSION=\"${PROJECT_VERSION}\" 
                                                    BOXERUI_BIN_DIR=\"${PROJECT_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}\"
                                                    BOXERUI_ROOT_DIR="${PROJECT_SOURCE_DIR}"
                                                    BOXERUI_APP_NAME=\"${CMAKE_PROJECT_NAME}\"
                                                    BOXERUI_ASSERT_ENABLED) #TODO set path slashes properly. i.e. // : https://cmake.org/cmake/help/v3.21/command/cmake_path.html
    # Applies to all platforms 
    set_target_properties(${TARGET_NAME} PROPERTIES
                      #RUNTIME_OUTPUT_DIRECTORY_DEBUG    "${PROJECT_SOURCE_DIR}/bin/debug"
                      DEBUG_POSTFIX                     "${CMAKE_DEBUG_POSTFIX}"
                      #RUNTIME_OUTPUT_DIRECTORY_RELEASE  "${PROJECT_SOURCE_DIR}/bin/release"
                      CMAKE_LINK_WHAT_YOU_USE           ON                                      # Set compile time property for target only
                      #RULE_LAUNCH_COMPILE               "${CMAKE_COMMAND} -E time"
                      FOLDER                            "SOURCE FILES"
                      VERSION                           "${PROJECT_VERSION}")

    source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/" PREFIX "Header Files" FILES ${FILE_LIST})

    if(WIN32)
            set_target_properties(${PROJECT_NAME} PROPERTIES
                                                                LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE"
                                                                LINK_FLAGS_RELEASE "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
                                                                LINK_FLAGS_RELWITHDEBINFO "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"
                                                                LINK_FLAGS_MINSIZEREL "/SUBSYSTEM:windows /ENTRY:mainCRTStartup"    )
    endif(WIN32)
    
    install(TARGETS ${TARGET_NAME}
                                    RUNTIME DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
                                    COMPONENT applications)
                                    #LIBRARY DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
                                    #ARCHIVE DESTINATION ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})

    


include(CMakePrintHelpers)
cmake_print_properties(TARGETS ${TARGET_NAME} PROPERTIES PRECOMPILE_HEADERS CMAKE_LINK_WHAT_YOU_USE)
cmake_print_variables(CMAKE_BINARY_DIR CMAKE_SOURCE_DIR CMAKE_CURRENT_BINARY_DIR CMAKE_CURRENT_SOURCE_DIR CMAKE_SYSTEM_NAME CMAKE_HOME_DIRECTORY CMAKE_HOST_SYSTEM_NAME PLATFORM_SRC_FILES)
