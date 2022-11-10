#include <utils/win/win.h>

namespace utils {
	namespace win {
		void c_window::time_data_t::initialize() {
			last_frame = std::chrono::steady_clock::now();
		}

		void c_window::time_data_t::begin_frame() {
			std::chrono::steady_clock::time_point current_time{ std::chrono::steady_clock::now() };
			delta_time = std::chrono::duration_cast<std::chrono::duration<float>>(current_time - last_frame).count();
			last_frame = current_time;
		}

		bool c_window::create() {
			if(!RegisterClassA(&wnd_class)) throw std::runtime_error{ "register class error" };

			wnd_handle = CreateWindowA(wnd_class.lpszClassName, name.c_str(), styles, pos.x, pos.y, size.x, size.y, nullptr, nullptr, instance, nullptr);
			if(wnd_handle) {
				SetWindowLongPtrA(wnd_handle, 0, (LONG_PTR)this);
				time_data.initialize();
				on_create();
			}

			return wnd_handle != nullptr;
		}

		void c_window::destroy() {
			on_destroy();

			if(!wnd_handle) throw std::runtime_error{ "window handle is nullptr" };
			if(!instance) throw std::runtime_error{ "instance is nullptr" };

			DestroyWindow(wnd_handle);
			UnregisterClassA(name.c_str(), instance);
		}

		void c_window::main_loop() {
			if(!wnd_handle) throw std::runtime_error{ "window handle is nullptr" };

			ShowWindow(wnd_handle, SW_SHOWDEFAULT);
			UpdateWindow(wnd_handle);

			MSG msg{ };
			while(msg.message != WM_QUIT) {
				if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
					TranslateMessage(&msg);
					DispatchMessageA(&msg);
					continue;
				}

				time_data.begin_frame();
				on_main_loop();
			}
		}

		vec2_t c_window::get_window_size() const {
			RECT wnd_rect{ };
			GetClientRect(wnd_handle, &wnd_rect);
			return { wnd_rect.right - wnd_rect.left, wnd_rect.bottom - wnd_rect.top };
		}

		LRESULT WINAPI c_window::wnd_proc(HWND _wnd_handle, UINT msg, WPARAM w_param, LPARAM l_param) {
			if(c_window * window{ (c_window*)GetWindowLongPtrA(_wnd_handle, 0) }) {
				const std::vector<std::any>& results{ window->on_wnd_proc(_wnd_handle, msg, w_param, l_param) };
				if(const auto& first_result{ std::ranges::find_if(results, [](const auto& result) { return result.has_value() && std::any_cast<int>(result) != -1; }) };
					first_result != results.end())
					return std::any_cast<int>(*first_result);
			}

			return DefWindowProcA(_wnd_handle, msg, w_param, l_param);
		}
	}

	namespace console {
		void attach() {
			if(!AllocConsole()) throw std::runtime_error{ "cant alloc console" };

			freopen_s(&old_out, "CONOUT$", "w", stdout);
			freopen_s(&old_in, "CONIN$", "r", stdin);
		}

		void detach() {
			fclose(old_out);
			fclose(old_in);
			FreeConsole();
		}

		bool i_command::handle(std::string_view str) {
			if(str.empty()) return false;

			for(std::string_view command : str | std::views::split(';') | std::views::transform([](const auto& splited) { return std::string_view{ splited }; })) {
				std::ranges::filter_view args{ command | std::views::split(' ') | std::views::filter([](const auto& arg) { return !arg.empty(); }) };
				if(args.empty()) continue;

				if(auto finded{ std::ranges::find_if(i_command::registered_commands, [&](const auto& command) { return command->name() == std::string{ (*args.begin()).begin(), (*args.begin()).end() }; }) }; finded != i_command::registered_commands.end()) {
					return (*finded)->execute({ std::next(args.begin()), args.end() });
				}
			}

			return false;
		}
	}
}