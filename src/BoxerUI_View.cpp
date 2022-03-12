#include "BoxerUI_View.h"

namespace BoxerUI {

	void BoxerUI_View::showdemos()
	{ //bool show_demo_window) {

		bool show_another_window = false;
		bool show_demo_window = true;
		// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
		if (&show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);
		{
			bool p_open = false;
			if (&show_demo_window)
			{
				//ImPlot::CreateContext();
				//ImPlot::ShowDemoWindow(&p_open);
				//ImPlot::DestroyContext();
			}
		}
		// 3. Show another simple window.
		if (show_another_window)
		{
			ImGui::Begin("Another Window", &show_another_window); // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
			ImGui::Text("Hello from another window!");
			if (ImGui::Button("Close Me"))
				show_another_window = false;
			ImGui::End();
		}
	}

	void BoxerUI_View::displaySensors(double temperature, double battery)
	{
		static int counter = 0;
		static bool setTempBttn = false;
		//ImFont* title_style{};
		//titleStyle(title_style);

		{
			ImGui::Begin("My Table Test"); // , ImGuiWindowFlags_AlwaysAutoResize);

			{
				static ImGuiSelectableFlags selectFlags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiSelectableFlags_AllowDoubleClick;
				ImGui::BeginTable("table", 2);

				//static char *tableHeader[] = { "Sensors","Current","Max","Min" };
				//static char* sensors[] = { "Temperature","Battery","Tires","Min", "Min" };
				//titleStyle();
				ImGui::TableSetupColumn("Sensors", ImGuiTableColumnFlags_WidthStretch);
				ImGui::TableSetupColumn("Values", ImGuiTableColumnFlags_WidthStretch);
				ImGui::TableHeadersRow();
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				//ImGui::PushFont(title_style);
				ImGui::Text("Temperature");
				//ImGui::PopFont();
				//ImGui::PushFont(default_font);
				ImGui::TableNextColumn();
				ImGui::Text("%f", temperature);
				ImGui::TableNextRow();
				ImGui::TableNextColumn();
				ImGui::Text("Battery");
				ImGui::TableNextColumn();
				ImGui::Text("%f", battery);

				ImGui::EndTable();
			}

			if (ImGui::Button("change temperature"))
			{
				//boxerController.setModelTemperature(19.3);
				setTempBttn = true;
				//pid = CreateProcess();
			}
			if (setTempBttn)
			{
				ImGui::SameLine();
				ImGui::Text("Thanks for clicking me! Counter: %d", counter);
			}
			if (ImGui::Button("Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);
			ImGuiListClipper clipper;
			clipper.Begin(10); // We have 1000 elements, evenly spaced.
			while (clipper.Step())
				for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
				{
					ImGui::Text("line number %d", i);
				}

			ImGui::End();
		}
	}

	void BoxerUI_View::mainMenuBar() {
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				//ShowExampleMenuFile();
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
				if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Open Overlay", "CTRL+SHIFT+O")) {}
				if (ImGui::MenuItem("Quit", "Alt+F4")) {
					BoxerUI_Monitor* monitor = BoxerUI_Monitor::Get();
					monitor->m_appRunning = false;
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

	void BoxerUI_View::plotStream()
	{

		bool show_imgui_style_editor = false;
		//int   bar_data_A[11] = {3,11,1,5,6,1,1,9,7 };
		//int   bar_data_B[11] = {0, 1,2,3,4,5,6,7,8,9,10 };

		float xs1[1001], ys1[1001];
		for (int i = 0; i < 1001; ++i)
		{
			xs1[i] = i * 0.001f;
			ys1[i] = 0.5f + 0.5f * sinf(50 * (xs1[i] + (float)ImGui::GetTime() / 10));
		}
		static float xs2[11], ys2[11];
		for (int i = 0; i < 11; ++i)
		{
			xs2[i] = i * 0.1f;
			ys2[i] = xs2[i] * xs2[i];
		}

		//ImPlot::CreateContext();
		//ImGui::Begin("ImPlot Test###mainview", &show_imgui_style_editor);

		//if (ImPlot::BeginPlot("My Plot", "my x label", "my y label"))
		//{

		//	//ImPlot::PlotBars("My Bar Plot", bar_data, 11);
		//	ImPlot::PlotLine("My Line Plot1", xs1, ys1, 1001);
		//	ImPlot::SetNextMarkerStyle(ImPlotMarker_Diamond);
		//	ImPlot::PlotLine("My Line Plot2", xs2, ys2, 11);
		//	ImPlot::EndPlot();
		//}

		//ImGui::End();
		//ImPlot::DestroyContext();
	}

	void BoxerUI_View::signinWindow(bool* boxer_analytics)
	{ //, int ui_window_width, int ui_window_height) {
		bool p_open = true;

		static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);

		ImGui::SetNextWindowViewport(viewport->ID);
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		//ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

		const ImVec2 x = ImVec2(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y);

		//ImGui::SetWindowPos(ImVec2(GetCurrentWindow()->Pos.x,GetCurrentWindow()->Pos.y));

		//const ImVec2 pos = ImVec2(ImGui::GetCurrentWindow()->ContentSize.x *0.5, ImGui::GetCurrentWindow()->ContentSize.y*0.5);
		//ImGui::GetMainViewport()->Pos.x;
		//ImGui::GetMainViewport()->Size.x;
		//ImGui::GetWindowSize()->Size.x;
		//ImGui::GetWindowViewPort()->Size.x;
		//std::cout << ImGui::GetCurrentWindow()->Size.x << std::endl << ImGui::GetCurrentWindow()->Size.y;

		ImGui::Begin("Index", &p_open, flags); //, indexFlags);
		const ImVec2 pos = ImVec2(viewport->WorkPos.x + (viewport->WorkSize.x * 0.15f), viewport->WorkPos.y + (viewport->WorkSize.y * 0.15f));
		ImGui::SetNextWindowPos(pos); // pos);
		//ImGui::SetNextWindowPos);
		//ImGui::SetNextWindowPos(x, ImGuiCond_FirstUseEver);
		//ImGui::SameLine(ImGui::GetWindowWidth() / 2);
		ImGui::BeginChild("identification", ImVec2(0.0f, 0.0f), false); // , ImGuiWindowFlags_AlwaysAutoResize);

		ImGui::PushFont(ImGui::GetFont()->ContainerAtlas->Fonts[1]);
		ImGui::Text("Boxr");
		ImGui::PopFont();

		ImGuiInputTextFlags signin_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_NoUndoRedo;
		static char username[64], password[64];
		ImGui::InputTextWithHint("Username", "Username", username, IM_ARRAYSIZE(username), signin_flags);
		ImGui::SameLine();
		HelpMarker("Enter your credentials here");
		//std::cout << IsItemEdited() ? "True" : "False";
		ImGui::InputTextWithHint("Password", "Password", password, IM_ARRAYSIZE(password), signin_flags |= ImGuiInputTextFlags_Password);
		//ImGui::InputText("password (clear)", password, IM_ARRAYSIZE(password));

		ImGui::Spacing();
		if (button("Login"))
		{
			*boxer_analytics = false;
			std::cout << *boxer_analytics << std::endl;
		}

		ImGui::SameLine(185);
		//Indent(80.0f);
		if (ImGui::Button("Register", ImVec2(65, 30)))
		{
			//*boxer_analytics = false;
			std::cout << *boxer_analytics << std::endl;
		}
		ImGui::EndChild();
		ImGui::End();
	}

	void BoxerUI_View::views() {

		//viewDockspace();

		mainMenuBar();

		if (!sideNav())
		{
			//appFrameRate();
			mainViews();
		}
	}

	void BoxerUI_View::indexWindow() {
		ImFont* font1 = ImGui::GetFont();

		ImGui::PushFont(font1->ContainerAtlas->Fonts[2]); //BoxerUI_View::boxerUI_font);
		ImGui::Text("Boxer");
		ImGui::PopFont();
		ImGui::Separator();

	}

	bool BoxerUI_View::sideNav()
	{
		BoxerUI_Monitor* monitor = BoxerUI_Monitor::Get();
		static bool toggle_settings = false, index_window = false;

		if (toggle_settings)
		{
			toggle_settings = settings();
		}
		else
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();

			ImGui::SetNextWindowViewport(viewport->ID);
			const ImVec2 min_const = ImVec2((viewport->WorkSize.x) * 0.15f, (viewport->WorkSize.y));
			const ImVec2 max_const = ImVec2((viewport->WorkSize.x) * 0.45f, (viewport->WorkSize.y));
			static ImGuiWindowFlags flags;// = ImGuiWindowFlags_NoSavedSettings;// | ImGuiWindowFlags_NoTitleBar;

			//ImGui::SetWindowDock

			//ImGui::SetNextWindowPos(ImVec2(ImGui::GetMainViewport()->WorkPos.x, ImGui::GetMainViewport()->WorkPos.y));
			ImGui::SetNextWindowSizeConstraints(min_const, max_const);
			//ImGui::SetNextWindowSize(min_const, ImGuiCond_FirstUseEver);
			ImGui::Begin("SideNav", false, flags);
			contextMenu();
			//if(it->second == true)

			{
				//ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");

				//ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
				//Settings
				marginTop("Settings", ImVec2(2, 20));

				ImGui::PushFont(ImGui::GetFont()->ContainerAtlas->Fonts[4]);
				if (navButton(ICON_MD_SETTINGS "Settings##settings"))
				{
					//ImGui::BeginViewportSideBar	TODO

					cached_nav_item = nav_item;
					toggle_settings = !toggle_settings;
					nav_item = NavItem::Settings;
				}
				ImGui::PopFont();

				//ImGui::Rect()
				ImDrawList* draw_list = ImGui::GetWindowDrawList();
				draw_list->AddCircle(ImVec2(22, 22), 44.0f, ImU32());
				ImGui::Separator();
			}

			{
				//Home
				//marginTop("Home", ImVec2(2, 20));
				//ImGui::Indent(40.5f);
				//ImGui::SameLine(10.0f,2.0f);
				ImGui::Spacing();

				ImGui::PushFont(ImGui::GetFont()->ContainerAtlas->Fonts[4]);
				//ImGui::Text("%s##Home", ICON_MD_HOME);
				if (navButton(ICON_MD_HOME "Home##home"))
				{
					nav_item = NavItem::Home;
					index_window = !index_window;
				}
				//signinWindow(&index_window);
				ImGui::PopFont();
			}

			{
				//Camera Stream
				ImGui::Spacing();
				marginTop("Camera", ImVec2(2, 20));
				marginLeft("Camera", ImVec2(2, 20));
				ImGui::PushFont(ImGui::GetFont()->ContainerAtlas->Fonts[4]);
				//ImGui::Text("%s##Camera", ICON_MD_CAMERA);
				if (navButton(ICON_MD_CAMERA "Camera Stream##Camera"))
				{
					nav_item = NavItem::Stream;
				}
				ImGui::PopFont();
			}

			{
				//Analytics
			ImGui::Spacing();
				ImGui::PushFont(ImGui::GetFont()->ContainerAtlas->Fonts[4]);
				if (navButton(ICON_MD_TUNE "Analytics##stream"))
				{
					nav_item = NavItem::Analytics;
				}
				ImGui::PopFont();
			}

			ImGui::End();
		}

		return toggle_settings;
	}

	void BoxerUI_View::mainViews() {
		{
			BoxerUI_Monitor* monitor = BoxerUI_Monitor::Get();
			if (monitor->m_appRunning)
			{
				static ImGuiWindowFlags flags;// = ImGuiWindowFlags_NoSavedSettings;// | ImGuiWindowFlags_NoTitleBar;
				ImVec2 main_dis_viewport_size = ImGui::GetContentRegionAvail();
				const ImVec2 main_min_const = ImVec2((main_dis_viewport_size.x) * 0.55f, main_dis_viewport_size.y);
				const ImVec2 main_max_const = ImVec2((main_dis_viewport_size.x) * 0.75f, main_dis_viewport_size.y);

				//ImGui::SetNextWindowSizeConstraints(main_min_const, main_max_const);
				//ImGui::SetNextWindowSize(main_min_const, ImGuiCond_FirstUseEver);
				ImGui::Begin("mainView###mainview", false, flags);
				contextMenu();
				overlay();
				switch (nav_item)
				{

				case NavItem::Home:
					/* Go to home... */
					indexWindow();
					break;

				case NavItem::Settings:
					/* Go to settings... */

					break;

				case NavItem::Stream:
					/* Go to stream... */
					camera_stream.cameraView();
					break;

				case NavItem::Analytics:
					/* Go to Analytics... */
					plotStream();
					break;

				default:
					/* Go to home...*/
					break;
				}
				ImGui::End();
			}
			/*else
			{
				camera_stream.initCamera();
			}*/
		}
	}

	bool BoxerUI_View::settings()
	{
		//settings that will replace the sideNav upon toggle
		static bool keyboard = false, show_demos = false, dev_analytics = false;
		ImGuiIO& io = ImGui::GetIO();
		bool in_settings = true, open_dir = false;
		static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings;

		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);

		//ImFont* font1 = io.Fonts->AddFontFromFileTTF("font.ttf", size_pixels);
		/*
		ImGuiIO& io = ImGui::GetIO();*/
		ImFont* font1 = ImGui::GetFont(); // = io.Fonts->Fonts[0];

		if (ImGui::Begin("Settings", 0, flags)) {

			if (ImGui::BeginChild("Settings###primary", { keyboard ? (ImGui::GetCurrentWindow()->ContentSize.x * 0.45f) : 0.0f,0.0f }, false)) {

				ImGui::PushFont(font1->ContainerAtlas->Fonts[1]); //BoxerUI_View::boxerUI_font);
				ImGui::Text("Settings");
				ImGui::PopFont();
				//BoxerUI_View::boxerUI_fonts[2].b
				ImGui::Text("%s among %d items", ICON_FA_ALLERGIES, 2);
				ImGui::Button(ICON_FA_AMBULANCE " Search");

				ImGui::AlignTextToFramePadding();
				if (ImGui::ArrowButton("Return To Menu##backBttn", ImGuiDir_Left))
				{
					in_settings = false;
					nav_item = cached_nav_item;
				}

				//static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
				if (ImGui::Checkbox("Inputs", &keyboard)) // &flags, ImGuiItemStatusFlags_Focused))
				{
					//keyboard = !keyboard;

					std::cout << keyboard << std::endl;

				}

				// Edit a color (stored as ~4 floats)
				//ImGui::ColorEdit4("Color", my_color);

				// Plot some values
				const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
				ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));

				// Display contents in a scrolling region
				ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");


				if (button("ImGui Demo"))
				{
					show_demos = !show_demos;
				}
				if (show_demos)
				{
					showdemos();
				}

				if (button("Get FOnt"))
				{
					//getFontFile();
					fontFile();
				}

				if (button("Dev Analytics")) {
					dev_analytics = !dev_analytics;
				}
				if (dev_analytics) {
					ImGui::ShowFontSelector("Font Selector");
					ImGui::ShowMetricsWindow(&dev_analytics);
				}

				ImGui::EndChild();
			}

			ImGui::SameLine();

			ImGui::BeginChild("Settings###secondry", { 0.0f,0.0f }, true);
			{

				if (keyboard) {
					inputs(&keyboard);
				}


				ImGui::EndChild();
			}
			ImGui::End();
		}


