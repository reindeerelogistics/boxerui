cmake_minimum_required(VERSION 3.16)
project(BoxerUI_Network)

#file(GLOB to_remove file_to_remove.cpp)
#list(REMOVE_ITEM list ${to_remove})   

#file(APPEND <filename> <content>...)
# reference on file(): https://cmake.org/cmake/help/latest/command/file.html

# aux_source_directory("${CMAKE_CURRENT_LIST_DIR}" NETWORK_SOURCE_FILES)
# list(REMOVE_ITEM NETWORK_SOURCE_FILES "src/f4.cpp")
set(NETWORK_SOURCE_FILES "uiBackend.cpp")

include_directories(${NETWORK_SOURCE_FILES})

add_library(NETWORK_TARGET STATIC "${NETWORK_SOURCE_FILES}")