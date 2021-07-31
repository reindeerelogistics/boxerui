#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>

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

	
	/*
	extern void leftJoystick(const float* axes);
	extern void rightJoystick(const float* axes);
	extern void leftTrigger(const float* axes);
	extern void rightTrigger(const float* axes);
	extern void buttonA(const unsigned char* buttons);
	extern void buttonB(const unsigned char* buttons);
	extern void buttonX();
	extern void buttonY();
	extern void buttonLB();
	extern void buttonRB();
	extern void buttonB7();
	extern void buttonB8();
	extern void buttonUp();
	extern void buttonRight();
	extern void buttonDown();
	extern void buttonLeft();
	extern void input();
	*/
	void button(const unsigned char* buttons, const char* desc, int button_val,  const char* cmd );
	void joystick(const float* axes, const char* desc, int axes_val, const char* cmd);
	void trigger(const float* axes, const char* desc, int axes_val, const char* cmd);
	void input();
}
