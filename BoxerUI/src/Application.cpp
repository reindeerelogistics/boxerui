#include "Application.h"


void Application::glfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void Application::glfwWindowCloseCallback(GLFWwindow* m_window)
{
	//Perhaps call the controller to pack things up. Its time to end
	BoxerUI_Monitor* monitor = BoxerUI_Monitor::Get();
	Application& app = Application::Get();

	monitor->m_appRunning = app.m_boxerController->destroyCamThreads();
	app.m_isRunning=monitor->m_appRunning ;		//set the monitor flag to false so it might notify the rest of the application to free resources and shutdown

	
	glfwSetWindowShouldClose(m_window, app.m_isRunning ? GL_FALSE : GL_TRUE);

}

void Application::glfwMonitorCallback(GLFWmonitor* monitor, int event) {
	if (event == GLFW_CONNECTED)
	{
		// The monitor was connected
		std::cout << "New Monitor detected!" << std::endl;
		//GLFWmonitor** monitors = glfwGetMonitors(&m_monitorCount);
	}
	else if (event == GLFW_DISCONNECTED)
	{
		std::cout << "Monitor removed!" << std::endl;
		// The monitor was disconnected
	}

}

void Application::monitorAndWiindowInit() {
	// Decide GL+GLSL versions

	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only


	// Create window with graphics context
	glfwWindowHint(GLFW_DECORATED, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	//glfwWindowHint(GLFW_VISIBLE, GL_TRUE);
	glfwWindowHint(GLFW_AUTO_ICONIFY, GL_TRUE);
	//glfwWindowHint(GLFW_FLOATING, GL_TRUE);
	//glfwWindowHint(GLFW_SRGB_CAPABLE, GL_FALSE);
	//glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

	int ui_window_width = 1280, ui_window_height = 720, monitor_W = 0, monitor_H = 0;

	m_window = glfwCreateWindow(ui_window_width, ui_window_height, BOXERUI_APP_NAME, NULL, NULL);

	glfwGetWindowSize(m_window, &ui_window_width, &ui_window_height);

	//m_monitor = glfwGetWindowMonitor(m_window);

	m_monitor = glfwGetPrimaryMonitor();		//Get primary monitor

	//glfwGetMonitorPhysicalSize(monitor, &monitor_W, &monitor_H);
	//glfwSetWindowPos(m_window, (monitor_W/3), (monitor_H/3));

	//const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	//glfwSetWindowMonitor(m_window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

	// std::string image_path = cv::samples::findFile("../boxer.jpg");
	// cv::Mat img = cv::imread(image_path);// , cv::IMREAD_COLOR);

	// GLFWimage images[2];
	// images[0].pixels = img.ptr();// load_icon("my_icon.png");
	// images[0].height = 48;
	// images[0].width = 48;
	// //images[1] = load_icon("my_icon_small.png");
	// glfwSetWindowIcon(m_window, 1, images);
}

bool Application::initApplication()
{
	const char* glsl_version = "#version 130";

	// Setup window
	glfwSetErrorCallback(glfwErrorCallback);
	if (!glfwInit()) {
		BOXERUI_ASSERT(m_isRunning == true);	//glfw Init failed
		return m_isRunning;
	}

	monitorAndWiindowInit();
	if (m_window == NULL) {
		BOXERUI_ASSERT(m_isRunning == true);	//Application window was not initialized
		return m_isRunning;
	}
	glfwMakeContextCurrent(m_window);
	glfwSwapInterval(1); // Enable vsync

	// Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
	bool err = gl3wInit() != 0;
#endif
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	//cv::cuda::setGlDevice();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;

	BoxerUI::Boxer_Log::initLogger();
	BOXER_INFO_LOGGER(BOXERUI_APP_NAME);
	BOXER_TRACE_LOGGER("BOXERUI_VERSION: " BOXERUI_VERSION );
	//std::cout << "BOXERUI_BIN_DIR: " << BOXERUI_BIN_DIR << std::endl;
	BOXERUI_CHECKCUDA();

	//std::cout <<"\\"; BOXERUI_BIN_DIR"\\" << std::endl;

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
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

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

	//BOXERUI_ASSERT(m_isRunning==true);		
	return m_isRunning;
}

void Application::preRun() {

	glfwSetMonitorCallback(glfwMonitorCallback);
	glfwSetWindowCloseCallback(m_window, glfwWindowCloseCallback);
	// Poll and handle events (inputs, window resize, etc.)
	// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
	// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
	// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
	// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
	glfwPollEvents();
	// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_AutoHideTabBar);
}

void Application::postRun() {// Rendering
	ImGuiIO& io = ImGui::GetIO();

	const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(m_window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(m_window) directly)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	glfwSwapBuffers(m_window);
}

bool Application::runApplication() {

	initApplication();		//if unsuccessful init

	while (!glfwWindowShouldClose(m_window) && m_isRunning) {
		preRun();
		m_boxerController->views();
		postRun();
	}

	endApplication();

	return m_isRunning;
}

void Application::endApplication()
{
	GLFWwindow* window = glfwGetCurrentContext();
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(m_window);
	glfwTerminate();
}
