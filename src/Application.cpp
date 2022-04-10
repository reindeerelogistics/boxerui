#include "Application.h"

//void Application::glfwWindowCloseCallback(GLFWwindow* m_window)
//{
//	//Perhaps call the controller to pack things up. Its time to end
//	BoxerUI_Monitor* monitor = BoxerUI_Monitor::Get();
//	Application& app = Application::Get();
//
//	monitor->m_appRunning = app.m_boxerController->destroyCamThreads();
//	app.m_isRunning = monitor->m_appRunning;		//set the monitor flag to false so it might notify the rest of the application to free resources and shutdown
//
//
//	glfwSetWindowShouldClose(m_window, app.m_isRunning ? GL_FALSE : GL_TRUE);
//
//}

void Application::initApplication()
{
	// Window setup
	//s_appWindow.Create();

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//cv::cuda::setGlDevice();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	// Logging
	BoxerUI::Boxer_Log::initLogger();
	BOXER_INFO_LOGGER(BOXERUI_APP_NAME);
	BOXER_FILE_LOGGER;
	BOXER_TRACE_LOGGER("BOXERUI_VERSION: " BOXERUI_VERSION);
	//std::cout << "BOXERUI_BIN_DIR: " << BOXERUI_BIN_DIR << std::endl;
	//BOXERUI_CHECKCUDA();


	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;	// Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
	//io.ConfigViewportsNoAutoMerge = false;
	//io.ConfigDockingWithShift = true;
	//io.ConfigFlags |=ImGuiConfigFlags_shift
	//io.ConfigDockingAlwaysTabBar = false;
	//io.ConfigViewportsNoTaskBarIcon = false;
	//io.ConfigViewportsNoDefaultParent = false;
	//ImGuiConfigFlags inputs =ImGuiConfigFlags_NavEnableKeyboard;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.5f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(s_appWindow.getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 130");
#if _WIN32
#else
#endif // _WIN32



	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !

	TextTheme texttheme;
	texttheme.setFont();
	//IM_ASSERT(font != NULL);


}

void Application::preRun() {
#if _WIN32
	
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_AutoHideTabBar);
#else
#endif // _WIN32

}

void Application::postRun() {// Rendering
	s_appWindow.onUpdate();
}

void Application::runApplication() {

	while (!isRunning()) {
		preRun();
		m_boxerController->views();
		postRun();
	}
}

bool Application::cleanup() {
	BoxerUI_Monitor* monitor = BoxerUI_Monitor::Get();
	Application& app = Application::Get();

	return app.m_boxerController->destroyCamThreads();
}

void Application::endApplication()
{
	cleanup();
#if _WIN32
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
#else
#endif // _WIN32

}

Application::Application() {

	m_boxerController = std::make_unique<BoxerUI::BoxerUI_Controller>();
	initApplication();

}

Application::~Application() {
	endApplication();
}
