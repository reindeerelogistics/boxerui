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

void BoxerUI_Controller::views()
{
	boxerView.sideNav();
}

void BoxerUI_Controller::cameraView()
{
	
}