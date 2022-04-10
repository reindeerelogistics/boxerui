#include "Application.h"


int main(int argc, char** argv)
{
	Application& boxerApp = Application::Get();
	return boxerApp.runApplication();
}
