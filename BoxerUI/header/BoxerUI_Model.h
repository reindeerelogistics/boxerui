#pragma once

#include "Boxer.h"
#include "Boxerpch.h"
// #include "CameraStream_Model.h"

// #include "opencv2/core/cuda.hpp"
// #include <opencv2/core.hpp>
// #include <opencv2/cudaimgproc.hpp>

//#include <opencv2/cudacodec.hpp>
//#include <opencv2/cudaarithm.hpp>
//#include <opencv2/cudabgsegm.hpp>
//#include <opencv2/cudaimgproc.hpp>
//#include <opencv2/core/opengl.hpp>

#ifndef _INPUTS_H
//#define _INPUTS_H
#include "Inputs_Model.h"
#endif

//using namespace std::chrono_literals;
using CameraMap = std::map <int, std::queue<cv::Mat >>;
class BoxerUI_Model
{
private:
	double temperature, battery;// , ultrasonic;
	Inputs input;

public:
	double getTemperature();
	double getBattery();
	void setTemperature(double temperature);
	void setBattery(double battery);
	void inputHandler();

	static void cameraPayloadRecv(CameraMap& cam_map, cv::VideoCapture& vid, int cam_index, bool& cam_stream);
protected:
	void print(const char* text);
};
