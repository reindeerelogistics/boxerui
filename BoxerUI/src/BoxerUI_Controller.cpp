#include "BoxerUI_Controller.h"
//#include "Networking/socketLibrary.cpp"
bool CameraStream::show_camera = false;

double BoxerUI_Controller::getModelBattery()
{
	return boxerModel.getBattery();
}
double BoxerUI_Controller::getModelTemperature()
{
	return boxerModel.getTemperature();
}
void BoxerUI_Controller::setModelBattery(double batteryVal)
{
	boxerModel.setBattery(batteryVal);
}
void BoxerUI_Controller::setModelTemperature(double temperatureVal)
{
	boxerModel.setTemperature(temperatureVal);
}
void BoxerUI_Controller::inputHandlerModel()
{
	boxerModel.inputHandler();
}

void BoxerUI_Controller::cameraPayloadRecv()
{
	//TODO: Call to socket function to receive frame buffers, send to model for processing

	//camera_stream.setCamContext();
	//boxerModel.cameraStreamProc();
}
void BoxerUI_Controller::decomposePayload(Json::Value jsonPayload)
{
	// converts json to model data attributes
	boxerModel.setBattery(3);	  //jsonPayload["Battery"].asDouble());
	boxerModel.setTemperature(5); //jsonPayload["Temperature"].asDouble());
}
void BoxerUI_Controller::displayIndexWindow(bool* boxer_analytics)
{											//,int ui_width,int ui_height) {
	boxerView.indexwindow(boxer_analytics); // , ui_width, ui_height);
}
void BoxerUI_Controller::displayFPS()
{
	boxerView.appFrameRate();
}
void BoxerUI_Controller::demoWindows()
{						   //bool demo_window) {
	boxerView.showdemos(); // &demo_window);
}
void BoxerUI_Controller::updateBSView()
{
	//boxerView.displaySensors(boxerModel.getTemperature(), boxerModel.getBattery());
}
void BoxerUI_Controller::plotView()
{
	//boxerSocket.payloadRecv(4, *"payload", 0);
	boxerView.plotStream();
}
void BoxerUI_Controller::navView()
{
	boxerView.sideNav();
}

void BoxerUI_Controller::indexView()
{
	boxerView.indexView();
}

cv::Mat procCam(cv::VideoCapture vid, cv::Mat& temp)
{ //, std::vector<cv::Mat> payload) {

	//if (is_camera_on)

	//static  = std::vector<cv::Mat>(5);
	//vid = ;
	//cap = true;
	static bool x = true;
	//std::vector<cv::Mat> load= std::vector<cv::Mat>(5);// = f.get();
	//cv::VideoCapture vid = cv::VideoCapture(1);;
	//cam_mutex.lock();
	if (vid.isOpened())
	{
		std::cout << "Camera Opened" << std::endl;
		//std::unique_lock<std::mutex> guard(cam_mutex);
		// , std::defer_lock);

		//for (int i = 0; i < 5; i++)
		{

			std::cout << "Camera retrieve" << std::endl;
			//std::unique_lock<std::mutex> guard(cam_mutex);
			(vid).retrieve(temp);
			//load[i]=(temp);
		}
		//guard.unlock();
	}

	//vid.~VideoCapture();
	//cam_mutex.unlock();
	return temp;
}
//std::mutex m;
void BoxerUI_Controller::cameraView()
{
	static bool x = true;


	if (x)
	{
		x = false;
#ifndef _WIN32
		serveraddr.sin_family = AF_INET;
		serveraddr.sin_port = htons(8000);
		serveraddr.sin_addr.s_addr = inet_addr("0.0.0.0");
#endif // !_WIN32
	}
	static bool cam_thread_init = true;
	if (camera_stream.show_camera)
	{

		if (cam_thread_init)
		{
			cam_thread_init = false;
			int i = 0;

			std::queue<cv::Mat> temp;
			for (cv::VideoCapture& var : camera_stream.vid_captures)
			{
				var = cv::VideoCapture((i == 0 ? 1 : 0), cv::CAP_DSHOW);
				//var = cv::VideoCapture(1, cv::CAP_DSHOW);
				//var.set(cv::CAP_PROP_FPS, 30.0);

				(camera_stream.payload_frames).insert({ i,temp });// = temp;
				i++;
			}

			for (size_t i = 0; i < (camera_stream.payload_frames).size(); i++)
			{//vector of threads based on camera size

				camera_stream.cam_threads.push_back(std::thread(boxerModel.cameraStreamProc, std::ref(camera_stream.payload_frames), std::ref(camera_stream.vid_captures[i]), (i), std::ref(camera_stream.show_camera)));
				//boxerModel.cameraStreamProc(std::ref(camera_stream.payload_frames), std::ref(camera_stream.vid_captures[i]), (i), std::ref(camera_stream.show_camera));
			}
		}
	}
	else {
		for (size_t i = 0; i < camera_stream.cam_threads.size(); i++)
		{
			//m.lock();
			std::thread& t = camera_stream.cam_threads[i];
			if (t.joinable()) {
				std::cout << "Thread ID: " << t.get_id() << " joined successfully" << std::endl;
				t.join();
				camera_stream.cam_threads.erase(camera_stream.cam_threads.begin() + i);
			}
			//m.unlock();
		}
		camera_stream.payload_frames.clear();
		cam_thread_init = true;
	}

	//struct FrameStructure Overhead = recvFrameOverhead(sockfd, serveraddr);
	//int rows = Overhead.rows;
	//int cols = Overhead.cols;
	//cv::Mat temp = recvFrame(sockfd, serveraddr);
	//cv::Mat* temp2 = &temp;
	//camera_stream.initCamera(temp2);
	camera_stream.initCamera();
	}