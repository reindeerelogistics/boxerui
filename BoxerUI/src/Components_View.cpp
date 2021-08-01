#include "Components_View.h"

void Components_View::resetFrame() {
	//Current frame is discarded and renders a new one upon call.
	ImGui::EndFrame();
	ImGui::UpdatePlatformWindows();
	ImGui::Render();
	ImGui::NewFrame();
}

void Components_View::HelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}

bool Components_View::colButton(const char* desc, ImGuiColorEditFlags flags, const ImVec4 col, ImVec2 size) {
	return ImGui::ColorButton(desc,col,flags,size);
}

bool Components_View::button(const char* desc, ImVec2 size) {
	return ImGui::Button(desc, size);
}
