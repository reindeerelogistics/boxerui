#include "CameraStream_View.h"

CameraStream::~CameraStream() {
	if (!cam_threads.empty())
	{
		destroyCamThreads();
	}
}

void CameraStream::destroyCamThreads()
{
	//destroy our camera stream thread pool	
		//= cam_threads[i];
	int i = 0;
	std::cout << "Num of active threads: " << cam_threads.size() << std::endl;
	for (std::thread& t : cam_threads)
	{
		if (t.joinable()) {
			std::cout << "Thread ID: " << t.get_id() << " joined successfully" << std::endl;
			t.join();
			(cam_threads).erase((cam_threads).begin() + i);
		}
		i++;
	}
	std::cout << "Num of active threads after joining: " << cam_threads.size() << std::endl;
}

void CameraStream::bindCVMat2GLTexture(cv::Mat disp_frame)//, CameraMap& payload_frames)
{
	ImGuiIO& io = ImGui::GetIO();

	//if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	//{
	//	GLFWwindow* backup_current_context = glfwGetCurrentContext();
	//	//ImGui::UpdatePlatformWindows();
	//	//ImGui::RenderPlatformWindowsDefault();
	//	//glfwMakeContextCurrent(backup_current_context);
	//}

	GLuint image_texture;
	//cv::Mat disp_frame;

	/*if (!freeze_frame)
		disp_frame = payload_frames[*context].front();*/

		//disp_frame = freeze_frame_mat;

	if ((disp_frame).empty())
	{
		std::cout << "image empty" << std::endl;
	}
	else
	{
		cv::cvtColor(disp_frame, disp_frame, cv::COLOR_BGR2RGBA);

		glGenTextures(1, &image_texture);
		glBindTexture(GL_TEXTURE_2D, image_texture);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Set texture clamping method
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_READ_COLOR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_READ_COLOR);
		glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);


		glTexImage2D(GL_TEXTURE_2D,		 // Type of texture
			0,					 // Pyramid level (for mip-mapping) - 0 is the top level
			GL_RGBA,			 // colour format to convert to
			(disp_frame).cols,	 // Image width
			(disp_frame).rows,	 // Image height
			0,					 // Border width in pixels (can either be 1 or 0)
			GL_RGBA,			 // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
			GL_UNSIGNED_BYTE,	 // Image data type
			(disp_frame).data); // The actual image data itself
		ImGui::Text("pointer = %p", image_texture);
		ImGui::Text("size = %d x %d", (disp_frame).cols, (disp_frame).rows);

		ImTextureID my_tex_id = reinterpret_cast<void*>(static_cast<intptr_t>(image_texture));
		float my_tex_w = (float)io.Fonts->TexWidth;
		float my_tex_h = (float)io.Fonts->TexHeight;
		{
			ImGui::Text("%.0fx%.0f", (disp_frame).cols, (float)(disp_frame).rows);
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImVec2 uv_min = ImVec2(0.0f, 0.0f);																						   // Top-left
			ImVec2 uv_max = ImVec2(1.0f, 1.0f);																						   // Lower-right
			ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);																		   // No tint
			ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);																		   // 50% opaque white
			ImGui::Image(my_tex_id, ImVec2((float)(disp_frame).cols, (float)(disp_frame).rows), uv_min, uv_max, tint_col, border_col); //reinterpret_cast<ImTextureID*>(my_frame_texture)

			if (ImGui::IsItemHovered())
			{//Tooltip feature that will allow zooming in on mouse hover
				ImGui::BeginTooltip();
				float region_sz = 32.0f;
				float region_x = io.MousePos.x - pos.x - region_sz * 0.5f;
				float region_y = io.MousePos.y - pos.y - region_sz * 0.5f;
				float zoom = 4.0f;
				if (region_x < 0.0f)
				{
					region_x = 0.0f;
				}
				else if (region_x > (disp_frame).cols - region_sz)
				{
					region_x = (disp_frame).cols - region_sz;
				}
				if (region_y < 0.0f)
				{
					region_y = 0.0f;
				}
				else if (region_y > (float)(disp_frame).rows - region_sz)
				{
					region_y = (float)(disp_frame).rows - region_sz;
				}
				ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
				ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
				ImVec2 uv0 = ImVec2((region_x) / (disp_frame).cols, (region_y) / (float)(disp_frame).rows);
				ImVec2 uv1 = ImVec2((region_x + region_sz) / (disp_frame).cols, (region_y + region_sz) / (float)(disp_frame).rows);
				ImGui::Image(my_tex_id, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
				ImGui::EndTooltip();
			}
		}
	}
}

