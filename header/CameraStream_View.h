#pragma once
//#include "Boxer.h"
#include "Components_View.h"
#include "CameraStream_Model.h"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/stitching.hpp"
#include <opencv2/core/utility.hpp>

//using CameraMapValue = ;
using CameraMap = std::map <int, std::queue<cv::Mat>>;

#define BUFFER_SIZE 5
#define NUM_CAMERAS 1

class CameraStream : public Components_View
{
public:
	bool show_camera;

	std::map<const char*, bool> context_items;

	std::vector<std::thread> cam_threads;

	std::vector<cv::VideoCapture> vid_captures = std::vector<cv::VideoCapture>(NUM_CAMERAS);

	std::string cam1, cam2;
	//std::shared_ptr<std::map <int,std::queue<cv::Mat>>>payload_frames=std::make_shared<CameraMap>();
   //std::shared_ptr<CameraMap> payload_frames;
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
		: freeze_frame(false), 
		context_items({ {"Close Camera",false},{"Camera FPS",false} }),
		enhance(false),
		payload_frames(),
		show_camera(true),
		cam_threads(),
		//cam1("udpsrc port=5000 ! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG,framerate=30/1 ! rtpjpegdepay ! jpegdec ! videoconvert ! appsink"),
		cam1("ksvideosrc device-index=0 ! videoconvert n-threads=2 ! appsink"),
		// gst-launch-1.0 autovideosrc ! video/x-raw,width=320,height=240 ! videoconvert ! facedetect min-size-width=60 min-size-height=60 ! colorspace ! xvimagesink
		//cam1("autovideosrc ! video/x-raw,width=1440,height=900,framerate=30/1 ! videoconvert n-threads=2 ! appsink"),
		//cam1("camerabin ! appsink"),
		//cam1("appsrc ! videoconvert n-threads=2 ! autovideosink"),
		cam2()
	{
		//payload_frames = std::make_shared<CameraMap>();
	}
	~CameraStream();

public:
	/** @brief This method establishes the properties of each individual camera based on its initialization from initCamera() method
	@param camera we are receiving stream from (indicated as an integer value),
	which video capture object we are accessing, and the applications width and height
	@return No values are returned. This is mearly a test and can be useful later.
	**/
	void initCamera();

	bool destroyCamThreads();

	void cameraView();

	int stitchingTest();
};

