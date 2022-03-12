#pragma once
/**This header file is a general header file that can be configured to the entire scope of the project
It is meant to encompas any general function, variables or marcos that will pertain to the whole project.
Under no circumstance are the contents of this file meant to replace the message passing system impl by the MVC pattern.
i.e. Don't be tempted to use this file to bypass the Controller. Messages/data passed between the BoxerModel and BoxerView must go through the COntroller
**/


#include "imgui.h"
#include "imgui_internal.h"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "opencv2/opencv.hpp"
#include "opencv2/core/cuda.hpp"
#include <opencv2/core.hpp>


#define BOXER_UI
#define BOXERUI_CHECKCUDA()  (BoxerUI::cudaInfo())
//CMAKE Definitions
// #define BOXERUI_VERSION		established through CMAKE. Requires loose dependency on CMAKE
// #define BOXERUI_BIN_PATH		established through CMAKE. Requires loose dependency on CMAKE
// #define BOXERUI_APP_NAME		established through CMAKE. Requires loose dependency on CMAKE
// #define BOXERUI_BUILD_TYPE		established through CMAKE. Requires loose dependency on CMAKE

#ifdef BOXERUI_ASSERT_ENABLED
#include <assert.h>
#define BOXERUI_ASSERT(EXP) assert(EXP)
#endif

//Singleton research: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
//Thread safe singleton BoxerUI_Monitor.
struct BoxerUI_Monitor
{
public:

	static BoxerUI_Monitor* Get();
	/*{
		static BoxerUI_Monitor monitor_instance;
		return monitor_instance;
	}*/

	/*bool camDisplaying() { return m_camDisplaying; }
	bool appRunning() { return m_appRunning; }*/

public:
	bool m_camDisplaying;
	bool m_appRunning;
	bool m_mainContextMenu;
	int m_overlayCorner;

private:
	static BoxerUI_Monitor* s_monitorInstance;

	BoxerUI_Monitor()
		:m_camDisplaying(false), m_appRunning(true), m_mainContextMenu(true), m_overlayCorner(3)
	{};

};



namespace BoxerUI {
	//BoxerUI_Monitor& Get();
	bool cudaInfo();
	const char* getPath();
	std::string appendPath(const char* append);

}