bool CameraStream::streamCamera(int* camera)
{
	static bool input_thread_flag = true;
	ImGuiIO& io = ImGui::GetIO();

	if (ImGui::Button("Freeze Frame"))
	{ //if freeze frame is clicked. capture the current frame...
		vid_captures[*camera].read(freeze_frame_mat);
		freeze_frame = !freeze_frame;
	}


	{//Main "viewport"/context stream
		//You can use the "##" or "###" markers to use the same label with different id, or same id with different label.See documentation at the top of this file.
		ImGui::BeginChild("Camera_Viewport##cam_viewport", ImVec2((ImGui::GetCurrentWindow()->ContentSize.x) * 0.75f, 0.0f), true);

		if (input_thread_flag)
		{
			input_thread_flag = false;
			cam_threads.emplace_back(std::thread(BoxerUI_Inputs::input, std::ref(show_camera)));
			std::cout << "Input thread" << std::endl;
		}
		else if (cam_threads.empty()) {
			input_thread_flag = true;
		}
		if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow)) {
			io.WantCaptureKeyboard = false;
			//Dispatch inputs to BoxerUI_Inputs
			//input_type = InputType::Gamepad;
		   // std::cout << "Window in focus" << std::endl;
			//input_thread_flag = true;
		}
		else {
			io.WantCaptureKeyboard = true;
			//Dispatch Inputs to Inputs_Model
			//std::cout << "Window not in focus" << std::endl;
		}

		freeze_frame ? freezeFrame(camera) : setCamContext(*camera);
		ImGui::EndChild();
		ImGui::SameLine();
	}

	{ //Queue of streams on side child window
		ImGui::BeginChild("childCams", ImVec2(0.0f, 0.0f), true);
		for (int i = 0; i < (payload_frames).size(); i++)
		{
			if ((*camera) == i)
			{ //i.e. if the current index camera is in context, skip it in iteration and set its context to secondary in the side queue
				continue;
			}
			else
			{
				if (!payload_frames[i].empty())
				{
					//cv::resize(payload_frames[i].front(), payload_frames[i].front(), cv::Size(200,200));
					payload_frames[i].front();
				}

				setCamContext(i);
			} //TODO set the cameras prop so current context stream is appropriatly sized
		}
		ImGui::EndChild();
	}
	return true;
}

void CameraStream::freezeFrame(int* camera)
{

	std::cout << "Freeze frame: " << freeze_frame << std::endl;
	static int zoom_vert, zoom_hor = 0, zoom = 3;
	if (ImGui::Button("Enhance"))
	{
		//TODO: resize the image & sharpen to increase quality upon zoom
		//cv::resize(freeze_frame_img, freeze_frame_img, cv::Size(), 0.5, 0.5, cv::INTER_LINEAR);
		enhance = !enhance;
	}
	if (enhance)
	{   //TODO: Enhance image. i.e impl zooming into image without loosing image quality
		//ImGui::VSliderInt("Vertical", ImVec2(18, 160), &zoom_vert, 1, 5);
		//ImGui::SliderInt("Horizontal", &zoom_hor, 1, 5);
		//ImGui::SliderInt("Zoom", &zoom, 1, 5);
		//for (int i = 0; i < zoom_val; i++)
		//ImGui::Text("%*sThis is line %d", i * 4, "", i);
		//cv::Rect2d roi = //(zoom_vert, zoom_vert, freeze_frame_img.cols/2, freeze_frame_img.rows/2);

		//freeze_frame_img = freeze_frame_img(cv::selectROI(freeze_frame_img, false, false));
	}

	if (ImGui::Button("Screenshot"))
	{
		//TODO: take & save SS to file
		takeScreenshot();
	}
	bindCVMat2GLTexture(freeze_frame_mat);
}

