//#pragma once
#include "imgui.h"
#include "imgui_internal.h"

//#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

using namespace ImGui;
using namespace std;
#define BUFFER_SIZE 5
#define NUM_CAMERAS 4

class CameraStream {
	bool freeze_frame = false, enhance = false;
	cv::VideoCapture cameras[NUM_CAMERAS];
	cv::Mat frames[NUM_CAMERAS], freeze_frame_img;
	GLuint my_frame_texture;
private:
	static void dispFrame(cv::Mat* frame)
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
			BindCVMat2GLTexture(&disp_frame);// , & my_frame_texture);

			disp_frame.release();
		}

		/*BindCVMat2GLTexture(frame);
		frame->release();*/
	}

	static void BindCVMat2GLTexture(cv::Mat* disp_frame)//, GLuint* image_texture)
	{
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

			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.cols, image.rows, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.ptr());
			glTexImage2D(GL_TEXTURE_2D,	   // Type of texture
				0,				   // Pyramid level (for mip-mapping) - 0 is the top level
				GL_RGB,		   // colour format to convert to
				(*disp_frame).cols,	   // Image width
				(*disp_frame).rows,	   // Image height
				0,				   // Border width in pixels (can either be 1 or 0)
				GL_RGBA,		   // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
				GL_UNSIGNED_BYTE, // Image data type
				(*disp_frame).data);	   // The actual image data itself
			ImGui::Text("pointer = %p", image_texture);
			ImGui::Text("size = %d x %d", (*disp_frame).cols, (*disp_frame).rows);
			ImGui::Image((void*)(intptr_t)image_texture, ImVec2((float)(*disp_frame).cols, (float)(*disp_frame).rows)); //reinterpret_cast<ImTextureID*>(my_frame_texture)
		}

	}