		return in_settings;
	}

	void BoxerUI_View::inputs(bool* keyboard) {
		//if (ImGui::BeginChild("Inputs###secondary", { 0.0f,0.0f }, true)) {
		ImGuiIO& io = ImGui::GetIO();
		ImFont* font1 = ImGui::GetFont();

		ImGui::PushFont(font1->ContainerAtlas->Fonts[2]); //BoxerUI_View::boxerUI_font);
		ImGui::Text("Inputs");
		ImGui::PopFont();
		ImGui::SameLine();
		ImGui::SeparatorEx(ImGuiSeparatorFlags_Vertical);
		ImGui::SameLine();
		ImGui::Text("Text beside input");
		//keyboard ? input_type = InputType::Keyboard : input_type = InputType::None;
			/*else{std::cout << "Keyboard Not Selected" << std::endl;
				}*/

		keyboard ? io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard : ImGuiConfigFlags_NavEnableGamepad;

		//keyboard?input_type = InputType::Keyboard:input_type = InputType::None;
		//ImGuiConfigFlags_NavEnableGamepad = !ImGuiConfigFlags_NavEnableGamepad;
		/*else{std::cout << "Keyboard Not Selected" << std::endl;
			}*/
			//ImGui::EndChild();
		//}
	}

	void BoxerUI_View::indexView()
	{
		sideNav();
		plotStream();
		showdemos();
		appFrameRate();
	}

	void BoxerUI_View::viewDockspace() {

		//TODO: Logging, Create a submodule for opencv algo API, Patch/hotfix release will use MinSizeRel,
		//E.g. https://github.com/jayanam/jgl_demos/blob/3d887e28ee8566ab79365505be2eeff628387d9e/JGL_MeshLoader/source/render/ui_context.cpp
				//https://gist.github.com/PossiblyAShrub/0aea9511b84c34e191eaa90dd7225969
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGuiID dockspaceID = viewport->ID;
		static bool first_time = true;

		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;//ImGuiDockNodeFlags_NoCloseButton | ImGuiDockNodeFlags_NoWindowMenuButton | ImGuiDockNodeFlags_NoDocking | ImGuiDockNodeFlags_NoSplit | ImGuiDockNodeFlags_NoTabBar |
		//if (first_time)
		{
			first_time = false;
			//if (!ImGui::DockBuilderGetNode(dockspaceID)) 
			{
				ImGui::DockBuilderGetNode(dockspaceID);
				ImGui::DockBuilderRemoveNode(dockspaceID);
				ImGui::DockBuilderAddNode(dockspaceID, dockspace_flags);
				//ImGui::DockBuilderSetNodeSize(dockspaceID, ImVec2((viewport->WorkSize.x) * 0.15f, (viewport->WorkSize.y)));
				//ImGui::DockBuilderSetNodeSize(dockspaceID, viewport->Size);
				//ImGui::DockBuilderSetNodePos(dockspaceID, viewport->Pos);


				ImGuiID mainView = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Down, 0.8f, nullptr, &dockspaceID);
				ImGuiID sideNav = ImGui::DockBuilderSplitNode(dockspaceID, ImGuiDir_Left, 0.2f, nullptr, &dockspaceID);


				ImGui::DockBuilderDockWindow("mainView", mainView);
				ImGui::DockBuilderDockWindow("SideNav", sideNav);

				ImGui::DockBuilderFinish(dockspaceID);
			}
		}
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), dockspace_flags);
	}

	void BoxerUI_View::fontFile() {
		IFileOpenDialog* dlg = NULL;
		IShellItem* item = NULL;
		dlg->QueryInterface(&dlg);
		//item->QueryInterface();
		//dlg->SetFolder(BOXERUI_BIN_DIR);

	}
	HRESULT BoxerUI_View::getFontFile() {
		IFileDialog* getFont = NULL;

		HRESULT hr = getFont->QueryInterface(&getFont);
		//LPWSTR* pszName;
		if (SUCCEEDED(hr))
		{
			//getFont->GetFileName(pszName);

			getFont->Close(hr);
		}
		return hr;
	}

}