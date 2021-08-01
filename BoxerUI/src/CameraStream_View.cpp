#include "CameraStream_View.h"

bool CameraStream::freeze_frame = false;
bool CameraStream::enhance = false;
CameraMap CameraStream::payload_frames = {};

void CameraStream::dispFrame(cv::Mat *frame)
{
	//creates a buffer of 5 frames before binding cv::Mat type to GLTexture
	cv::Mat frames_buf[BUFFER_SIZE];
	//GLuint my_frame_texture;
	for (int i = 0; i < BUFFER_SIZE; i++)
	{
		frames_buf[i] = *frame;
		(*frame).~Mat();
	}
	for (int i = 0; i < 5; i++)
	{
		cv::Mat disp_frame = cv::Mat(100, 100, CV_64FC1);

		disp_frame = frames_buf[i];
		BindCVMat2GLTexture(&disp_frame); // , & my_frame_texture);

		disp_frame.release();
	}
}

void CameraStream::BindCVMat2GLTexture(cv::Mat* disp_frame)
{
	ImGuiIO &io = ImGui::GetIO();
	GLuint image_texture;
	if ((*disp_frame).empty())
	{
		std::cout << "image empty" << std::endl;
	}
	else
	{
		cv::cvtColor(*disp_frame, *disp_frame, cv::COLOR_BGR2RGBA);

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
			(*disp_frame).cols,	 // Image width
			(*disp_frame).rows,	 // Image height
			0,					 // Border width in pixels (can either be 1 or 0)
			GL_RGBA,			 // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
			GL_UNSIGNED_BYTE,	 // Image data type
			(*disp_frame).data); // The actual image data itself
		ImGui::Text("pointer = %p", image_texture);
		ImGui::Text("size = %d x %d", (*disp_frame).cols, (*disp_frame).rows);

		ImTextureID my_tex_id = reinterpret_cast<void*>(static_cast<intptr_t>(image_texture));
		float my_tex_w = (float)io.Fonts->TexWidth;
		float my_tex_h = (float)io.Fonts->TexHeight;
		{
			ImGui::Text("%.0fx%.0f", (*disp_frame).cols, (float)(*disp_frame).rows);
			ImVec2 pos = ImGui::GetCursorScreenPos();
			ImVec2 uv_min = ImVec2(0.0f, 0.0f);																						   // Top-left
			ImVec2 uv_max = ImVec2(1.0f, 1.0f);																						   // Lower-right
			ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);																		   // No tint
			ImVec4 border_col = ImVec4(1.0f, 1.0f, 1.0f, 0.5f);																		   // 50% opaque white
			ImGui::Image(my_tex_id, ImVec2((float)(*disp_frame).cols, (float)(*disp_frame).rows), uv_min, uv_max, tint_col, border_col); //reinterpret_cast<ImTextureID*>(my_frame_texture)

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
				else if (region_x > (*disp_frame).cols - region_sz)
				{
					region_x = (*disp_frame).cols - region_sz;
				}
				if (region_y < 0.0f)
				{
					region_y = 0.0f;
				}
				else if (region_y > (float)(*disp_frame).rows - region_sz)
				{
					region_y = (float)(*disp_frame).rows - region_sz;
				}
				ImGui::Text("Min: (%.2f, %.2f)", region_x, region_y);
				ImGui::Text("Max: (%.2f, %.2f)", region_x + region_sz, region_y + region_sz);
				ImVec2 uv0 = ImVec2((region_x) / (*disp_frame).cols, (region_y) / (float)(*disp_frame).rows);
				ImVec2 uv1 = ImVec2((region_x + region_sz) / (*disp_frame).cols, (region_y + region_sz) / (float)(*disp_frame).rows);
				ImGui::Image(my_tex_id, ImVec2(region_sz * zoom, region_sz * zoom), uv0, uv1, tint_col, border_col);
				ImGui::EndTooltip();
			}
		}
	}
}

