#include "BoxerUI_Model.h"

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

	input.keyboardInputHandler();
}

void BoxerUI_Model::cameraPayloadRecv(CameraMap& cam_map, cv::VideoCapture& vid, int cam_index, bool& cam_stream)
{ //WIP Receive frames from socket here and create a buffer for it
	cv::Mat input, output;
	std::cout << "Cuda Device info: " << std::endl;
	

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
					//TODO: All module work are done here


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
