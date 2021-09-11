# WIP: Verify/Retrive the CUDA Toolkit from web through URL
    # URL: https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=20.04&target_type=runfile_local
    # Read more on docs/DEVELOPING.md.

find_package(CUDAToolkit )

message(CHECK_START "Finding CUDA Toolkit")

if(NOT CUDAToolkit_FOUND)
    message(CHECK_FAIL "not found")
    # Get from internet...

else()
    # CUDA Toolkit found.
    message(CHECK_PASS "found")
    message(STATUS "CUDA Toolkit arch available: ${CUDA_ARCHITECTURES}")
    add_compile_definitions(BOXERUI_CUDA=\"HAVE_CUDA\")
endif()