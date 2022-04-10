#include "platform\opengl\OpenglWindow.h"

//#ifndef TEST_DATA_DIR
//#error "Must specify test data directory path in TEST_DATA_DIR."
//#else
//#define STRINGIFY(x) #x
//#define TOSTRING(x) STRINGIFY(x)
//constexpr const char* testDataFolder = TOSTRING(TEST_DATA_DIR);
//#undef TOSTRING
//#undef STRINGIFY
//#endif

namespace BoxerUI {


	static bool s_glfwInit = false;

	Windows::Windows(const WindowProps& props)
	{
		//m_window = nullptr;
		//m_monitor=nullptr;
		init(props);
	}

	Windows::~Windows() {
		//Terminate the window
		shutdown();
	}

	int Windows::init(const WindowProps& props)
	{
		// Setup window
		glfwSetErrorCallback(glfwErrorCallback);
		if (!glfwInit()) {
			//BOXERUI_ASSERT(s_glfwInit == true);	//glfw Init failed
			return 1;
		}

		// Decide GL+GLSL versions

		// GL 3.0 + GLSL 130
		//const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		GLenum
		gl3wBindFramebuffer();
		glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
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

		m_window = glfwCreateWindow(props.Width, props.Height, BOXERUI_APP_NAME, NULL, NULL);

		//glfwGetWindowSize(m_window, props.Width, &props.Height);

		//m_monitor = glfwGetWindowMonitor(m_window);

		m_monitor = glfwGetPrimaryMonitor();		//Get primary monitor

		if (m_window == NULL) {
			//BOXERUI_ASSERT(s_glfwInit == true);	//Application window was not initialized
			return 1;
		}
		glfwMakeContextCurrent(m_window);
		setVsync(props.Vsync); // Enable vsync

		// Initialize OpenGL loader
		bool err = gl3wInit() != 0;

		if (err)
		{
			fprintf(stderr, "Failed to initialize OpenGL loader!\n");
			return 1;
		}


		glfwSetMonitorCallback(glfwMonitorCallback);
		glfwSetWindowCloseCallback(m_window, glfwWindowCloseCallback);
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		
		
		return 0;
	}

	void Windows::shutdown()
	{
		//GLFWwindow* window = glfwGetCurrentContext();
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

	void Windows::onUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();

		//const ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		ImGui::Render();
		int display_w, display_h;
		ImVec4 clear_color = ImVec4(0.0f, 0.0f, 0.0f, 1.00f);
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
		glfwPollEvents();
	}

	Window* Window::Create(const WindowProps& props) {
		return new Windows(props);
	}

	void Windows::setVsync(bool enabled) {
		isVsync = enabled;

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}

	void Windows::glfwErrorCallback(int error, const char* description)
	{
		fprintf(stderr, "Glfw Error %d: %s\n", error, description);
	}

	void Windows::glfwWindowCloseCallback(GLFWwindow* m_window)
	{

		glfwSetWindowShouldClose(m_window, GL_TRUE);

	}

	void Windows::glfwMonitorCallback(GLFWmonitor* monitor, int event) {
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

	GLFWwindow* Windows::getWindow() {
		GLFWwindow* window = glfwGetCurrentContext();
		return  window;
	}
}