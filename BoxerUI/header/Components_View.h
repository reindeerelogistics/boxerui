#pragma once		
#include "Boxer.h"
#include "Boxerpch.h"

#define NUM_CONTEXT_ITEMS 2

//Examples of windows file dialogue: https://github.com/microsoft/Windows-classic-samples/blob/main/Samples/Win7Samples/winui/shell/appplatform/commonfiledialog/CommonFileDialogApp.cpp
		//Could help as well: https://www.informit.com/articles/article.aspx?p=25925
		//https://docs.microsoft.com/en-us/windows/win32/learnwin32/asking-an-object-for-an-interface
struct ContextItem {
public:
	const std::string m_name;
	const std::string m_shortcut;
	bool m_value;
	bool m_enabled;

	ContextItem(const std::string& name, const std::string& shortcut) :m_name(name), m_shortcut(shortcut), m_value(false), m_enabled(true) {};
	ContextItem(const std::string& name) :m_name(name), m_shortcut(""), m_value(false), m_enabled(true) {};

};

struct ContextItems {

	//const char* items_names[NUM_CONTEXT_ITEMS] = { "Close", "Analytics" };
	//const char* items_shortcut[NUM_CONTEXT_ITEMS] = { "Esc", "" };

	//std::vector<ContextItems>  = std::vector<ContextItems>(sizeof(items_names));

public:
	std::map<std::string, ContextItem*> m_mainContextItems;

	ContextItems() :m_mainContextItems() {

		m_mainContextItems.insert(std::make_pair("Open Overlay", new ContextItem("Open Overlay", "CTRL+SHIFT+O")));
		m_mainContextItems.insert(std::make_pair("Analytics", new ContextItem("Analytics")));
		//m_mainContextItems.emplace("", ContextItem("Analytics"));
	}

	ContextItems(ContextItem item) {
		//m_mainContextItems.emplace(&item);
	}

};



class Components_View
{
public:
	static void appFrameRate();
private:
	ContextItems s_contentItems;
protected:
	
	static void resetFrame();		//Do !!NOT!! use within Begin()/BeginChild() window

	static void endFrame();

	static void startFrame();

	static void HelpMarker(const char* desc);

	static bool colButton(const char* desc, ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoTooltip, const ImVec4 col = ImVec4(0.26f, 0.60f, 0.98f, 0.40f), ImVec2 size = ImVec2(65, 30));

	static bool button(const char* desc, ImVec2 size = ImVec2(65, 30));

	static bool navButton(const char* desc, ImVec2 size = ImVec2(85, 45));

	static bool margin(const char* desc, ImVec2 size = ImVec2(85, 30));

	static bool marginY(const char* desc, ImVec2 sizeT = ImVec2(2, 4),ImVec2 sizeB = ImVec2(2, 4), ImGuiButtonFlags flags= ImGuiButtonFlags_NoHoldingActiveId | ImGuiButtonFlags_PressedOnDragDropHold | ImGuiButtonFlags_NoHoveredOnFocus | ImGuiButtonFlags_AlignTextBaseLine);

	static bool marginTop(const char* desc="margin-up", ImVec2 size = ImVec2(2, 4), ImGuiButtonFlags flags = ImGuiButtonFlags_NoHoldingActiveId | ImGuiButtonFlags_PressedOnDragDropHold | ImGuiButtonFlags_NoHoveredOnFocus | ImGuiButtonFlags_AlignTextBaseLine);

	static bool marginBottom(const char* desc="margin-down", ImVec2 size = ImVec2(2, 4), ImGuiButtonFlags flags = ImGuiButtonFlags_NoHoldingActiveId | ImGuiButtonFlags_PressedOnDragDropHold | ImGuiButtonFlags_NoHoveredOnFocus | ImGuiButtonFlags_AlignTextBaseLine);

	static bool marginX(const char* desc, ImVec2 sizeL = ImVec2(2, 4),ImVec2 sizeR = ImVec2(2, 4), ImGuiButtonFlags flags= ImGuiButtonFlags_NoHoldingActiveId | ImGuiButtonFlags_PressedOnDragDropHold | ImGuiButtonFlags_NoHoveredOnFocus | ImGuiButtonFlags_AlignTextBaseLine);

	static bool marginLeft(const char* desc="margin-left", ImVec2 size = ImVec2(2, 4), ImGuiButtonFlags flags = ImGuiButtonFlags_NoHoldingActiveId | ImGuiButtonFlags_PressedOnDragDropHold | ImGuiButtonFlags_NoHoveredOnFocus | ImGuiButtonFlags_AlignTextBaseLine);

	static bool marginRight(const char* desc="margin-right", ImVec2 size = ImVec2(2, 4), ImGuiButtonFlags flags = ImGuiButtonFlags_NoHoldingActiveId | ImGuiButtonFlags_PressedOnDragDropHold | ImGuiButtonFlags_NoHoveredOnFocus | ImGuiButtonFlags_AlignTextBaseLine);


	bool contextMenu(const char* conMenuName = "mainContext");

	bool contextMenu(ContextItem* context_item);

	bool contextMenu(const char* label, const char* shortcut = NULL, bool selected = false, bool enabled = true);

	bool overlay();

};

