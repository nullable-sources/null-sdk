#pragma once
#include <Windows.h>
#include <format>

#include <data-types/vec2.h>
#include <data-types/callbacks.h>

namespace utils {
	enum class e_window_callbacks {
		on_create, //@note: void()
		on_destroy, //@note: void()
		on_main_loop, //@note: void()
		on_wnd_proc //@note: int(HWND, UINT, WPARAM, LPARAM). If callback returns != -1 then DefWindowProc call will be skipped.
	};

	namespace win {
		class c_window {
		public:
			struct time_data_t {
				std::chrono::steady_clock::time_point last_frame{ };
				float delta_time{ };
				
			public:
				void initialize();
				void begin_frame();
			} time_data{ };

		public:
			array_callbacks_t<e_window_callbacks> callbacks{ };

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
			c_window(const HINSTANCE& _instance) : instance(_instance) { }
			c_window(const HWND& _wnd_handle) : wnd_handle(_wnd_handle) { }

		public:
			bool create();
			void destroy();

			void main_loop();

			//@note: use for get size from wnd_handle
			vec2_t get_window_size() const;

			virtual void on_create() { callbacks.call<void()>(e_window_callbacks::on_create); }
			virtual void on_destroy() { callbacks.call<void()>(e_window_callbacks::on_destroy); }
			virtual void on_main_loop() { callbacks.call<void()>(e_window_callbacks::on_main_loop); }
			virtual std::vector<std::any> on_wnd_proc(HWND _wnd_handle, UINT msg, WPARAM w_param, LPARAM l_param) { return callbacks.call<int(HWND, UINT, WPARAM, LPARAM)>(e_window_callbacks::on_wnd_proc, _wnd_handle, msg, w_param, l_param); }

		private:
			static LRESULT WINAPI wnd_proc(HWND _wnd_handle, UINT msg, WPARAM w_param, LPARAM l_param);
		};
	}

	namespace console {
		struct handle_t {
		public:
			HANDLE out{ }, in{ };

		public:
			void get() { out = GetStdHandle(STD_OUTPUT_HANDLE); in = GetStdHandle(STD_INPUT_HANDLE); }
			void set() { if(out) SetStdHandle(STD_OUTPUT_HANDLE, out); if(in) SetStdHandle(STD_INPUT_HANDLE, in); }

			void set_mode() {
				SetConsoleMode(out, ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
				SetConsoleMode(in, ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);
			}

		public:
			operator bool() { return out && in; }
		};

		inline handle_t handle{ }, old_handle{ };

		static void attach() {
			old_handle.get();

			if(!AllocConsole()) throw std::runtime_error("cant alloc console");

			handle.get();
			handle.set_mode();
		}

		static void detach() {
			FreeConsole();
			old_handle.set();
		}

		template <typename... args_t>
		static void print(std::string_view text, args_t... args) {
			if(!handle) return;

			std::string buf{ std::vformat(text, std::make_format_args(args...)) };
			WriteConsoleA(handle.out, buf.c_str(), (DWORD)buf.size(), nullptr, nullptr);
		}

		static char read_key() {
			char key{ };
			DWORD keys_read{};

			if(handle) ReadConsoleA(handle.in, &key, 1, &keys_read, nullptr);

			return key;
		}
	}
}