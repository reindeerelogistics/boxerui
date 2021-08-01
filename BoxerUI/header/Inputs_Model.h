#pragma once
#include "Boxer.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

enum class InputType  {//same as an enum but with a scope
	None		,
	Keyboard	,
	Gamepad		,
	Joystick	,
	Touch		
};

class Inputs
{

private:

	
	void gamepadInputHandler();
	void joystickInputHandler();
	void touchInputHandler();
	void noInputHandler();
	
public:
	//void inputHandler();
void keyboardInputHandler();
};
 //extern // = InputType::None;
//static ImGuiIO& io = ImGui::GetIO();


