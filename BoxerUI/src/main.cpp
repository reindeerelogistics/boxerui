// Dear ImGui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan/Metal graphics context creation, etc.)
// If you are new to Dear ImGui, read documentation from the docs/ folder + read the top of imgui.cpp.
// Read online: https://github.com/ocornut/imgui/tree/master/docs
#include "Boxer.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imconfig.h"

#include "BoxerUI_Controller.h"
#include "TextTheme.h"


#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
// About Desktop OpenGL function loaders:
//  Modern desktop OpenGL doesn't have a standard portable header file to load OpenGL function pointers.
//  Helper libraries are often used for this purpose! Here we are supporting a few common ones (gl3w, glew, glad).
//  You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h> // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h> // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h> // Initialize with gladLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
#include <glad/gl.h> // Initialize with gladLoadGL(...) or gladLoaderLoadGL()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
#define GLFW_INCLUDE_NONE	   // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/Binding.h> // Initialize with glbinding::Binding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
#define GLFW_INCLUDE_NONE		 // GLFW including OpenGL headers causes ambiguity or multiple definition errors.
#include <glbinding/glbinding.h> // Initialize with glbinding::initialize()
#include <glbinding/gl/gl.h>
using namespace gl;
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include <GLFW/glfw3.h>
// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int main(int, char**)
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback);
	if (!glfwInit())
		return 1;

	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
	// GL ES 2.0 + GLSL 100
	const char* glsl_version = "#version 100";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);		   // Required on Mac
#else
	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);
	glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

	// Create window with graphics context
	int ui_window_width = 1280, ui_window_height = 720;
	GLFWwindow* window = glfwCreateWindow(ui_window_width, ui_window_height, "Reheindeer Robotics - BoxerUI", NULL, NULL);
	glfwGetWindowSize(window, &ui_window_width, &ui_window_height);

	GLFWmonitor* monitor = glfwGetWindowMonitor(window);
	//const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	//glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);

	// std::string image_path = cv::samples::findFile("../boxer.jpg");
	// cv::Mat img = cv::imread(image_path);// , cv::IMREAD_COLOR);

	// GLFWimage images[2];
	// images[0].pixels = img.ptr();// load_icon("my_icon.png");
	// images[0].height = 48;
	// images[0].width = 48;
	// //images[1] = load_icon("my_icon_small.png");
	// glfwSetWindowIcon(window, 1, images);

	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
	bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
	bool err = gladLoadGL() == 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD2)
	bool err = gladLoadGL(glfwGetProcAddress) == 0; // glad2 recommend using the windowing library loader instead of the (optionally) bundled one.
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING2)
	bool err = false;
	glbinding::Binding::initialize();
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLBINDING3)
	bool err = false;
	glbinding::initialize([](const char* name)
		{ return (glbinding::ProcAddress)glfwGetProcAddress(name); });
