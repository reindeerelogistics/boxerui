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
message("TestSrc: ${BOXERUI_SOURCE_TESTS}")
add_executable(BoxerUI_Tests ${BOXERUI_SOURCE_TESTS})
target_link_libraries(BoxerUI_Tests PUBLIC gtest_main )
# add_test(NAME ${BoxerUI_Tests} COMMAND ${BoxerUI_Tests})
set_tests_properties(${BoxerUI_Tests} TIMEOUT 1)


# TODO: define a function to simplify adding tests
# function(do_test target arg result)
#   add_test(NAME Comp${arg} COMMAND ${target} ${arg})
#   set_tests_properties(Comp${arg}
#     PROPERTIES PASS_REGULAR_EXPRESSION ${result}
#     )
# endfunction(do_test)

include(GoogleTest)
gtest_discover_tests(BoxerUI_Tests)

