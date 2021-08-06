#pragma once

#include <iostream>
#include "implot.h"
#include "Inputs_Model.h"
#include "TextTheme.h"
#include "Components_View.h"

#include "../resource/icons/IconFontCppHeaders/IconsFontAwesome5.h"
#include "../resource/icons/IconFontCppHeaders/IconsMaterialDesign.h"

//#define _BOXERUI_TEST

class BoxerUI_View :public Components_View
{
	
public:
	static void appFrameRate();
	static void showdemos();
	static void displaySensors(double temperature, double battery);
	static void plotStream();
	static void indexwindow(bool* boxer_analytics);

	bool sideNav();

	bool settings();
	
	void indexView();

};