#enable_language(CXX)
#include(GNUInstallDirs)
#install(PROGRAM 
#        DESTINATION ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}
#)

message("CPACK FILES: ${CPACK_PACKAGE_FILES}")

execute_process(COMMAND ${CMAKE_COMMAND} --install ${CPACK_PACKAGE_FILES} --prefix "${CMAKE_SOURCE_DIR}/dist/${CMAKE_BUILD_TYPE}")