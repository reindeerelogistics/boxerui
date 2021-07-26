#pragma once
#include "Boxer.h"
class Components_View
{
protected:

	//Do !!NOT!! use within Begin()/BeginChild() window
	static void resetFrame();

	static void HelpMarker(const char* desc);

	static bool colButton(const char* desc, ImGuiColorEditFlags flags= ImGuiColorEditFlags_NoTooltip , const ImVec4 col = ImVec4(0.26f, 0.60f, 0.98f, 0.40f), ImVec2 size = ImVec2(65, 30));
	
	static bool button(const char* desc, ImVec2 size = ImVec2(65, 30));

	static bool navButton(const char* desc, ImVec2 size = ImVec2(65, 30));
};

