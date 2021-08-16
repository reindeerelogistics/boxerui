cmake_minimum_required(VERSION 3.16)
project(BoxerUI_Tests)


include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# include(ExternalProject)
# FetchContent_Declare(googletest
#     GIT_REPOSITORY https://github.com/google/googletest
#     # CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}
# )


file(GLOB_RECURSE BOXERUI_SOURCE_TESTS LIST_DIRECTORIES true "*.h" "*.cpp")# Recuresively searches to include all files with the following pattern
message("TsetSrc: ${BOXERUI_SOURCE_TESTS}")
add_executable(BoxerUI_Tests ${BOXERUI_SOURCE_TESTS})
target_link_libraries(BoxerUI_Tests PUBLIC gtest_main )
# add_test(NAME ${BoxerUI_Tests} COMMAND ${BoxerUI_Tests})

include(GoogleTest)
gtest_discover_tests(BoxerUI_Tests)

