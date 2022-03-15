#include "CameraStream_Model.h"

#if defined(HAVE_CUDA)
cv::Mat CameraStream_Model::cudaStreamProc(cv::Mat& input)
{
	//https://stackoverflow.com/questions/17842827/how-to-use-gpustream-in-opencv
	//cv::cuda::DeviceInfo dev_info(0);

	////cv::Ptr<cv::cudacodec::VideoReader> d_reader = cv::cudacodec::createVideoReader(fname);

	//// allocate page-locked memory
	//cv::cuda::HostMem host_src_pl(768, 1024, CV_8UC1, cv::cuda::HostMem::AllocType::PAGE_LOCKED);
	//cv::cuda::HostMem host_dst_pl;

	// get Mat header for CudaMem (no data copy)
	//cv::Mat host_src = host_src_pl;
	//cv::Ptr<cv::cuda::CannyEdgeDetector> canny_edg = cv::cuda::createCannyEdgeDetector(2.0, 100.0, 3, false);

	// create Stream object
	cv::cuda::Stream* cuda_stream{}; // stream_callback();

	static cv::cuda::GpuMat gpu_input, gpu_output;
	cv::Mat output; // (gpu_output);

	/*cv::cuda::cvtColor(input, input, cv::COLOR_BGR2GRAY);
	cv::cuda::bilateralFilter(gpu_input, gpu_output, -1, 50, 7);
	canny_edg->detect(gpu_input, gpu_output, cuda_stream);*/

	gpu_input.upload(input); //, *cuda_stream);
	//cv::cuda::blur(gpu_input, gpu_output, cv::Size(5, 5), cv::Point(-1, -1), cuda_stream);
	cv::cuda::bilateralFilter(gpu_input, gpu_input, 30, 100, 100);
	//cv::cuda::threshold(gpu_input, gpu_input, 128.0, 255.0, cv::THRESH_BINARY);
	gpu_input.download(output); //Use download if mat object requires modification

	gpu_input.~GpuMat();
	gpu_output.~GpuMat();

	return output;
}

//https://stackoverflow.com/a/47483001
//use cv2.goodFeaturesToTrack to find good corners.
//use cv2.calcOpticalFlowPyrLK to track the corners.
//use cv2.findHomography to compute the homography matrix.
//use cv2.warpPerspective to transform video frame.
void CameraStream_Model::camStab(cv::Mat& input)
{
	cv::cuda::Stream stab_stream;
	cv::cuda::cvtColor(input, input, cv::COLOR_BGR2GRAY, 8, stab_stream);
}
#elif defined(HAVE_OPENMP)

void CameraStream_Model::ompStreamProc(CameraMap& cam_map, std::vector<cv::VideoCapture>& vid, int cam_index, bool& cam_stream)
{

	// omp:: omp_set_num_threads(cam_index);
#pragma omp parallel// sections for nowait
	{
		//#pragma omp parallel section
		//		{
		//			//Do work that requires omp here
		//		}
	}
}
#endif

void CameraStream_Model::boxerStreamProc()
{
	cv::cuda::resetDevice();
}

void CameraStream_Model::cameraPayloadRecv(CameraMap& cam_map, cv::VideoCapture& vid, int cam_index, bool& cam_stream)
{ //WIP Receive frames from socket here and create a buffer for it
	cv::Mat input = cv::Mat(100, 100, CV_8UC1), output;
	int i = 0;
	//cv::cudacodec::createVideoWriter();
		//If camera is open populate the payload_frames queue
	if ((vid).isOpened())
	{
		std::cout << "Camera Opened: " << cam_index << std::endl;
		while (cam_stream)
		{
			if (cam_map[cam_index].size() < 10)
			{
				(vid).read(input);
				//TODO: All module work are done here

				//output=CameraStream_Model::cudaStreamProc(input);

				(cam_map)[cam_index].emplace(input);
			}
			else
			{
				cam_map[cam_index].pop();

				//std::cout << "Popped at cam index: " << cam_index << "\t\tnum of pops"<<i++ <<"\t\tsize of queue: " << cam_map[cam_index].size() << std::endl;
			}

		}
		input.~Mat();
		output.~Mat();

	}

	vid.~VideoCapture();

}

//void CameraStream_Model::cameraPayloadRecv(CameraMap& cam_map, cv::VideoCapture& vid, int cam_index, bool& cam_stream)
//{ //WIP Receive frames from socket here and create a buffer for it
//	cv::Mat input = cv::Mat(100, 100, CV_8UC1), output;
//
//	cv::cuda::GpuMat imgGPU;
//
//	//If camera is open populate the payload_frames queue
//	if ((vid).isOpened())
//	{
//		std::cout << "Camera Opened: " << cam_index << std::endl;
//		while (cam_stream)
//		{
//			if (cam_map[cam_index].size() < 10)
//			{
//				(vid)>>(input);
//				imgGPU.upload(input);
//				//TODO: All module work are done here
//				auto start = cv::getTickCount();
//				cv::cuda::bilateralFilter(imgGPU, imgGPU, 30, 100, 100);
//				auto end = cv::getTickCount();
//
//				auto totalTime = (end - start) / cv::getTickFrequency();
//				auto fps = 1 / totalTime;
//				std::cout << "FPS: " << fps << std::endl;
//
//				//cv::putText(input, "FPS: "+std::to_string(int(fps)),cv::Point(50,50),cv::FONT_HERSHEY_DUPLEX,1, cv::Scalar(0,255,))
//
//				//output=CameraStream_Model::cudaStreamProc(input);
//				imgGPU.download(input);
//				(cam_map)[cam_index].emplace(input);
//			}
//			else
//			{
//				cam_map[cam_index].pop();
//			}
//
//		}
//		input.~Mat();
//		output.~Mat();
//
//	}
//
//	vid.~VideoCapture();
//
//}