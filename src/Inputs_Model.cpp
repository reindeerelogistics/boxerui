#include "Inputs_Model.h"
#include <iostream>
using namespace std;

//void Inputs::inputHandler() {
//	
//
//	switch (input_type) {
//	case InputType::Gamepad:
//		gamepadInputHandler();
//		break;
//	case InputType::Joystick:
//		joystickInputHandler();
//		break;
//	case InputType::Touch:
//		touchInputHandler();
//		break;
//	case InputType::Keyboard:
//		keyboardInputHandler();
//		break;
//	default:
//		noInputHandler();
//		//keyboardInputHandler();
//	}
//
//	//endFrame();
//	//beginFrame();//i.e. reload the frame to consider the input
//	
//	
//
//}
void Inputs::keyboardInputHandler() {
	//cout << "input_type" << endl;
	//ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	
	io.NavActive = true;

	//io.KeysDown[];
	//if IsWindowFocused(ImGuiFocusedFlags_AnyWindow)
	
	//if(ImGui::IsWindowFocused(ImGuiFocusedFlags_ChildWindows))

	if (io.WantCaptureKeyboard) {
		//dispatch the inputs to imgui
		//ImGui::TreeNode("");
ImGui::Text("Keys pressed:");
		for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) {
			if (ImGui::IsKeyPressed(i)) {
				
				//cout << io.KeyMap[87]<< endl;
				ImGui::SameLine();
				ImGui::Text("%d (0x%X)", i, i);
			}
		}
	}
	else {
		//dispatch to applcation. i.e. to boxer robot
		
		
	}
}
void Inputs::gamepadInputHandler() {
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
}
void Inputs::joystickInputHandler() {
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
}
void Inputs::touchInputHandler() {
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
}
void Inputs::noInputHandler() {
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
}




