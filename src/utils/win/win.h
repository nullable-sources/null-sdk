#pragma once
#include <Windows.h>

#include <data-types/vec2.h>
#include <data-types/callbacks.h>

namespace utils {
	enum class e_window_callbacks {
		wnd_proc //std::function<int(HWND, UINT, WPARAM, LPARAM)>. If callback returns > -1 then DefWindowProc call will be skipped.
	};

	namespace win {
		class c_window {
		public:
			struct time_data_t {
				std::uint64_t ticks_per_second{ }, time{ };
				float delta_time{ };
				
				void initialize();
				void begin_frame();
			} time_data{ };

			single_callbacks_t<e_window_callbacks> callbacks{ };

			HWND wnd_handle{ nullptr };
			HINSTANCE instance{ };
			WNDCLASSA wnd_class{
				CS_CLASSDC,
				&c_window::wnd_proc,
				0,
				sizeof(c_window*),
				instance,
				LoadIcon(instance, MAKEINTRESOURCE(107)),
				LoadCursor(nullptr, IDC_ARROW),
				(HBRUSH)(COLOR_WINDOW),
				MAKEINTRESOURCEA(109),
				"null"
			};

			std::string name{ "null" };
			vec2_t pos{ 100, 100 }, size{ 800, 600 };

			std::uint32_t styles{ WS_OVERLAPPEDWINDOW };

		public:
			c_window() = default;
			c_window(HINSTANCE _instance) : instance(_instance) { }

			bool create();
			void destroy();

			void main_loop(std::function<void()> function);

			//virtual methods for render
			virtual void render_create() { }
			virtual void render_destroy() { }
			virtual void render_main_loop_begin() { }
			virtual void render_main_loop_end() { }
			virtual int render_wnd_proc(HWND _wnd_handle, UINT msg, WPARAM w_param, LPARAM l_param) { return -1; } //will be ignored if it returns -1

			//use for get size from wnd_handle
			vec2_t get_window_size() const;
		private:
			static LRESULT WINAPI wnd_proc(HWND _wnd_handle, UINT msg, WPARAM w_param, LPARAM l_param);
		};
	}
}