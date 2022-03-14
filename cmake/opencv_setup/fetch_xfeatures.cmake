#WIP: Retrieve opencv_contrib from source and make available to rest of project

include(FetchContent)

FetchContent_Declare(opencv_contrib
										GIT_REPOSITORY      https://github.com/opencv/opencv_contrib.git
										GIT_TAG             master
										GIT_PROGRESS        ON
										DOWNLOAD_DIR        "${PROJECT_SOURCE_DIR}")
# Fetch the content using previously declared details
FetchContent_GetProperties(opencv_contrib)

FetchContent_Populate(opencv_contrib)