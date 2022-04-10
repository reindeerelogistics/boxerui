#file(GLOB_RECURSE HEADER_SRC_FILES LIST_DIRECTORIES true "*.h")# Recuresively searches to include all files with the following pattern
#message("Header src files: ${HEADER_SRC_FILES}")
aux_source_directory("${HEADERS_DIR}" "${TARGET_NAME}_HEADERS")
set(PLATFORM_HEADER_DIR "${HEADERS_DIR}/platform/")# CACHE PATH "Directory to the platforms" PARENT_SCOPE) 
message("PLATFORM_HEADER_DIR: ${PLATFORM_HEADER_DIR}")

if (WIN32)
	set(PLATFORM_HEADER_FILES 
								"${PLATFORM_HEADER_DIR}/opengl/OpenglWindow.h")
elseif (UNIX)
	set(PLATFORM_HEADER_FILES 
								"${PLATFORM_HEADER_DIR}/directx11/Directx11Window.h")
else ()
    message(FATAL_ERROR "Unknown OS '${CMAKE_SYSTEM_NAME}'")
endif ()

set(HEADER_SRC_FILES 
					"${${TARGET_NAME}_HEADERS}" 
					"${PLATFORM_HEADER_FILES}")

include(CMakePrintHelpers)
cmake_print_variables(CMAKE_BINARY_DIR CMAKE_SOURCE_DIR CMAKE_CURRENT_BINARY_DIR CMAKE_CURRENT_SOURCE_DIR PLATFORM_HEADER_DIR)
