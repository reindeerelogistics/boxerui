#pragma once
#include "TextTheme.h"
#include "BoxerUI_Controller.h"

#if _WIN32
#include "platform\opengl\OpenglWindow.h"
#else
#include "platform\directx11\Directx11Window.h"	
#endif

class Application
{
private:
	BoxerUI::WindowProps prop;
	BoxerUI::Windows s_appWindow = BoxerUI::Windows(prop);
	std::unique_ptr<BoxerUI::BoxerUI_Controller> m_boxerController;
	bool m_isRunning;
	int m_monitorCount;

private:
	Application();
	~Application();
private:
	void preRun();
	void postRun();
	bool isRunning() {  return s_appWindow.isWindowClosed(); }
	bool cleanup();
	void endApplication();
	void initApplication();
public:
	void runApplication();

	static Application& Get() {
		static Application s_appInstance;
		return s_appInstance;
	}
};