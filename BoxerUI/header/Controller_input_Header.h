#pragma once

#include "../libs/imgui/examples/libs/gl3w/GL/gl3w.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <cstdlib>
#include "../src/RoboCMD/RoboCMD.cpp"
#include <sstream>
#include <string>


/*
enum class Buttons {
	btnA = 0,
	btnB = 1,
};
*/
namespace BoxerUI_Inputs {

	//map<Buttons,const char*> button_map;

	std::string split(std::string target, bool dir, char delim);
	std::map<std::string, std::string> getConfig();

	
	
	void button(const unsigned char* buttons, const char* desc, int button_val);
	void joystick(const float* axes, const char* desc, int axes_val);
	void trigger(const float* axes, const char* desc, int axes_val);
	void input();
	void send(const float com,const float data,const float max,const float min,const float zero);
	

}
