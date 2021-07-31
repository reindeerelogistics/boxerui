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
				count = i;
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
			std::cout << cmd << getConfig().find(desc)->second << std::endl;
		}
	}
}

void BoxerUI_Inputs::joystick(const float* axes, const char* desc, int axes_val, const char* cmd) {
	std::string NA = "NA";
	if (getConfig().find(desc)->second != NA) {

		if (axes[axes_val] > 0.1 || axes[axes_val] < -0.1) {

			std::cout << cmd << getConfig().find(desc)->second << " Value " << -axes[axes_val] << " Max " << 1 << " Min " << -1 << " Zero " << 0 << std::endl; // range -1-1

		}
	  }
}

void BoxerUI_Inputs::trigger(const float* axes, const char* desc, int axes_val, const char* cmd) {
	std::string NA = "NA";
	if (getConfig().find(desc)->second != NA) {

		if (axes[axes_val] > -0.9) {

			std::cout << cmd << getConfig().find(desc)->second << " Value " << -axes[axes_val] << " Max " << 1 << " Min " << -1 << " Zero " << 0 << std::endl; // range -1-1

		}
	}
}



/*
void BoxerUI_Inputs::leftJoystick(const float* axes) {
	string NA = "NA";
	if (getConfig().find("LJ")->second != NA) {

		if (axes[1] > 0.1 || axes[1] < -0.1) {

			cout << "Absolute Linear velocity " << getConfig().find("LJ")->second << " Value " << -axes[1] << " Max " << 1 << " Min " << -1 << " Zero " << 0 << endl; // range -1-1

		}
	}
}


void BoxerUI_Inputs::rightJoystick(const float* axes) {
	string NA = "NA";
	if (getConfig().find("RJ")->second != NA) {
		if (axes[2] > 0.1 || axes[2] < -0.1) {
			cout << "Absolute Turn " << getConfig().find("RJ")->second << " Value " << axes[2] << " Max " << 1 << " Min " << -1 << " Zero " << 0 << endl; // range -1-1
		}
	}

}


void BoxerUI_Inputs::leftTrigger(const float* axes) {
	string NA = "NA";
	if (getConfig().find("LT")->second != NA) {
		if (axes[4] > -0.9) {
			cout << "Absolute Linear Aceleration " << getConfig().find("LT")->second << " Value " << axes[4] << " Max " << 1 << " Min " << -1 << " Zero " << 0 << endl; // range 0-2
		}
	}

}

void BoxerUI_Inputs::rightTrigger(const float* axes) {
	string NA = "NA";
	if (getConfig().find("RT")->second != NA) {
		if (axes[5] > -0.9) {
			cout << "Absolute Break force " << getConfig().find("RT")->second << " Value " << axes[5] << " Max " << 1 << " Min " << -1 << " Zero " << 0 << endl;
		}
	}

}


void BoxerUI_Inputs::buttonA(const unsigned char* buttons) {
	string NA = "NA";
	if (getConfig().find("BA")->second != NA) {
		if (GLFW_PRESS == buttons[0])
		{
			cout << "Multi-command " << getConfig().find("BA")->second << endl;
		}
	}

}


void BoxerUI_Inputs::buttonB(const unsigned char* buttons) {


	string NA = "NA";
	if (getConfig().find("BB")->second != NA) {
		if (GLFW_PRESS == buttons[1])
		{
			cout << "Parking Break " << getConfig().find("BB")->second << endl;
		}
	}

}

void BoxerUI_Inputs::buttonX() {
	int buttonCount;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	string NA = "NA";
	if (getConfig().find("BX")->second != NA) {
		if (GLFW_PRESS == buttons[2])
		{
			cout << "Repeat last command " << getConfig().find("BX")->second << endl;
		}
	}
}

void BoxerUI_Inputs::buttonY() {
	int buttonCount;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	string NA = "NA";
	if (getConfig().find("BY")->second != NA) {
		if (GLFW_PRESS == buttons[3])
		{
			cout << getConfig().find("BY")->second << endl;
		}
	}
}

void BoxerUI_Inputs::buttonLB() {
	int buttonCount;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	string NA = "NA";
	if (getConfig().find("LB")->second != NA) {
		if (GLFW_PRESS == buttons[4])
		{
			cout << getConfig().find("LB")->second << endl;
		}
	}

}

void BoxerUI_Inputs::buttonRB() {
	int buttonCount;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	string NA = "NA";
	if (getConfig().find("RB")->second != NA) {
		if (GLFW_PRESS == buttons[5])
		{
			cout << getConfig().find("RB")->second << endl;
		}
	}
}

void BoxerUI_Inputs::buttonB7() {
	int buttonCount;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	string NA = "NA";
	if (getConfig().find("B7")->second != NA) {
		if (GLFW_PRESS == buttons[6])
		{
			cout << getConfig().find("B7")->second << endl;
		}
	}
}

void BoxerUI_Inputs::buttonB8() {
	int buttonCount;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	string NA = "NA";
	if (getConfig().find("B8")->second != NA) {
		if (GLFW_PRESS == buttons[7])
		{
			cout << getConfig().find("B8")->second << endl;
		}
	}
}

void BoxerUI_Inputs::buttonUp() {
	int buttonCount;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	string NA = "NA";
	if (getConfig().find("BU")->second != NA) {
		if (GLFW_PRESS == buttons[10])
		{
			cout << getConfig().find("BU")->second << endl;
		}
	}
}

void BoxerUI_Inputs::buttonRight() {
	int buttonCount;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);
	string NA;
	if (getConfig().find("BR")->second != NA) {
		if (GLFW_PRESS == buttons[11])
		{
			cout << getConfig().find("BR")->second << endl;
		}
	}

}

void BoxerUI_Inputs::buttonDown() {
	int buttonCount;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	string NA = "NA";
	if (getConfig().find("BD")->second != NA) {
		if (GLFW_PRESS == buttons[12])
		{
			cout << getConfig().find("BD")->second << endl;
		}
	}
}

void BoxerUI_Inputs::buttonLeft() {
	int buttonCount;
	const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &buttonCount);

	string NA = "NA";
	if (getConfig().find("BL")->second != NA) {
		if (GLFW_PRESS == buttons[13])
		{
			cout << getConfig().find("BL")->second << endl;
		}
	}
}
*/
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


		/*
		buttonA(buttons);
		buttonX();
		buttonB(buttons);
		buttonY();
		buttonLB();
		buttonRB();
		buttonB7();
		buttonB8();
		buttonUp();
		buttonRight();
		buttonDown();
		buttonLeft();
		*/
		//trigger and joystick
		joystick(axes, "LJ", 1, "Linear V");//LJ
		joystick(axes, "LJ", 2, "Turn");//RJ
		trigger(axes, "LT", 4, "Accerlate");//LT
		trigger(axes, "RT", 5, "Break");//RT
		/*
		leftJoystick(axes);
		rightJoystick(axes);
		leftTrigger(axes);
		rightTrigger(axes);
		*/
		const char* name = glfwGetJoystickName(GLFW_JOYSTICK_1);
		//cout << name << endl;
	}
}