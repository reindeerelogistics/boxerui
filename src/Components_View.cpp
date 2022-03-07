#include "Components_View.h"

void Components_View::resetFrame() {
	//Current frame is discarded and renders a new one upon call.
	endFrame();
	startFrame();
}

void Components_View::endFrame() {
	//Current frame is discarded and renders a new one upon call.
	ImGui::EndFrame();
	ImGui::UpdatePlatformWindows();

}

void Components_View::startFrame() {
	//Current frame is discarded and renders a new one upon call.

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

void Components_View::appFrameRate()
{
	{
		ImGui::Begin("overlay###overlay"); // Create a window called "Hello, world!" and append into it.
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}
}

bool Components_View::colButton(const char* desc, ImGuiColorEditFlags flags, const ImVec4 col, ImVec2 size) {
	return ImGui::ColorButton(desc, col, flags, size);
}

bool Components_View::button(const char* desc, ImVec2 size) {
	return ImGui::Button(desc, size);
}

bool Components_View::navButton(const char* desc, ImVec2 size) {
	ImGuiButtonFlags flags = ImGuiButtonFlags_AlignTextBaseLine;
	//ImGui::IsItemClicked()

	return ImGui::ButtonEx(desc, size,flags);
}

bool Components_View::margin(const char* desc, ImVec2 size) {
	//ImVec2 sz = ImGui::CalcTextSize(desc);
	//ImVec2 cursor = ImGui::GetCursorPos();
	//ImGui::InvisibleButton("##padded-text", sz + ImVec2(padding_x * 2, padding_y * 2));    // ImVec2 operators require imgui_internal.h include and -DIMGUI_DEFINE_MATH_OPERATORS=1
	//ImVec2 final_cursor_pos = ImGui::GetCursorPos();
	//ImGui::SetCursorPos(cursor + ImVec2(padding_x, padding_y));
	//ImGui::Text(desc);
	//ImGui::SetCursorPos(final_cursor_pos);

	return false;
}

bool Components_View::marginY(const char* desc, ImVec2 sizeT,ImVec2 sizeB, ImGuiButtonFlags flags) {
	
	return (marginTop(desc,sizeT,flags) && marginBottom(desc,sizeB,flags));// ImGui::InvisibleButton(("%s##padding-x", desc), size, flags);
}

bool Components_View::marginX(const char* desc, ImVec2 sizeL,ImVec2 sizeR, ImGuiButtonFlags flags) {
	
	return (marginLeft(desc,sizeL,flags) && marginRight(desc,sizeR,flags));// ImGui::InvisibleButton(("%s##padding-x", desc), size, flags);
}

bool Components_View::marginTop(const char* desc, ImVec2 size, ImGuiButtonFlags flags) {
	return ImGui::InvisibleButton(("%s##padding-up", desc), ImVec2(ImGui::CalcTextSize(desc).x,size.y), flags);
}

bool Components_View::marginBottom(const char* desc, ImVec2 size, ImGuiButtonFlags flags) {
	return ImGui::InvisibleButton(("%s##padding-down", desc),ImVec2(ImGui::CalcTextSize(desc).x,size.y), flags);
}

bool Components_View::marginLeft(const char* desc, ImVec2 size, ImGuiButtonFlags flags) {	
	ImGui::InvisibleButton(("%s##padding-left", desc), ImVec2(size.x,ImGui::CalcTextSize(desc).y), flags);
	ImGui::SameLine();
	return true;
}

bool Components_View::marginRight(const char* desc, ImVec2 size, ImGuiButtonFlags flags) {
	return ImGui::InvisibleButton(("%s##padding-right", desc),ImVec2(size.x,ImGui::CalcTextSize(desc).y), flags);
	ImGui::SameLine();
	return true;
}

bool Components_View::contextMenu(ContextItem* context_item) {
	//s_contentItems.m_mainContextItems.emplace(&context_item);
	contextMenu();
	return false;
}

bool Components_View::contextMenu(const char* conMenuName) {
	if (!ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
		return false;
	}
	std::map<std::string, ContextItem*>::iterator it = s_contentItems.m_mainContextItems.begin();
	static bool temp_state = false;
	ImGuiPopupFlags popupFlags = ImGuiPopupFlags_NoOpenOverExistingPopup | ImGuiPopupFlags_MouseButtonRight;
	
	if (ImGui::BeginPopupContextItem("mainContext", popupFlags))
	{
		/*for (auto& item : s_contentItems.m_mainContextItems) {
			if (ImGui::MenuItem(item.first.c_str(), item.second.m_shortcut.c_str(), item.second.m_value, item.second.m_enabled))item.second.m_value = !item.second.m_value;
		}*/
		while (it != s_contentItems.m_mainContextItems.end())
		{

			if (ImGui::MenuItem(it->first.c_str(), it->second->m_shortcut.c_str(), it->second->m_value, it->second->m_enabled)) it->second->m_value = !it->second->m_value;
			it++;
		}
		//auto* temp = &s_contentItems.m_mainContextItems;
		////BOXERUI_ASSERT(!context_items.empty());
		//while (!(*temp).empty())
		//{
		//	if (ImGui::MenuItem((*temp).front().m_name.c_str(), (*temp).front().m_shortcut.c_str(), (*temp).front().m_value, (*temp).front().m_enabled))(*temp).front().m_value = !(*temp).front().m_value;
		//	//temp.pop();
		//	*temp.
		//}

		ImGui::EndPopup();
	}
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))ImGui::OpenPopup(conMenuName);
	return false;
}

