#pragma once
#include "Boxer.h"
#include "Boxerpch.h"
#include "../resource/icons/IconFontCppHeaders/IconsFontAwesome5.h"
#include "../resource/icons/IconFontCppHeaders/IconsMaterialDesign.h"
#include <map>


enum class FontStyle {
	PantonDemo_Black,
	PantonDemo_Light,
	Poppins_Regular,
	Poppins_Medium,
	Custom_Font
};

enum class IconStyle {
	MaterialIcons_Regular,
	MaterialIconsOutlined_Regular,
	FontAwesome_Regular,
	Custom_Font
};

using TextStyleMap = std::map<FontStyle, std::string>;
using IconStyleMap = std::map<IconStyle, std::string>;

/** @brief This text theme follows material design type scalling guidelines(https://material.io/design/typography/the-type-system.html#type-scale)
@note fonts are loaded in the following order
**/
struct TextTheme {

	void setFont();
private:
	ImGuiIO& io = ImGui::GetIO();

	ImFont* font_default;

	ImFontConfig config_icon, config_font;

	TextStyleMap createFontMap();

	IconStyleMap createIconMap();

	void headline(const TextStyleMap* m);
	void subtitle(const TextStyleMap* m);
	void body(const TextStyleMap* m);
	void button(const TextStyleMap* m);

	//ICONS
	void icons(const IconStyleMap* map, const ImWchar* icon_ranges);
};