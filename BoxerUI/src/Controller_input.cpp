#include "Controller_input_Header.h"
//using namespace std;



int main(void)
{


	//library
	if (!glfwInit())
	{
		return -1;
	}


	while (true)
	{

		BoxerUI_Inputs::input();
		glfwPollEvents();

	}

	glfwTerminate();

	return 0;
}
std::string BoxerUI_Inputs::split(std::string target, bool dir, char delim) {

	if (dir == 0) {

		std::string result;
		for (int i = 0; i < target.length(); i++) {

			if (target[i] != delim) {
				result += target[i];
			}
			else {
				return result;
			}
		}
	}
	//right
	else {

		std::string result;
		int count = 0;
		for (int i = 0; i < target.length(); i++) {
			if (target[i] == delim) {
				count = i+1;
			}
		}
		for (int i = count; i < target.length(); i++) {
			result += target[i];
		}
		return result;
	}
}
std::map<std::string, std::string> BoxerUI_Inputs::getConfig() {
	std::string filename = "Confige.txt";
	std::ifstream input;

	input.open(filename);

	if (!input.is_open()) {
		std::cout << "file is occupied" << std::endl;
	}

	std::map<std::string, std::string> config;
	std::string line;
	while (getline(input, line)) {

		config.insert(std::pair<std::string, std::string>(split(line, 0, ':'), split(line, 1, ':')));
	}

	input.close();
	return config;
}
void BoxerUI_Inputs::button(const unsigned char* buttons, const char* desc, int button_val, const char* cmd) {
	std::string NA = "NA";

	if (getConfig().find(desc)->second != NA) {
		if (GLFW_PRESS == buttons[button_val])
		{
			//std::cout << cmd << getConfig().find(desc)->second << std::endl;
			send(getConfig().find(desc)->second,75,100,-100,0);
		}
	}
}

void BoxerUI_Inputs::joystick(const float* axes, const char* desc, int axes_val, const char* cmd) {
	std::string NA = "NA";
	if (getConfig().find(desc)->second != NA) {

		if (axes[axes_val] > 0.1 || axes[axes_val] < -0.1) {

			//std::cout << cmd << getConfig().find(desc)->second << " Value " << -axes[axes_val] << " Max " << 1 << " Min " << -1 << " Zero " << 0 << std::endl; // range -1-1
			send(getConfig().find(desc)->second, -axes[axes_val],1,-1,0);
		}
		else {
			if (axes[axes_val] > 0.1 || axes[axes_val] < -0.1) {

				//std::cout << cmd << getConfig().find(desc)->second << " Value " << axes[axes_val] << " Max " << 1 << " Min " << -1 << " Zero " << 0 << std::endl; // range -1-1
				send(getConfig().find(desc)->second, axes[axes_val],1,-1,0);

			}
	  }
}


void BoxerUI_Inputs::trigger(const float* axes, const char* desc, int axes_val, const char* cmd) {
	std::string NA = "NA";
	if (getConfig().find(desc)->second != NA) {

		if (axes[axes_val] > -0.95) {

			//std::cout << cmd << getConfig().find(desc)->second << " Value " << -axes[axes_val] << " Max " << 1 << " Min " << -1 << " Zero " << 0 << std::endl; // range -1-1
			send(getConfig().find(desc)->second, -axes[axes_val],1,-1,0);
		}
	}
}

void BoxerUI_Inputs::send(const float* com,const float* data,const float* max,const float* min,const float* zero){
	cmd.set(com,data,max,min,zero);
	cmd.send();
}

void BoxerUI_Inputs::input() {
	glfwWaitEventsTimeout(0.2);
	int present = glfwJoystickPresent(GLFW_JOYSTICK_1);

	/*
	static bool button_init = true;

	if (button_init) {
		button_init = false;

		button_map{
			{Button::btnA,"BA"},
			{Button::btnB,"BB"},
			//{Button::btnc,"BB"},
		}
	}
	*/
	if (1 == present)
	{
		int axesCount;
		int buttonCount;

		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);


		//buttons

		button(buttons, "BA", 0, "Multi command");//Button A
		button(buttons, "BB", 1, "button B");
		button(buttons, "BY", 2, "button Y");
		button(buttons, "LB", 3, "button LB");
		button(buttons, "RB", 4, "button RB");
		button(buttons, "B7", 5, "button 7");
		button(buttons, "B8", 6, "button 8");
		button(buttons, "BU", 10, "button UP");
		button(buttons, "BR", 11, "button Right");
		button(buttons, "BD", 12, "button Down");
		button(buttons, "BL", 13, "button Left");


		
		//trigger and joystick
		joystick(axes, "LJ", 1, "Linear V");//LJ
		joystick(axes, "LJ", 2, "Turn");//RJ
		trigger(axes, "LT", 4, "Accerlate");//LT
		trigger(axes, "RT", 5, "Break");//RT
		
		const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
		//cout << name << endl;
	}
}