bool CameraStream::streamCamera(int* camera)
{
ImGuiIO& io = ImGui::GetIO();
	if (ImGui::Button("Freeze Frame"))
	{ //if freeze frame is clicked. capture the current frame...
		freeze_frame = !freeze_frame;

		//TODO: clone the main context frame to freeze frame then display
		//cameras[*camera].retrieve(frames[FREEZE_FRAME_IMG]);
	}

	
	{//Main "viewport"/context stream
		//You can use the "##" or "###" markers to use the same label with different id, or same id with different label.See documentation at the top of this file.
		ImGui::BeginChild("Camera_Viewport##cam_viewport", ImVec2((ImGui::GetCurrentWindow()->ContentSize.x) * 0.75f, 0.0f), true);

		if (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootWindow)) {
			io.WantCaptureKeyboard = false;
			//input_type = InputType::Gamepad;
			//Dispatch inputs to Boxer_Inputs
			std::cout << "Window in focus" << std::endl;
		}
		else {

			io.WantCaptureKeyboard = true;
			//Dispatch Inputs to BoxerUI_Inputs
			std::cout << "Window not in focus" << std::endl;
		}

		freeze_frame ? freezeFrame() : setCamContext(*camera);
		//: setCamContext(*camera);
		ImGui::EndChild();
		ImGui::SameLine();
	}

	{ //Queue of streams on side child window
		ImGui::BeginChild("childCams", ImVec2(0.0f, 0.0f), true);
		for (int i = 0; i < NUM_CAMERAS; i++)
		{
			if ((*camera) == i)
			{ //i.e. if the current index camera is in context, skip it in iteration and set its context to secondary in the side queue
				continue;
			}
			else
			{
				setCamContext(i);
			} //TODO set the cameras prop so current context stream is appropriatly sized
		}
		ImGui::EndChild();
	}
	return true;
}

void CameraStream::freezeFrame()
{
	std::cout << "Freeze frame: " << freeze_frame << std::endl;
	//cv::Mat freeze_frame_img;
	//freeze_frame_img=frame.clone();
	//BindCVMat2GLTexture(frames);// .at(FREEZE_FRAME_IMG));
	static int zoom_vert, zoom_hor = 0, zoom = 3;
	if (ImGui::Button("Enhance"))
	{
		//TODO: resize the image & sharpen to increase quality upon zoom
		//cv::resize(freeze_frame_img, freeze_frame_img, cv::Size(), 0.5, 0.5, cv::INTER_LINEAR);
		enhance = !enhance;
	}
	if (enhance)
	{	//TODO: Enhance image. i.e impl zooming into image without loosing image quality
		//ImGui::VSliderInt("Vertical", ImVec2(18, 160), &zoom_vert, 1, 5);
		//ImGui::SliderInt("Horizontal", &zoom_hor, 1, 5);
		//ImGui::SliderInt("Zoom", &zoom, 1, 5);
		//for (int i = 0; i < zoom_val; i++)
		//ImGui::Text("%*sThis is line %d", i * 4, "", i);
		//cv::Rect2d roi = //(zoom_vert, zoom_vert, freeze_frame_img.cols/2, freeze_frame_img.rows/2);

		//freeze_frame_img = freeze_frame_img(cv::selectROI(freeze_frame_img, false, false));
	}
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
			if (const ImGuiPayload *payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
			{
				IM_ASSERT(payload->DataSize == sizeof(int));
				int payload_n = *(const int *)payload->Data;

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
	 bool fx = true;
	 //CameraStream::frame=*data;
	
	static int item_current = 0;

	{
		ImGui::Begin("OpenGL/OpenCV Camera Test###camstream");

		if (ImGui::Button("Show Camera"))
			show_camera = !show_camera;

		if (show_camera)
		{
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

			//TODO Create thread here to process streaming content to window
			//std::async(std::launch::async, &CameraStream::streamCamera, std::ref(item_current), std::ref(freeze_frame));
			//auto f=std::async(std::launch::async, [] {return CameraStream::streamCamera(item_current, freeze_frame); });
			//f.get();
			streamCamera(&item_current);
		}
		ImGui::End();
	}
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
	BindCVMat2GLTexture(&payload_frames[context][context]);
	payload_frames[context][context].~Mat();
}

#endif
