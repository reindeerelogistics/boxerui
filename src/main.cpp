#include "Application.h"


int main(int, char**)
{
	Application& boxerApp = Application::Get();
	return boxerApp.runApplication();
}
