#include "BoxerUI_Model.h"

#if _WIN32
//TODO: Complete impl of windows threads
DWORD WINAPI camProcThread(LPVOID lpParam)
{
	std::cout << "Thread Running..." << std::endl;

	return 0;
}
#endif // _WIN32

double BoxerUI_Model::getTemperature()
{
	return BoxerUI_Model::temperature;
}
double BoxerUI_Model::getBattery()
{
	return BoxerUI_Model::battery;
}
void BoxerUI_Model::setTemperature(double temperature)
{
	this->BoxerUI_Model::temperature = temperature;
}
void BoxerUI_Model::setBattery(double battery)
{
	this->BoxerUI_Model::battery = battery;
}
void BoxerUI_Model::inputHandler() {//InputType input_type=InputType::None) {

	//ImGui::Begin("##input");

	input.keyboardInputHandler();

	//ImGui::End();
}

void* BoxerUI_Model::cameraPayloadRecv(void* args)
{ //TODO Receive frames from socket here and create a buffer for it

	cv::Mat iptr;
	//*iptr=(cv::Mat*)malloc(sizeof(args));
	//*iptr=*(cv::Mat*)args;
	//*iptr = (cv::Mat *)malloc(sizeof(cv::Mat[5]));
	//*iptr=payload;

	cv::VideoCapture vid = cv::VideoCapture(0);
	if (vid.isOpened())
	{
		for (int i = 0; i < 5; i++)
		{
			std::cout << "Camera Opened" << std::endl;
			vid.retrieve(iptr);
		}
		vid.~VideoCapture();
		*(cv::Mat*)args = iptr;
	}

	//pthread_exit(NULL);
	return args;
}

void BoxerUI_Model::cameraStreamProc(CameraMap& cam_map, cv::VideoCapture& vid, int cam_index, bool& cam_stream)
{ // Collect frames from network here and add send to controller to add onto frame buffers in CameraStream::streamCamera()

	cv::Mat input, output;
	std::cout << "Cuda Device info: " << std::endl;
// 	cv::ocl::Device(context.device(0)); 
// UMat img, gray; 
	// cv::cuda::printCudaDeviceInfo(0);

	//cv::Ptr<cv::cudacodec::VideoReader> d_reader = cv::cudacodec::createVideoReader(fname);
	//cv::cuda::GpuMat temp_gpu;
	//cv::cuda::

	{//If camera is open populate the payload_frames queue
		if ((vid).isOpened())
		{
			std::cout << "Camera Opened: " << cam_index << std::endl;
			while (cam_stream)
			{
				if (!cam_map[cam_index].empty())
					cam_map[cam_index].pop();

				while (cam_map[cam_index].size() < 10)
				{
					(vid).read(input);
					//temp_gpu.upload(input);
					//cv::cuda::bilateralFilter(output, input, 30, 100, 100);
					//TODO: Do other work here that requires gpu/cuda
					//temp_gpu.download(output);
					(cam_map)[cam_index].emplace(input);
					input.~Mat();
					output.~Mat();
				}
			}

		}
	}
	//cv::cuda::Stream strm;
	//strm.

	vid.~VideoCapture();
}

void BoxerUI_Model::print(const char* text)
{
	std::cout << text << std::endl;
}