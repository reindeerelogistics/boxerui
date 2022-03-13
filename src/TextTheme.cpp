#include "TextTheme.h"

TextStyleMap TextTheme::createFontMap()
{
	std::map<FontStyle, std::string> textstyle_map = {
	{FontStyle::PantonDemo_Black, BoxerUI::appendPath(" resource/fonts/Panton/PantonDemo-Black.otf")},
	{FontStyle::PantonDemo_Light, BoxerUI::appendPath(" resource/fonts/Panton/PantonDemo-Light.otf") },
	{FontStyle::Poppins_Regular, BoxerUI::appendPath(" resource/fonts/Poppins/Poppins-Regular.ttf")},
	{FontStyle::Poppins_Medium, BoxerUI::appendPath(" resource/fonts/Poppins/Poppins-Medium.ttf")},
	};
	return textstyle_map;
}

IconStyleMap TextTheme::createIconMap()
{
	std::map<IconStyle, std::string> textstyle_map = {
	{IconStyle::MaterialIconsOutlined_Regular, BoxerUI::appendPath(" resource/icons/MaterialDesignIcons/MaterialIconsOutlined-Regular.otf")},
	{IconStyle::FontAwesome_Regular, BoxerUI::appendPath(" resource/icons/FontAwesome/fontawesome-free-5.15.3-desktop/otfs/FontAwesome5Free-Regular-400.otf")},
	};
	
	return textstyle_map;
}

void TextTheme::setFont()
{
	const TextStyleMap textstyle_map = createFontMap();
	const IconStyleMap iconstyle_map = createIconMap();

	config_font.OversampleH = 3;
	io.Fonts->AddFontDefault();

	const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, ICON_MIN_MD, ICON_MAX_MD, 0 };// Will not be copied by AddFont*, keep in scope as indicated in ImGui docs (https://github.com/reindeererobotics/imgui/blob/master/docs/FONTS.md#font-loading-instructions)

	headline(&textstyle_map);
	subtitle(&textstyle_map);
	icons(&iconstyle_map, icon_ranges); //Icons are loaded first and merged with the default font as this font is guarateed to always to be available
	body(&textstyle_map);
	button(&textstyle_map);

	//Builds all fonts
	io.Fonts->Build();
}

void TextTheme::headline(const TextStyleMap* map) {//impl Header styles
	io.Fonts->AddFontFromFileTTF(map->at(FontStyle::PantonDemo_Light).c_str(), 96.0f, &config_font);//Headline 1
	io.Fonts->AddFontFromFileTTF(map->at(FontStyle::PantonDemo_Light).c_str(), 60.0f, &config_font);//Headline 2
	//io.Fonts->AddFontFromFileTTF(map->at(FontStyle::PantonDemo_Black), 48.0f, &config_font);//Headline 3
	//io.Fonts->AddFontFromFileTTF(map->at(FontStyle::PantonDemo_Black), 34.0f, &config_font);//Headline 4
	//io.Fonts->AddFontFromFileTTF(map->at(FontStyle::PantonDemo_Black), 24.0f, &config_font);//Headline 5
	//io.Fonts->AddFontFromFileTTF(map->at(FontStyle::PantonDemo_Black), 20.0f, &config_font);//Headline 6
}

void TextTheme::subtitle(const TextStyleMap* map) {//impl subtitle styles
	io.Fonts->AddFontFromFileTTF(map->at(FontStyle::Poppins_Regular).c_str(), 16.0f, &config_font);//subtitle 1
	io.Fonts->AddFontFromFileTTF(map->at(FontStyle::Poppins_Medium).c_str(), 14.0f, &config_font);//subtitle 2
}

void TextTheme::body(const TextStyleMap* map) {//impl body styles
	io.Fonts->AddFontFromFileTTF(map->at(FontStyle::Poppins_Regular).c_str(), 16.0f, &config_font);//body 1
	io.Fonts->AddFontFromFileTTF(map->at(FontStyle::Poppins_Regular).c_str(), 14.0f, &config_font);//body 2
}

void TextTheme::button(const TextStyleMap* map) {//impl button styles
	io.Fonts->AddFontFromFileTTF(map->at(FontStyle::Poppins_Medium).c_str(), 14.0f, &config_font);//button
}

void TextTheme::icons(const IconStyleMap* map, const ImWchar* icon_ranges) {

	config_icon.MergeMode = true;
	config_icon.PixelSnapH = true;
	config_icon.GlyphMinAdvanceX = 13.0f;

	//ICONS
	io.Fonts->AddFontFromFileTTF(map->at(IconStyle::FontAwesome_Regular).c_str(), 24.0f, &config_icon, icon_ranges);//Icons
	io.Fonts->AddFontFromFileTTF(map->at(IconStyle::MaterialIconsOutlined_Regular).c_str(), 24.0f, &config_icon, icon_ranges);

}


