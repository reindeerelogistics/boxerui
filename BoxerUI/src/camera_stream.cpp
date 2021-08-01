#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/utility.hpp>
#include <iostream>
using namespace std;

static int streamCamera(int capture_camera) {

	cv::VideoCapture cap = cv::VideoCapture(capture_camera, cv::CAP_ANY);
	cv::Mat frame;
	if (!cap.isOpened()) {
		cout << "Camera not opened" << endl;
		return -1;
	}
	else {
		cout << "Camera is opened at video camera: " << capture_camera << endl;
		cap.retrieve(frame);		//We are now streaming by retrieving the frames.

		//TODO: implement a buffer that will queue the frames for a seamless stream

		return 1;
	}

	frame.release();

return 0;
}