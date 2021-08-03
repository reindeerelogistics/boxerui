#pragma once
#include "Boxer.h"
#include "BoxerUI_View.h"
#include "Components_View.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp> //Note: no need to include these headers in the working file. These will be handled automatically by linker

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include <future>
#include <map>
#include <queue>


#ifdef _WIN32

#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#endif

using CameraMap = std::map <int, std::queue<cv::Mat >>;

//#ifndef CAMERASTREAM_VIEW_H_
//...
//#endif // !CAMERASTREAM_VIEW_H_
//Preprocessor. Checks if the symbol has been not bee ndefined. Use #pragma, it includes the symbol once

#define BUFFER_SIZE 5
#define NUM_CAMERAS 1
#define FREEZE_FRAME_IMG (NUM_CAMERAS+1)

class CameraStream : public Components_View
{

	static bool freeze_frame, enhance;

	cv::Mat freeze_frame_mat;

	void dispFrame(cv::Mat* frame);

	void BindCVMat2GLTexture(cv::Mat* disp_frame);

	//destroy the frame & cap objects then release from memory
	void destroyCamera(int *index);

	void setCameraPropTest(int *camera, cv::VideoCapture *capture, float *w, float *h);

	 bool streamCamera(int* camera);

	 void setCamContext(int context=0);

	 void freezeFrame();

	void swapCamViews();

	void takeScreenshot();

public:
	std::vector<cv::VideoCapture> vid_captures = std::vector<cv::VideoCapture>(NUM_CAMERAS);
	
	cv::Mat frame= cv::Mat(100, 100, CV_8UC4);

	static bool show_camera;

	//static std::shared_ptr<CameraMap> payload_frames;
	static CameraMap payload_frames;
	
	std::future<CameraMap> cam_futures;


	std::vector<std::thread> cam_threads;

	/** @brief This method establishes the properties of each individual camera based on its initialization from initCamera() method
	@param camera we are receiving stream from (indicated as an integer value),
	which video capture object we are accessing, and the applications width and height
	@return No values are returned. This is mearly a test and can be useful later.
	**/
	void initCamera();

	
};