public: 
	void initCamera(bool* show_camera, float* w, float* h) {
		if (show_camera)
		{
			float capture_width, capture_height;
			for (int i = 0; i < NUM_CAMERAS; i++)
			{
				//set and initialize the cameras
				//If index is 0, set the width & hwight to half its passed value. Else set it to a third of its value
				capture_width = (*w) / (i == 0 ? 2 : 5);
				capture_height = (*h) / (i == 0 ? 2 : 5);

				//set the camera properties
				setCameraProp(&i, &cameras[i], (&capture_width), (&capture_height));
			}

			//for (int i = 0; i < NUM_CAMERAS; i++)
			//{//stream the data and bind to unique Mat objects
				//if (show_camera) {
				//streamCamera();
				//}
			//}

		}
		else
		{
			for (int i = 0; i < NUM_CAMERAS; i++)
			{//destroy the frame & cap objects then release from memory
				//if (show_camera) { //TODO move to initCamera(). Might break something not sure what yet.				
				cameras[i].~VideoCapture();
				frames[i].~Mat();
				//}
			}
		}
	}

	/** @brief This method establishes the properties of each individual camera based on its initialization from initCamera() method

	@param camera we are receiving stream from (indicated as an integer value),
	which video capture object we are accessing, and the applications width and height
	@return No values are returned. This is mearly a test and can be useful later.
	**/
	void setCameraProp(int* camera, cv::VideoCapture* capture, float* w, float* h) { 
		//change param of line below from 0 to *camera
		*(capture) = cv::VideoCapture(*camera == 0 ? 1 : 0, cv::CAP_ANY);
		if (!(*capture).isOpened())
		{
			cout << "Camera not opened" << endl;
		}
		else
		{
			cout << "Camera opened at: " << 0 << endl;
			cout << (*capture).getBackendName() << endl;
			cout << (*capture).get(cv::CAP_PROP_POS_FRAMES) << endl;
			(*capture).set(3, *w);  //frame width
			(*capture).set(4, *h); //fram height
		}
	}


	void streamCamera(int* camera) {//cv::VideoCapture* cap,cv::Mat* frame) {//stream the data and bind to unique Mat objects

		if (Button("Freeze Frame")) {//if freeze frame is clicked. capture the current frame...
			freeze_frame = !freeze_frame;
			//if (freeze_frame)
			cameras[*camera].read(freeze_frame_img);
		}

		//if (*camera == 0)
		{
			ImGui::BeginChild("Main_Viewport", ImVec2((ImGui::GetCurrentWindow()->ContentSize.x) * 0.75f, 0.0f), true);
			//camera == 0 ?
			setCamContext();
			//: setCamContext(*camera);
			ImGui::EndChild();
			ImGui::SameLine();
		}

		ImGui::BeginChild("childCam", ImVec2(0.0f, 0.0f), true);
		for (int i = 1; i < NUM_CAMERAS; i++)
		{
			setCamContext(i);
		}
		ImGui::EndChild();

	}

	void setCamContext(int context = 0) {

#ifdef _WIN32
		//context==0?setCameraProp(context, cameras[context],)
		cameras[context].retrieve(frames[context]);
#else
		cameras[context].read(frames[context]);
#endif


		if (freeze_frame) { freezeFrame(); }
		else
		{
			dispFrame(&frames[context]);
		}
	}

	void freezeFrame() {
		if (freeze_frame)
		{//... and render onto screen through similar process as streaming as video
			cout << "Freeze frame: " << freeze_frame << endl;
			//cv::Mat freeze_frame_img;
			//freeze_frame_img=frame.clone();
			BindCVMat2GLTexture(&freeze_frame_img);// , & frame_texture);
			static int  zoom_vert, zoom_hor = 0, zoom = 3;
			if (Button("Enhance")) {
				//TODO: resize the image & sharpen to increase quality upon zoom
				//cv::resize(freeze_frame_img, freeze_frame_img, cv::Size(), 0.5, 0.5, cv::INTER_LINEAR);
				enhance = !enhance;
			}
			if (enhance) {
				//ImGui::VSliderInt("Vertical", ImVec2(18, 160), &zoom_vert, 1, 5);
				//ImGui::SliderInt("Horizontal", &zoom_hor, 1, 5);
				//ImGui::SliderInt("Zoom", &zoom, 1, 5);
				//for (int i = 0; i < zoom_val; i++)
					//ImGui::Text("%*sThis is line %d", i * 4, "", i);
				//cv::Rect2d roi = //(zoom_vert, zoom_vert, freeze_frame_img.cols/2, freeze_frame_img.rows/2);

				freeze_frame_img = freeze_frame_img(cv::selectROI(freeze_frame_img, false, false));
			}
		}
	}


	void swapCamViews() {//TODO: Resume later. This is to allow the dragging and dropping of cam views on the UI to swap them out

		for (int n = 0; n < IM_ARRAYSIZE(cameras); n++)
		{
			ImGui::PushID(n);
			if (n != 0)
				ImGui::SameLine();
			//ImGui::Button(viewCameras[n], ImVec2(60, 60));
			//streamCamera(&cameras[n],&frames[n]);


			// Our buttons are both drag sources and drag targets here!
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_None))
			{
				// Set payload to carry the index of our item (could be anything)
				ImGui::SetDragDropPayload("DND_DEMO_CELL", &n, sizeof(cv::VideoCapture));

				// Display preview (could be anything, e.g. when dragging an image we could decide to display
				// the filename and a small preview of the image, etc.)
				//if (mode == Mode_Copy) { ImGui::Text("Copy %s", names[n]); }
				//if (mode == Mode_Move) { ImGui::Text("Move %s", names[n]); }
				//if (mode == Mode_Swap) { ImGui::Text("Swap %s", names[n]); }

				//n == 0 ? cameraContext() :

				ImGui::EndDragDropSource();
			}
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_DEMO_CELL"))
				{
					IM_ASSERT(payload->DataSize == sizeof(int));
					int payload_n = *(const int*)payload->Data;
					/*if (mode == Mode_Copy)
					{
						names[n] = names[payload_n];
					}
					if (mode == Mode_Move)
					{
						names[n] = names[payload_n];
						names[payload_n] = "";
					}
					if (mode == Mode_Swap)
					{*/
					const cv::VideoCapture tmp = cameras[n];
					cameras[n] = cameras[payload_n];
					cameras[payload_n] = tmp;
					//}
				}
				ImGui::EndDragDropTarget();
			}
			ImGui::PopID();
		}

	}
};