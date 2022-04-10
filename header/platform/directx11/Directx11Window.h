#pragma
#include "Window.h"

//#include <GLFW/glfw3.h>

namespace BoxerUI {
	class Windows : public Window {
	public:
		Windows(const WindowProps& props);
		virtual ~Windows();

		void onUpdate() override;

		virtual void onClose() override ;


		/*virtual uint32_t getWidth() const override { ImGui return  };
		virtual uint32_t getHeight() const override { return };*/
		/*inline uint32_t getWidth() const overide { return }
		inline uint32_t getHeight() const overide { return }*/

	private:
		virtual void init(const WindowProps& props);
		virtual void shutdown();
	};
}