void CameraStream::swapCamViews()
{ //TODO: Resume later. This is to allow the dragging and dropping of cam views on the UI to swap them out
	std::vector<cv::VideoCapture>::iterator camera = vid_captures.begin();
	int n = 0;
	for (; camera != vid_captures.end(); ++camera)
	{
		ImGui::PushID(n);
		if (n != 0)
			ImGui::SameLine();
		//streamCamera(&cameras[n],&frames[n]);

		// Our buttons are both drag sources and drag targets here!
		if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
		{
			// Set payload to carry the index of our item (could be anything)
			ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(cv::VideoCapture));
			ImGui::EndDragDropSource();
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
			{
				IM_ASSERT(payload->DataSize == sizeof(int));
				int payload_n = *(const int*)payload->Data;

				//Swap the camera streams
				const cv::VideoCapture tmp = vid_captures[n];
				vid_captures[n] = vid_captures[payload_n];
				vid_captures[payload_n] = tmp;
			}
			ImGui::EndDragDropTarget();
		}
		ImGui::PopID();
		n++;
	}
}

void CameraStream::initCamera()
{
	ImGui::Begin("OpenGL/OpenCV Camera Test##streamclosed");

	if (ImGui::Button("Open Camera"))
	{
		show_camera = !show_camera;
		//GLFWwindow* backup_current_context = glfwGetCurrentContext();
		//glfwMakeContextCurrent(backup_current_context);
		//glfwWindowHint(GLFW_FLOATING, show_camera ? GLFW_TRUE : GLFW_FALSE);		//If we are streaming keep window floating above others
	}
	if (show_camera)
	{
		displayCamera();
	}
	ImGui::End();
}

void CameraStream::displayCamera() {

	static int item_current = 0;

	static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);

	ImGui::Begin("OpenGL/OpenCV Camera Test##streamopened");

	if (ImGui::Button("Close Camera"))
		show_camera = !show_camera;

	//const ImVec2 x = ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);

	//switch camera in drop down
	const char* list_cameras[] = { "1", "2", "3", "4" };

	if (ImGui::Combo("List of Cameras", &item_current, list_cameras, IM_ARRAYSIZE(list_cameras)))
	{
		// if current item changes in the dropdown. the main context stream is swapped with the item_current stream in the queue
		std::cout << "item_current: " << item_current << std::endl;
	}
	ImGui::SameLine();
	HelpMarker(
		"Refer to the \"Combo\" section below for an explanation of the full BeginCombo/EndCombo API, "
		"and demonstration of various flags.\n");

	streamCamera(&item_current);
	ImGui::End();
}

//Should be for the user to set the directory they want to save and 
//read from
const char filePath[] = "/home/fof/catkin_ws/";

//This was way to simple for the time I put in. FML
void getFile(char* file, const char* name) {
	//std::strcat_s(file, filePath);
	//std::strcat_s(file, name);
}

void CameraStream::takeScreenshot() {
	std::time_t end_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	//const char* name = std::ctime(&end_time); char file1[100] = {};
	//getFile(file1, name);

	//cv::imwrite(file1, freeze_frame_mat); //have not tested with "freeze _frame_mat"   
}

cv::Mat loadScreenShots(const char* name) {
	char file2[100] = {};
	getFile(file2, name);

	return cv::imread(file2);
}


#ifdef _BOXERUI_TEST
void CameraStream::setCamContext(int context = 0)
{
	//*CameraStream::frames[context].data=CameraStream::frames_data[context];

#ifdef _WIN32
	//context==0?setCameraProp(context, cameras[context],)
	cameras[context].retrieve(frames[context]);
#else
	//cameras[context].read(frames[context]);
	cameras[context].read(frames[context]);
#endif
	//dispFrame(&frames[context]);
	BindCVMat2GLTexture(frames[context]);
}

