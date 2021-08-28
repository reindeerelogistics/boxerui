#pragma once

#include "Boxer.h"
#include "CameraStream_Model.h"

#include <map>
#include <queue>
#include <chrono>
#include <algorithm>


#include <mutex>
#include <thread>

#include <iostream>

#ifndef _INPUTS_H
//#define _INPUTS_H
#include "Inputs_Model.h"
#endif

//using namespace std::chrono_literals;
//namespace bxr {
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
	//}
};
