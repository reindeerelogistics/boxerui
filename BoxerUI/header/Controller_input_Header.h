#pragma once

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include "RoboCMD/RoboCMD.cpp"

#include <string>


/*
enum class Buttons {
	btnA = 0,
	btnB = 1,
};
*/
namespace BoxerUI_Inputs {
	//map<Buttons,const char*> button_map;
RoboCMD <float,float,float,float> cmd;

	std::string split(std::string target, bool dir, char delim);
	std::map<std::string, std::string> getConfig();

	
	
	void button(const unsigned char* buttons, const char* desc, int button_val,  const char* cmd );
	void joystick(const float* axes, const char* desc, int axes_val, const char* cmd);
	void trigger(const float* axes, const char* desc, int axes_val, const char* cmd);
	void input();
	void send(const float com,const float data,const float max,const float min,const float zero);
	

}
