#pragma once

#include "Boxer.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <map>
#include <queue>
#include <future>
#include <chrono>
#include <algorithm>
#include "opencv2/core/cuda.hpp"
#include <opencv2/core/core.hpp>
#include <mutex>
#include <thread>

#include <opencv2/core.hpp>
#include <opencv2/core/opengl.hpp>

#include <opencv2/highgui.hpp>

#ifdef _WIN32

#include <Windows.h>
#include <iostream>
#else
#include <stdio.h>
#include <pthread.h>

#endif // headers for threads

//using namespace std::this_thread
#ifndef _INPUTS_H
//#define _INPUTS_H
#include "Inputs_Model.h"
#endif

using namespace std::chrono_literals;
using CameraMap = std::map <int, std::queue<cv::Mat >>;

class BoxerUI_Model
{
private:
	double temperature, battery;// , ultrasonic;
	Inputs input;
	static void* cameraPayloadRecv(void* arg);

	

public:
	double getTemperature();
	double getBattery();
	void setTemperature(double temperature);
	void setBattery(double battery);
	void inputHandler();
	
	 //static CameraMap cameraStreamProc(std::shared_future<CameraMap> f, std::vector<cv::VideoCapture>& vid, bool& is_camera_on);
	 static void cameraStreamProc(CameraMap& f, cv::VideoCapture& vid, int cam_index,bool& cam_stream);

protected:
	void print(const char* text);
};
