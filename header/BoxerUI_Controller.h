#pragma once

#include "BoxerUI_View.h"
#include "BoxerUI_Model.h"
// #include "CameraStream_Model.h"

//#include "jsoncpp/json/json.h"

#ifdef _WIN32

#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#endif
namespace BoxerUI{
class BoxerUI_Controller
{

private:
	BoxerUI_View boxerView;
	BoxerUI_Model boxerModel;


		//static BoxerUI_Controller* boxerController;
public:
	BoxerUI_Controller()
		: boxerView(), boxerModel()		//Creates member instances
	{}

	/*static BoxerUI_Controller& Get() {
		return *boxerController;
	}*/

	~BoxerUI_Controller();

public:

	//MODEL
	double getModelBattery();
	double getModelTemperature();
	void setModelBattery(double batteryVal);
	void setModelTemperature(double temperatureVal);
	//void decomposePayload(Json::Value jsonPayload);
	void inputHandlerModel();//INPUT_MODEL

	//VIEW
	void displayFPS();
	void demoWindows();
	void updateBSView();
	void plotView();
	void views();

	void displayIndexWindow(bool* boxer_analytics);
	void cameraView();
	void indexView();
	void cameraPayloadRecv();
	bool destroyCamThreads();
};
};
