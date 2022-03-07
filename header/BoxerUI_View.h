#pragma once
//#include "implot.h"
#include "Inputs_Model.h"
#include "Components_View.h"
#include "CameraStream_View.h"
#include <Windows.h>
#include <Commdlg.h>
#include <shobjidl_core.h>


#include "../resource/icons/IconFontCppHeaders/IconsFontAwesome5.h"
#include "../resource/icons/IconFontCppHeaders/IconsMaterialDesign.h"

//#define _BOXERUI_TEST
namespace BoxerUI {
	class BoxerUI_View : public Components_View
	{

	
	private:
		static void mainMenuBar();
		HRESULT getFontFile();

		void fontFile();

		void inputs(bool* keyboard);
	public:
		CameraStream camera_stream;
		BoxerUI_View()
			: camera_stream(){}

	public:
		void viewDockspace();
		static void showdemos();
		static void displaySensors(double temperature, double battery);
		static void plotStream();
		static void signinWindow(bool* boxer_analytics);
		static void indexWindow();

		void views();

		void mainViews();

		bool sideNav();

		bool settings();

		void indexView();

		void cameraView();
	};

	enum class NavItem
	{
		Settings = 0,
		Home = 1,
		Stream = 2,
		Analytics = 3,
	};
	static NavItem nav_item = NavItem::Stream;
	static NavItem cached_nav_item;
}