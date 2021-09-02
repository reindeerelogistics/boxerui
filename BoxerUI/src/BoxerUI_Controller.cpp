#include "BoxerUI_Controller.h"
//#include "Networking/socketLibrary.cpp"

BoxerUI_Controller::~BoxerUI_Controller()
{
	//destructor for the controller. Should be called before exiting the program to free memory and delete variables from heap
	//camera_stream.~CameraStream();
	
}

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
//void BoxerUI_Controller::decomposePayload(Json::Value jsonPayload)
//{
//	// converts json to model data attributes
//	boxerModel.setBattery(3);	  //jsonPayload["Battery"].asDouble());
//	boxerModel.setTemperature(5); //jsonPayload["Temperature"].asDouble());
//}
void BoxerUI_Controller::displayIndexWindow(bool* boxer_analytics)
{
	boxerView.indexwindow(boxer_analytics);
}
void BoxerUI_Controller::displayFPS()
{
	boxerView.appFrameRate();
}
void BoxerUI_Controller::demoWindows() {
	boxerView.showdemos(); // &demo_window);
}
void BoxerUI_Controller::updateBSView()
{
	//boxerView.displaySensors(boxerModel.getTemperature(), boxerModel.getBattery());
}
void BoxerUI_Controller::plotView()
{
	boxerView.plotStream();
}
void BoxerUI_Controller::navView()
{
	boxerView.sideNav();
}

void BoxerUI_Controller::indexView()
{
	if (!camera_stream.show_camera)
	{
		boxerView.indexView();
	}
}

void BoxerUI_Controller::cameraView()
{
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
				//var.set(cv::CAP_PROP_FRAME_WIDTH, 80);
				//var.set(cv::CAP_PROP_FRAME_HEIGHT,90);
				//std::cout<<"Cam is opened? "<<var.isOpened();
				//var = cv::VideoCapture();

				(camera_stream.payload_frames).insert({ i,temp });
				i++;
			}

			for (size_t i = 0; i < (camera_stream.vid_captures).size(); i++)
			{
				//vector of threads based on camera size
				camera_stream.cam_threads.emplace_back(std::thread(boxerModel.cameraPayloadRecv, std::ref(camera_stream.payload_frames), std::ref(camera_stream.vid_captures[i]), (i), std::ref(camera_stream.show_camera)));
			}
		}
	}
	else if (!camera_stream.cam_threads.empty() && !camera_stream.show_camera)
	{
		std::cout << "Num of active threads: " << camera_stream.cam_threads.size() << std::endl;
		for (size_t i = 0; i < camera_stream.cam_threads.size(); i++)
		{
			std::thread& t = camera_stream.cam_threads[i];
			if (t.joinable()) {
				std::cout << "Thread ID: " << t.get_id() << " joined successfully" << std::endl;
				t.join();
				//camera_stream.cam_threads.erase(camera_stream.cam_threads.begin() + i);
			}
		}
		camera_stream.cam_threads.clear();
		std::cout << "Num of active threads after joining: " << camera_stream.cam_threads.size() << std::endl;
		//if (CameraStream_Model::destroyCamThreads(&camera_stream.cam_threads))
		{
			//camera_stream.~CameraStream();
			camera_stream.payload_frames.clear();
			cam_thread_init = true;
		}
	}

	camera_stream.initCamera();
}