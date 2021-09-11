#include "Boxer.h"
#include "Boxerpch.h"

BoxerUI_Monitor *BoxerUI_Monitor::monitor_instance = 0;

BoxerUI_Monitor *BoxerUI_Monitor::Get()
{
	if (BoxerUI_Monitor::monitor_instance == 0) //Checks num of references to the singleton is 0 for thread safety
	{
		monitor_instance = new BoxerUI_Monitor(); //Creates a new instance of BoxerUI_Monitor
	}
	return monitor_instance;
}

bool BoxerUI::cudaInfo()
{
	// bool cuda_found = false;
	// if (cv::cuda::getCudaEnabledDeviceCount() > 0)
	// {
	// 	std::cout << "Num of CUDA enabled devices: " << cv::cuda::getCudaEnabledDeviceCount() << std::endl;

	// 	cuda_found = true;
	// 	int i = cv::cuda::getCudaEnabledDeviceCount();

	// 	do
	// 	{
	// 		//cv::cuda::printCudaDeviceInfo(i);
	// 		cv::cuda::printShortCudaDeviceInfo(i);
	// 		i++;
	// 	} while (i <= 0);
	// }

	// return cuda_found;
}

const char *BoxerUI::getPath()
{
	std::filesystem::path pathToShow(BOXERUI_BIN_DIR);

	std::cout << "exists() = " << std::filesystem::exists(pathToShow) << "\n"
			  << "root_name() = " << pathToShow.root_name() << "\n"
			  << "root_path() = " << pathToShow.root_path() << "\n"
			  << "relative_path() = " << pathToShow.relative_path() << "\n"
			  << "parent_path() = " << pathToShow.parent_path() << "\n"
			  << "filename() = " << pathToShow.filename() << "\n"
			  << "stem() = " << pathToShow.stem() << "\n"
			  << "extension() = " << pathToShow.extension() << "\n";
}

std::string BoxerUI::appendPath( const char*  append){
	std::filesystem::path append_path(BOXERUI_ROOT_DIR);
	append_path /= append;

if (!std::filesystem::exists(append_path))
{
	std::cout<<"File not found!"<<std::endl;
}
 
	std::cout<<append_path<<std::endl;
	std::cout<<"FILENAME: "<<append_path.filename()<<std::endl;

	//const char* dest=append_path.generic_string().c_str();
	// append_path.~path();
	return append_path.generic_string();
	
}