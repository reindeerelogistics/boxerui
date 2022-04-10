# pragma once

#include "Boxerpch.h"
namespace BoxerUI {
	/** @brief This struct represents the properties utilized for cross platform windows initialization and management
	**/
	struct WindowProps {
		std::string Title;
		 int Width;
		 int Height;
		bool Vsync;
		/** @brief This struct represents the properties utilized for cross platform windows initialization and management
		
		**/
		WindowProps(const std::string& title = BOXERUI_APP_NAME,  int width = 1280,  int height = 720, bool enable_vsync=true)
			: Title(title), Width(width), Height(height), Vsync(enable_vsync) {
		}

	/*protected:
		WindowListener* listener_ = nullptr;
		GLFWwindow* window_ = nullptr;
		GLFWcursor* cursor_ibeam_;
		GLFWcursor* cursor_crosshair_;
		GLFWcursor* cursor_hand_;
		GLFWcursor* cursor_hresize_;
		GLFWcursor* cursor_vresize_;*/
	};

	class Window {
	public:
		virtual ~Window() {}

		virtual void onUpdate() = 0;
		//virtual void onClose() = 0;

		virtual void setVsync(bool enable) = 0;
		virtual bool getVsync() const = 0;
		virtual bool isWindowClosed() const = 0;


		//virtual uint32_t getWidth() const = 0;
		//virtual uint32_t getHeight() const = 0;

		/*virtual void onChangeFocus(bool focused) = 0;
		virtual void onKeyEvent(const KeyEvent& evt) = 0;
		virtual void onMouseEvent(const MouseEvent& evt) = 0;
		virtual void onScrollEvent(const ScrollEvent& evt) = 0;*/

		/** @brief This struct represents the properties utilized for creation of our window
			@param[in] WindowProps. Window properties for window initialization
			@return nothing.
		**/
		static Window* Create(const WindowProps& props = WindowProps());

		/*virtual void monitorCallback() = 0;
		virtual void errorCallback() = 0;
		virtual void windowCloseCallback() = 0;*/
	};


}