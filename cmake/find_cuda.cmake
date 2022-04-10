# WIP: Verify/Retrive the CUDA Toolkit from web through URL
    # URL: https://developer.nvidia.com/cuda-downloads?target_os=Linux&target_arch=x86_64&Distribution=Ubuntu&target_version=20.04&target_type=runfile_local
    # Read more on docs/DEVELOPING.md.

find_package(CUDAToolkit )

message(CHECK_START "Finding CUDA Toolkit")

if(NOT CUDAToolkit_FOUND)
    message(CHECK_FAIL "not found")
    message(SEND_ERROR "CUDAToolkit not found. Build will continue without the CUDAToolkit")
    # TODO: Get from internet...
    if (WIN32)
        #do something
    else()
        #macro(add_some_kind_of_target target_name infile outfile)
        #add_custom_command(
        #    OUTPUT ${outfile}
        #    COMMAND my_script.sh -i ${infile} --out ${outfile}
        #    DEPENDS ${infile} my_script.sh
        #)
        #add_custom_target(${target_name} DEPENDS ${outfile})
        #endmacro()
        
        # execute_process(COMMAND lspci | grep -i nvidia OUTPUT_VARIABLE )
        #    wget https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/cuda-ubuntu2004.pin
        #sudo mv cuda-ubuntu2004.pin /etc/apt/preferences.d/cuda-repository-pin-600
        #wget https://developer.download.nvidia.com/compute/cuda/11.6.1/local_installers/cuda-repo-ubuntu2004-11-6-local_11.6.1-510.47.03-1_amd64.deb
        #sudo dpkg -i cuda-repo-ubuntu2004-11-6-local_11.6.1-510.47.03-1_amd64.deb
        #sudo apt-key add /var/cuda-repo-ubuntu2004-11-6-local/7fa2af80.pub
        #sudo apt-get update
        #sudo apt-get -y install cuda
    endif (WIN32)
        

else()
    # CUDA Toolkit found.
    message(CHECK_PASS "found")
    message(STATUS "CUDA Toolkit arch available: ${CUDA_ARCHITECTURES}")
    add_compile_definitions(BOXERUI_CUDA=\"HAVE_CUDA\")
endif()