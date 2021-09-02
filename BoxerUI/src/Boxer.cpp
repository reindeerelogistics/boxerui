#include "Boxer.h"

BoxerUI_Monitor* BoxerUI_Monitor::monitor_instance = 0;

BoxerUI_Monitor* BoxerUI_Monitor::Get()
{
	if (BoxerUI_Monitor::monitor_instance == 0)		//Checks num of references to the singleton is 0 for thread safety
	{
		monitor_instance = new BoxerUI_Monitor();	//Creates a new instance of BoxerUI_Monitor
	}
	return monitor_instance;
}

bool BoxerUI::cudaInfo()
{
	bool cuda_found = false;
	if (cv::cuda::getCudaEnabledDeviceCount() > 0)
	{
		std::cout << "Num of CUDA enabled devices: " << cv::cuda::getCudaEnabledDeviceCount() << std::endl;

		cuda_found = true;
		int i = cv::cuda::getCudaEnabledDeviceCount();

		do
		{
			//cv::cuda::printCudaDeviceInfo(i);
			cv::cuda::printShortCudaDeviceInfo(i);
			i++;
		} while (i <= 0);
	}

	return cuda_found;
}


