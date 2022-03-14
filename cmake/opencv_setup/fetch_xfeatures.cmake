#WIP: Retrieve opencv_contrib from source and make available to rest of project

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED_${DEPNAME_UPPERCASE} ON)
FetchContent_Declare(opencv_contrib
										GIT_REPOSITORY      https://github.com/opencv/opencv_contrib.git
										GIT_TAG             master
										GIT_PROGRESS        ON
										SOURCE_DIR          "${CMAKE_BINARY_DIR}/opencv_contrib")
										#DOWNLOAD_DIR        "${PROJECT_SOURCE_DIR}")
# Fetch the content using previously declared details
FetchContent_MakeAvailable(opencv_contrib)

#FetchContent_Populate(opencv_contrib)