void CameraStream::setCameraPropTest(int* camera, cv::VideoCapture* capture, float* w, float* h)
{
	//This method establishes the properties of each individual camera based on its initialization from initCamera() method
	if (!(*capture).isOpened())
	{
		std::cout << "Camera not opened" << std::endl;
	}
	else
	{
		std::cout << "Camera opened at: " << 0 << std::endl;
		std::cout << (*capture).getBackendName() << std::endl;
		std::cout << (*capture).get(cv::CAP_PROP_POS_FRAMES) << std::endl;
		(*capture).set(3, *w); //frame width
		(*capture).set(4, *h); //fram height
	}
}

void CameraStream::initCamera()
{
	//static bool show_camera = false;//, cam_stream_process = true;
	static int item_current = 0;
	static bool reset_frame = false;

	//ImGui::EndFrame();


	if (reset_frame) {
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();


		//glfwPollEvents();
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_AutoHideTabBar);
		static float capture_width, capture_height;
		for (int i = 0; i < NUM_CAMERAS; i++)
		{
			float temp_size = (ImGui::GetCurrentWindow()->ContentSize.x);
			//set and initialize the cameras
			//If index is 1, set the width & hwight to half its passed value. Else set it to a third of its value
			capture_width = (ImGui::GetCurrentWindow()->ContentSize.x) / (i == 0 ? temp_size : 5);
			capture_height = (ImGui::GetCurrentWindow()->ContentSize.y) / (i == 0 ? temp_size : 5);

			//set the camera properties
			//TODO change "i==0?1:0" --> i==0?*camera:0
			cameras[i] = cv::VideoCapture(i == 0 ? 1 : 0, cv::CAP_ANY);
			setCameraPropTest(&i, &cameras[i], (&capture_width), (&capture_height));
		}


		reset_frame = false;
	}
	/*ImGui::EndFrame();
	ImGui::Render();
	ImGui::UpdatePlatformWindows();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	ImGui::NewFrame();*/

	ImGui::Begin("OpenGL/OpenCV Camera Test###camstream");

	//printf("Child process starts with PID = %d\n", (int)getpid());
	if (ImGui::Button("Show Camera"))
	{
		show_camera = !show_camera;
		reset_frame = true;
	}
	if (show_camera)
	{

		//switch camera in drop down
		const char* list_cameras[] = { "1", "2", "3", "4" };

		if (ImGui::Combo("List of Cameras", &item_current, list_cameras, IM_ARRAYSIZE(list_cameras)))
		{
			// if current item changes in the dropdown. the main context stream is swapped with the item_current stream in the queue

			std::cout << "item_current: " << item_current << std::endl;
		}
		// capture_camera = item_current;
		ImGui::SameLine();
		HelpMarker(
			"Refer to the \"Combo\" section below for an explanation of the full BeginCombo/EndCombo API, "
			"and demonstration of various flags.\n");

		// if (show_camera)
		{
			streamCamera(&item_current);
		}
	}
	else
	{
		for (int i = 0; i < NUM_CAMERAS; i++)
		{
			destroyCamera(&i);
		}
	}

	ImGui::End();
	//return reset_frame;
}

void CameraStream::destroyCamera(int* index)
{
	if (frames.size() > 0)
	{
		frames[*index].~Mat();
		// return;

		//for internal testing purposes only
		cameras[*index].~VideoCapture();
	}
}

#else
void CameraStream::setCamContext(int context)
{
	//static bool payload_flag = true;
	if (!payload_frames[context].empty())
	{
		/*	if (payload_flag)
			{
			cam_threads.push_back(std::thread(bindCVMat2GLTexture, std::ref(context),std::ref(payload_frames)));
			payload_flag = false;
			}*/
		bindCVMat2GLTexture(payload_frames[context].front());
	}
	else
	{
		ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 0.5f), "Buffering %c", "|/-\\"[(int)(ImGui::GetTime() / 0.25f) & 3]);
	}
}

#endif