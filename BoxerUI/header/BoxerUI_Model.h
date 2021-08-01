#pragma once

#include "Boxer.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <map>
#include <vector>
#include <future>
#include <chrono>
#include <algorithm>


#ifdef _WIN32

#include <Windows.h>
#include <iostream>
#else
#include <stdio.h>
#include <pthread.h>

#endif // headers for threads


#ifndef _INPUTS_H
//#define _INPUTS_H
#include "Inputs_Model.h"
#endif

using CameraMap = std::map <int, std::vector<cv::Mat >>;

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
	
	 static CameraMap cameraStreamProc(std::shared_future<CameraMap> f, std::vector<cv::VideoCapture>& vid, bool& is_camera_on);

protected:
	void print(const char* text);
};
