#pragma once

#include <omp.h>
#include <opencv2/opencv.hpp>
#include "opencv2/core/cuda.hpp"
#include <opencv2/core.hpp>
#include <opencv2/cudaimgproc.hpp>

#include <opencv2/core.hpp>
#include <opencv2/cudacodec.hpp>
#include <opencv2/cudaarithm.hpp>
#include <opencv2/cudabgsegm.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/core/opengl.hpp>

using CameraMap = std::map <int, std::queue<cv::Mat >>;
#define HAVE_CUDA
#define _OPENMP
namespace CameraStream_Model
{
//	void streamWorker() {
//
//		if (cv::cuda::getCudaEnabledDeviceCount() > 0)
//		{
//#
//			//cv::cuda::printCudaDeviceInfo(0);
//			cv::cuda::printShortCudaDeviceInfo(0);
//
//			//cv::cuda::DeviceInfo dev_info(0);
//
//			//std::cout << "NUM of CUDA enabled devices: " << cv::cuda::getCudaEnabledDeviceCount() << std::endl;
//
//			//cv::Ptr<cv::cudacodec::VideoReader> d_reader = cv::cudacodec::createVideoReader(fname);
//			//cv::cuda::GpuMat temp_gpu;
//			//cv::cuda::
//		}
//	}

#if defined(HAVE_CUDA)
	
	static void cudaStreamProc(cv::Mat& cuda_mat);

#endif

#if defined(_OPENMP)

	void ompStreamProc(CameraMap& cam_map, std::vector<cv::VideoCapture>& vid, int cam_index, bool& cam_stream);

#endif

#if !defined(_OPENMP) && !defined(HAVE_CUDA)
	void boxerStreamProc();
#endif
};

