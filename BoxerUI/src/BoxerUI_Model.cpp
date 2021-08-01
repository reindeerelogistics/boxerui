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
void BoxerUI_Model::inputHandler(){//InputType input_type=InputType::None) {
	
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


CameraMap BoxerUI_Model::cameraStreamProc(std::shared_future<CameraMap> f, std::vector<cv::VideoCapture>& vid, bool& is_camera_on)
{ // Collect frames from network here and add send to controller to add onto frame buffers in CameraStream::streamCamera()
	CameraMap cam_map = f.get();

	if (is_camera_on)
	{//If camera is open populate the payload_frames vector
		auto start = std::chrono::high_resolution_clock::now();

		for (int j = 0; j < 5; j++)
		{
			if ((vid)[j].isOpened())
			{
				std::cout << "Camera Opened" << std::endl;

				(vid)[j].retrieve(cam_map[j][0]);
			}

		}

		auto stop = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

		// To get the value of duration use the count()
		// member function on the duration object
		std::cout << "In model: " << duration.count() << std::endl;
	}

	return cam_map;
}

void BoxerUI_Model::print(const char* text)
{
	std::cout << text << std::endl;
}