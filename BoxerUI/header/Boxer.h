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

#include <opencv2/opencv.hpp>
#include "opencv2/core/cuda.hpp"
//#include <opencv2/core.hpp>

#define BOXERUI_VERSION		"0.0.0"
#define BOXERUI_CHECKCUDA()  (BoxerUI::cudaInfo())
#define BOXER_UI

//Singleton research: https://stackoverflow.com/questions/1008019/c-singleton-design-pattern
//Thread safe singleton BoxerUI_Monitor.
class BoxerUI_Monitor
{
public:

	static BoxerUI_Monitor* Get();
	/*{
		static BoxerUI_Monitor monitor_instance;
		return monitor_instance;
	}*/

private:
	static BoxerUI_Monitor* monitor_instance;
	//BoxerUI_Monitor() {};

};

namespace BoxerUI {
	//BoxerUI_Monitor& Get();
	bool cudaInfo();
}