#pragma once
#include "Boxer.h"
#include "Boxerpch.h"
#include "BoxerUI_View.h"
#include "Components_View.h"
#include "Controller_input_Header.h"

#ifdef _WIN32

#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#endif

using CameraMap = std::map <int, std::queue<cv::Mat >>;

#define BUFFER_SIZE 5
#define NUM_CAMERAS 2

class CameraStream : public Components_View
{
public:
	bool show_camera;

	std::vector<std::thread> cam_threads;

	std::vector<cv::VideoCapture> vid_captures = std::vector<cv::VideoCapture>(NUM_CAMERAS);

	//std::shared_ptr<CameraMap> payload_frames=std::make_shared<CameraMap>();
	CameraMap payload_frames;
private:
	bool freeze_frame, enhance;

	cv::Mat freeze_frame_mat;

	cv::Mat sec_context_frame = cv::Mat(100, 100, CV_8UC1);

private:
	void bindCVMat2GLTexture(cv::Mat disp_frame);// , CameraMap& payload);

	//destroy the frame & cap objects then release from memory
	void destroyCamera(int* index);

	void setCameraPropTest(int* camera, cv::VideoCapture* capture, float* w, float* h);

	bool streamCamera(int* camera);

	void setCamContext(int context = 0);

	void freezeFrame(int* camera);

	void swapCamViews();

	void takeScreenshot();

	void displayCamera();


public:

	CameraStream()
		: freeze_frame(false), enhance(false),payload_frames(), show_camera(false),cam_threads()
	{}
	~CameraStream();

public:
	/** @brief This method establishes the properties of each individual camera based on its initialization from initCamera() method
	@param camera we are receiving stream from (indicated as an integer value),
	which video capture object we are accessing, and the applications width and height
	@return No values are returned. This is mearly a test and can be useful later.
	**/
	void initCamera();
	
	void destroyCamThreads();
};

