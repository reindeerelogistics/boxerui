#pragma
#include "Window.h"
#include "Boxer.h"

namespace BoxerUI {
	class Windows : public Window {
	public:
		Windows(const WindowProps& props) ;
		//Windows() {};
		virtual ~Windows();

		void onUpdate() override;

		/** @brief Signal to system a close event has been made

		**/
		//void onClose() override;

		void setVsync(bool enable ) override;
		bool getVsync() const override { return isVsync; };
		bool isWindowClosed() const override { return glfwWindowShouldClose(m_window);};

		/*virtual void monitorCallback() override;
		virtual void errorCallback() override;
		virtual void windowCloseCallback() override;*/
		/*inline uint32_t getWidth() const overide { return }
		inline uint32_t getHeight() const overide { return }*/

	private:
		virtual int init(const WindowProps& props);
		virtual void shutdown();


		static void glfwMonitorCallback(GLFWmonitor* monitor, int event);
		static void glfwErrorCallback(int error, const char* description);
		static void glfwWindowCloseCallback(GLFWwindow* m_window);
	private:
		GLFWwindow* m_window;
		GLFWmonitor* m_monitor;

		bool isVsync;
		//bool m_isRunning;

	public:
		GLFWwindow* getWindow();


	};
}