#pragma once


#include "BoxerUI_View.h"
#include "BoxerUI_Model.h"
#include "CameraStream_View.h"

#include "jsoncpp/json/json.h"
#include <fstream>
#include <iostream>
#include <string>
#include <future>
#include <thread>
#include <chrono>
#include <algorithm>

#ifdef _WIN32

#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif

class BoxerUI_Controller
{
	/*BoxerUI_Controller(BoxerUI_View boxerView, BoxerUI_Model boxerModel) {
		this->boxerModel = boxerModel;
		this->boxerView = boxerView;
	}*/

	/*BoxerUI_Controller(ImFont fonts) {
		this->boxerfonts = fonts;
	}*/
	
private:
	
	BoxerUI_View boxerView;// = BoxerUI_View(boxerfonts);
	BoxerUI_Model boxerModel;
	CameraStream camera_stream;
#ifndef _WIN32
struct sockaddr_in serveraddr;
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
#endif // !_WIN32

public:	

	cv::Mat current_frame = cv::Mat(100, 100, CV_8UC4);
	
	//MODEL
	double getModelBattery();
	double getModelTemperature();
	void setModelBattery(double batteryVal);
	void setModelTemperature(double temperatureVal);
	void decomposePayload(Json::Value jsonPayload);
	void inputHandlerModel();//INPUT_MODEL
	
	//VIEW
	void displayFPS();
	void demoWindows();
	void updateBSView();
	void plotView();
	void navView();

	void displayIndexWindow(bool *boxer_analytics);
	void cameraView();
	void indexView();
	void cameraPayloadRecv();
};
