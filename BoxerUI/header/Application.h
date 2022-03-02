#pragma once
#include "Boxer.h"
#include "BoxerUI_Log.h"
//#include "Boxerpch.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imconfig.h"

#include "TextTheme.h"
#include "BoxerUI_Controller.h"

class Application
{
private:

	GLFWwindow* m_window;
	GLFWmonitor* m_monitor;
	std::unique_ptr<BoxerUI::BoxerUI_Controller> m_boxerController;
	bool m_isRunning;
	int m_monitorCount;

private:

	Application() :m_isRunning(true), m_window(nullptr),m_monitor(nullptr),m_monitorCount(0) {
		//m_window = std::make_unique<GLFWwindow>();

		//m_window = std::make_unique<GLFWwindow>();
		m_boxerController = std::make_unique<BoxerUI::BoxerUI_Controller>();
	};

private:
	void monitorAndWiindowInit();
	static void glfwMonitorCallback(GLFWmonitor* monitor, int event);
	static void glfwErrorCallback(int error, const char* description);
	static void glfwWindowCloseCallback(GLFWwindow* m_window);
	void preRun();
	void postRun();
public:

	//~Application();

	static Application& Get() {
		static Application s_appInstance;
		return s_appInstance;
	}

public:
	bool isRunning() { return m_isRunning; }
	bool initApplication();
	bool runApplication();
	void endApplication();
};