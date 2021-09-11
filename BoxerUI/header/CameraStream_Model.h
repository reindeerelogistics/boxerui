#pragma once
#include "Boxerpch.h"
#include <omp.h>

#include <opencv2/opencv.hpp>
#include "opencv2/core/cuda.hpp"
#include <opencv2/core.hpp>
// #include <opencv2/cudaimgproc.hpp>

// #include <opencv2/cudacodec.hpp>
// #include <opencv2/cudaarithm.hpp>
// #include <opencv2/cudabgsegm.hpp>

using CameraMap = std::map<int, std::queue<cv::Mat>>;

namespace CameraStream_Model
{

#if defined(HAVE_CUDA)

	cv::Mat cudaStreamProc(cv::Mat &cuda_mat);

#elif defined(HAVE_OPENMP)

	void ompStreamProc(CameraMap &cam_map, std::vector<cv::VideoCapture> &vid, int cam_index, bool &cam_stream);

	void camStab(cv::Mat &input);

#endif

	void boxerStreamProc();

void cameraPayloadRecv(CameraMap& cam_map, cv::VideoCapture& vid, int cam_index, bool& cam_stream);
};