bool Components_View::contextMenu(const char* label, const char* shortcut, bool selected, bool enabled)//, std::function<void()> f)
{
	return false;
}

bool Components_View::overlay() {

	static bool* p_open;
	if (s_contentItems.m_mainContextItems.find("Open Overlay")->second->m_value)
		p_open = &s_contentItems.m_mainContextItems.find("Open Overlay")->second->m_value;
	else
	{
		return false;
	}

	ImGuiPopupData d;
	d.OpenFrameCount;

	BoxerUI_Monitor* monitor = BoxerUI_Monitor::Get();
	
	ImGuiPopupFlags popupFlags = ImGuiPopupFlags_MouseButtonRight;
	
	ImGuiIO& io = ImGui::GetIO();
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	if (monitor->m_overlayCorner != -1)
	{
		const float PAD = 10.0f;
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImVec2 work_pos = viewport->WorkPos; // Use work area to avoid menu-bar/task-bar, if any!
		ImVec2 work_size = viewport->WorkSize;
		ImVec2 window_pos, window_pos_pivot;
		window_pos.x = (monitor->m_overlayCorner & 1) ? (work_pos.x + work_size.x - PAD) : (work_pos.x + PAD);
		window_pos.y = (monitor->m_overlayCorner & 2) ? (work_pos.y + work_size.y - PAD) : (work_pos.y + PAD);
		window_pos_pivot.x = (monitor->m_overlayCorner & 1) ? 1.0f : 0.0f;
		window_pos_pivot.y = (monitor->m_overlayCorner & 2) ? 1.0f : 0.0f;
		ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
		ImGui::SetNextWindowViewport(viewport->ID);
		window_flags |= ImGuiWindowFlags_NoMove;
	}
	ImGui::SetNextWindowBgAlpha(0.55f); // Transparent background = 0.35f
	//static bool context_item_value = it->second;

	if (ImGui::Begin("overlay###overlay", p_open, window_flags))
	{
		ImGui::Text("Simple overlay\n" "in the corner of the screen.\n" "(right-click to change position)");
		ImGui::Separator();
		if (ImGui::BeginPopupContextWindow("overlayPopup###overlay", popupFlags))
		{
			/*if (ImGui::MenuItem("Custom", NULL, monitor->m_overlayCorner == -1)) monitor->m_overlayCorner = -1;
			if (ImGui::MenuItem("Top-left", NULL, monitor->m_overlayCorner == 0)) monitor->m_overlayCorner = 0;
			if (ImGui::MenuItem("Top-right", NULL, monitor->m_overlayCorner == 1)) monitor->m_overlayCorner = 1;
			if (ImGui::MenuItem("Bottom-left", NULL, monitor->m_overlayCorner == 2)) monitor->m_overlayCorner = 2;
			if (ImGui::MenuItem("Bottom-right", NULL, monitor->m_overlayCorner == 3)) monitor->m_overlayCorner = 3;*/
			if (p_open && ImGui::MenuItem("Close Overlay", "Esc", s_contentItems.m_mainContextItems.find("Open Overlay")->second->m_value)) {
				*p_open = false;
			}

			ImGui::EndPopup();
		}
	}
	ImGui::End();

	appFrameRate();

	return p_open;
}