#else
	bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
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
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Load Fonts
	// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
	// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
	// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
	// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
	// - Read 'docs/FONTS.md' for more instructions and details.
	// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !



	//fonts.AddFontFromFileTTF("resource\\fonts\\Poppins-Regular.ttf", 14.0f, 0, fonts.GetGlyphRangesDefault());
	//fonts.AddFontDefault();

	//io.Fonts->AddFontDefault();
	//ImFont* x = io.Fonts->AddFontDefault();
	//x->ContainerAtlas =io.Fonts;
	//ImFontAtlas* fonts =  io.Fonts;

	TextTheme texttheme;
	texttheme.setFont();

	//io.Fonts = x->ContainerAtlas;
	//x->ContainerAtlas->Build();
	//io.Fonts = x->ContainerAtlas;


	//fonts->AddFontFromFileTTF("resource\\fonts\\PantonDemo-Black.otf", 55.0f);
	//io.Fonts->Build();
	// = io.Fonts->Fonts->AddFontDefault();
	//x->ContainerAtlas=fonts;// = io.Fonts->Fonts->AddFontDefault();
	//x->ContainerAtlas = &fonts;
	//fonts->Fonts[0] = ;
	{
		//TODO create an array that will read the contents of the resource/fonts and add to an ImFont array
	//ImFont* fonts[NUM_FONTS];
	//static const char* font_names[NUM_FONTS] = { "PantonDemo-Black.otf", "Poppins-Regular.ttf" };
	//const char* font_names[2] = { "PantonDemo-Black.otf", "Poppins-Regular.ttf" };



	//for (size_t i = 0; i < 2; i++)
	//{
	//	char font_path[100] = "resource\\fonts\\";
	//	strcat_s(font_path, font_names[i]);
	//	//d::cout << font_path << std::endl;
	//	//intf("%s", font_path);
	//	// git rm -r --cached BoxerUI/libs/imgui/
	//	fonts[i] = io.Fonts->AddFontFromFileTTF(font_path, 55);
	//}
	}
	//fonts = io.Fonts[0]->AddFont();
	//_fonts.AddFontFromFileTTF("Fonts\fontawesome-webfont.ttf", 14.0f, &icons_config, icons_ranges);
	//_fonts.GetTexDataAsRGBA32;
	//io.Fonts->AddFontFromFileTTF("resource\\icons\\Font Awesome 5 Brands-Regular-400.otf", 18.0f, &config, icon_ranges);
	//io.Fonts->AddFontFromFileTTF("resource\\icons\\MaterialIcons-Regular.ttf", 18.0f, &config, icon_ranges);
	//io.Fonts->AddFontFromFileTTF("resource\\fonts\\PantonDemo-Black.otf", 55.0f);// , & config, icon_ranges);// , io.Fonts->GetGlyphRangesDefault());
	//io.Fonts->AddFontFromFileTTF("resource\\fonts\\Poppins-Regular.ttf", 35.0f);// , & config, icon_ranges);// , io.Fonts->GetGlyphRangesDefault());
	//io.Fonts->GetTexDataAsRGBA32(&pixel_data, &width, &height, &bytes_per_pixel);

	//setFonts(fonts);
	//io.Fonts = x->ContainerAtlas;
	//io.Fonts->Build();
	//font->ContainerAtlas->AddFontFromFileTTF("resource\\fonts\\PantonDemo-Black.otf", 13.0f, &config);// , io.Fonts->GetGlyphRangesDefault());
	//font->ContainerAtlas->AddFontFromFileTTF("resource\\icons\\Font Awesome 5 Brands-Regular-400.otf", 13.0f, &config , icon_ranges);
	//font->ContainerAtlas->Build();
	//font.GetTexDataAsRGBA32(&pixel_data, &width, &height, &bytes_per_pixel);
	//fonts.AddFont(&config);
	//font->ContainerAtlas->Fonts[0].;
	//io.Fonts->Fonts[0];

	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
	//io.Fonts->AddFontFromFileTTF("../../misc/fonts/ProggyTiny.ttf", 10.0f);
	//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
	//IM_ASSERT(font != NULL);

	// Our state
	//bool show_demo_window = true;
	//static int item_current = 0;
	static bool show_boxer_windows = false, show_camera = false, show_index_window = true;
	bool p_open = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	//pid_t pid;
	//Initialize Boxer controller object.
	//BoxerUI_Model boxerModel = BoxerUI_Model();
	//BoxerUI_View boxerView;
	BoxerUI_Controller boxerController = BoxerUI_Controller(); // = BoxerUI_Controller(boxerView, boxerModel);
															   //boxerController.payloadRecv();


	// Main loop
	while (!glfwWindowShouldClose(window))
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();
		// glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT);
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_AutoHideTabBar);
		// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.

		{
			if (show_index_window)
			{
				boxerController.displayIndexWindow(&show_index_window);
			}
			else
			{
				//SetNextWindowViewport();
				ImGui::ShowStyleEditor();
				ImGui::ShowUserGuide();
				ImGui::ShowFontSelector("Font_selector");
				//ImFont* x = ImGui::GetFont();
				//ImGui::PushFont(x);
				//ImGui::Text("Settings");
				//ImGui::PopFont();

				boxerController.inputHandlerModel();
				//boxerController.cameraView();
				boxerController.indexView();
			}
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
