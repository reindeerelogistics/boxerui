cmake_minimum_required(VERSION 3.16)

file(GLOB_RECURSE BOXERUI_SOURCE_TESTS LIST_DIRECTORIES true "*.h" "*.cpp")# Recuresively searches to include all files with the following pattern

add_executable(BoxerUI_Tests ${BOXERUI_SOURCE_TESTS})
add_test(NAME ${BoxerUI_Tests} COMMAND ${BoxerUI_Tests})
target_link_libraries(BoxerUI_Tests PUBLIC gtest_main )

#include(GoogleTest)
#gtest_discover_tests(hello_test)


