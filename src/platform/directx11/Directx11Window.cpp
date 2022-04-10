#include "platform\directx11\Directx11Window.h"	

namespace BoxerUI {
	Windows::Windows(const WindowProps& props)
	{
		init(props);
	}
	Windows::~Windows() {
		shutdown();
	}
	void Windows::onUpdate()
	{

	}

	void Windows::onClose()
	{

	}
	void Windows::init(const WindowProps& props)
	{

	}
	void Windows::shutdown()
	{

	}

	Window* Window::Create(const WindowProps& props) {
		return new Windows(props);
	}
}