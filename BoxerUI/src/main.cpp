//Fix for profiling in VS: https://developercommunity.visualstudio.com/t/profiling-cpu-still-states-no-user-code-was-runnin/607535
#include "Application.h"


int main(int, char**)
{
	Application& boxerApp = Application::Get();
	return boxerApp.runApplication();
}
