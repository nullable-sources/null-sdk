#include "win.h"

namespace utils::win {
	void c_window::time_data_t::initialize() {
		if(!QueryPerformanceFrequency((LARGE_INTEGER*)&ticks_per_second)) throw std::runtime_error("QueryPerformanceFrequency(&ticks_per_second) exception");
		if(!QueryPerformanceCounter((LARGE_INTEGER*)&time)) throw std::runtime_error("QueryPerformanceCounter(&time) exception");
	}

	void c_window::time_data_t::begin_frame() {
		std::uint64_t current_time{ };
		if(!QueryPerformanceCounter((LARGE_INTEGER*)&current_time)) throw std::runtime_error("QueryPerformanceCounter(&current_time) exception");

		delta_time = (float)(current_time - time) / ticks_per_second;
		time = current_time;
	}

	bool c_window::create() {
		if(!RegisterClassA(&wnd_class)) throw std::runtime_error("register class error");

		wnd_handle = CreateWindowA(wnd_class.lpszClassName, name.c_str(), styles, pos.x, pos.y, size.x, size.y, nullptr, nullptr, instance, nullptr);
		if(wnd_handle) {
			SetWindowLongPtrA(wnd_handle, 0, (LONG_PTR)this);
			time_data.initialize();
			render_create();
		}

		return wnd_handle != nullptr;
	}

	void c_window::destroy() {
		render_destroy();

		if(!wnd_handle) throw std::runtime_error("window handle is nullptr");
		if(!instance) throw std::runtime_error("instance is nullptr");

		DestroyWindow(wnd_handle);
		UnregisterClassA(name.c_str(), instance);
	}

	void c_window::main_loop(std::function<void()> function) {
		if(!wnd_handle) throw std::runtime_error("window handle is nullptr");

		ShowWindow(wnd_handle, SW_SHOWDEFAULT);
		UpdateWindow(wnd_handle);

		MSG msg{ };
		while(msg.message != WM_QUIT) {
			if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
				continue;
			}

			render_main_loop_begin();
			time_data.begin_frame();
			function();
			render_main_loop_end();
		}
	}

	vec2_t c_window::get_window_size() const {
		RECT wnd_rect{ 0, 0, 0, 0 };
		GetClientRect(wnd_handle, &wnd_rect);
		return { wnd_rect.right - wnd_rect.left, wnd_rect.bottom - wnd_rect.top };
	}

	LRESULT WINAPI c_window::wnd_proc(HWND _wnd_handle, UINT msg, WPARAM w_param, LPARAM l_param) {
		if(c_window* window; window = (c_window*)GetWindowLongPtrA(_wnd_handle, 0)) {
			const std::vector<std::any>& results = window->callbacks.call<int(HWND, UINT, WPARAM, LPARAM)>(e_window_callbacks::wnd_proc, _wnd_handle, msg, w_param, l_param);

			const auto& first_result = std::ranges::find_if(results, [](const auto& result) { return result.has_value() && std::any_cast<int>(result) != -1; });
			if(first_result != results.end()) return std::any_cast<int>(*first_result);
			

			if(int result = window->render_wnd_proc(_wnd_handle, msg, w_param, l_param); result > -1) return result;
		}

		return DefWindowProcA(_wnd_handle, msg, w_param, l_param);
	}
}