#include "CameraStream_Model.h"


void CameraStream_Model::cudaStreamProc(cv::Mat& input) {
	
	//cv::cuda::printCudaDeviceInfo(0);
	//cv::cuda::printShortCudaDeviceInfo(0);

	//cv::cuda::DeviceInfo dev_info(0);

	std::cout << "NUM of CUDA enabled devices: " << cv::cuda::getCudaEnabledDeviceCount() << std::endl;

	//cv::Ptr<cv::cudacodec::VideoReader> d_reader = cv::cudacodec::createVideoReader(fname);
	//cv::cuda::GpuMat temp_gpu;
	//cv::cuda::

	// allocate page-locked memory
	cv::cuda::HostMem host_src_pl(768, 1024, CV_8UC1, cv::cuda::HostMem::AllocType::PAGE_LOCKED);
	cv::cuda::HostMem host_dst_pl;

	// get Mat header for CudaMem (no data copy)
	//cv::Mat host_src = host_src_pl;
	cv::Mat  output;

	// fill mat on CPU
	//cv::cuda::someCPUFunc(host_src);

	cv::cuda::GpuMat gpu_input, gpu_dst;

	// create Stream object
	//cv::cuda::Stream::StreamCallback stream_callback ();


	//cv::cuda::Event event;


	// next calls are non-blocking

	// first upload data from host
	//stream.enqueueHostCallback(host_src_pl, gpu_src);
	// perform blur

	gpu_input.upload(input);// , stream);
	//cv::cuda::bilateralFilter(gpu_input, gpu_input, 30, 100, 100);
	cv::cuda::threshold(gpu_input, gpu_input, 128.0, 255.0, cv::THRESH_BINARY);
	gpu_input.download(output); //Use download if mat object requires modification

	input.~Mat();
	output.~Mat();
	gpu_input.~GpuMat();

	//if (stream.queryIfComplete())
	//{
	////stream.enqueueHostCallback(stream_callback, &gpu_input);
	//		stream.waitForCompletion();
	//}


//cv::cuda::blur(gpu_src, gpu_dst, Size(5, 5), Point(-1, -1), stream);
// download result back to host
//stream.(gpu_dst, host_dst_pl);

// call another CPU function in parallel with GPU



// wait GPU for finish


}

void CameraStream_Model::ompStreamProc(CameraMap& cam_map, std::vector<cv::VideoCapture>& vid, int cam_index, bool& cam_stream) {

	omp_set_num_threads(cam_index);
#pragma omp parallel sections for nowait
	{
#pragma omp parallel section
		{
			for (size_t i = 0; i < cam_index; i++) {
				cv::Mat input, output;
				if ((vid)[i].isOpened())
				{
					std::cout << "Camera Opened: " << cam_index << std::endl;
					while (cam_stream)
					{
						if (!cam_map[cam_index].empty()) {
							cam_map[cam_index].pop();
						}
						while (cam_map[cam_index].size() < 10)
						{

							//else
							{
								//cv::cuda::Stream stream;
								(vid)[i].read(input);
								//gpu_input.upload(input);// , stream);
								//cv::cuda::bilateralFilter(gpu_input, gpu_input, 30, 100, 100);
								//cv::cuda::threshold(gpu_input, gpu_input, 128.0, 255.0, cv::THRESH_BINARY);
								//gpu_input.download(output);
								(cam_map)[cam_index].emplace(input);
								//gpu_input.download(); Use download if mat object requires modification
								input.~Mat();
								output.~Mat();
								//gpu_input.~GpuMat();
							}
						}
					}
				}
			}
		}
	}

}

//void CameraStream_Model::boxerStreamProc() {

//}
