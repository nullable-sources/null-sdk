module;
#include <windows.h>
#include <string>
export module null.sdk:utils.win;

import :utils.logger;
import :utils.callbacks;
import :math.vec2;

export namespace utils {
	namespace win {
		enum class e_window_callbacks {
			on_create, //@note: void()
			on_destroy, //@note: void()
			on_main_loop, //@note: void()
			on_wnd_proc //@note: int(HWND, UINT, WPARAM, LPARAM). If callback returns != -1 then DefWindowProc call will be skipped.
		};
		using window_callbacks_t = callbacks_tuple_t<
			callbacks_t<e_window_callbacks::on_create, void()>,
			callbacks_t<e_window_callbacks::on_destroy, void()>,
			callbacks_t<e_window_callbacks::on_main_loop, void()>,
			callbacks_t<e_window_callbacks::on_wnd_proc, int(HWND, UINT, WPARAM, LPARAM)>
		>;

		class c_window {
		public:
			window_callbacks_t callbacks{ };

			HWND wnd_handle{ nullptr };
			HINSTANCE instance{ GetModuleHandle(nullptr) };
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
			vec2_t<int> pos{ 100, 100 }, size{ 800, 600 };

			std::uint32_t styles{ WS_OVERLAPPEDWINDOW };

		public:
			c_window() : wnd_handle{ GetActiveWindow() } { }
			c_window(const HINSTANCE& _instance) : instance{ _instance } { }
			c_window(const HWND& _wnd_handle) : wnd_handle{ _wnd_handle } { }

		public:
			virtual bool create() {
				if(!RegisterClassA(&wnd_class)) logger.log(e_log_type::error, "register class error");

				wnd_handle = CreateWindowA(wnd_class.lpszClassName, name.c_str(), styles, pos.x, pos.y, size.x, size.y, nullptr, nullptr, wnd_class.hInstance, nullptr);
				if(wnd_handle) {
					SetWindowLongPtrA(wnd_handle, 0, (LONG_PTR)this);
					on_create();
				}

				return wnd_handle != nullptr;
			}

			virtual void destroy() {
				on_destroy();

				if(!wnd_handle) logger.log(e_log_type::error, "window handle is nullptr.");
				if(!wnd_class.hInstance) logger.log(e_log_type::error, "instance is nullptr.");

				DestroyWindow(wnd_handle);
				UnregisterClassA(name.c_str(), wnd_class.hInstance);
			}

			virtual void main_loop() {
				if(!wnd_handle) logger.log(e_log_type::error, "window handle is nullptr.");

				ShowWindow(wnd_handle, SW_SHOWDEFAULT);
				UpdateWindow(wnd_handle);

				MSG msg{ };
				while(msg.message != WM_QUIT) {
					if(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
						TranslateMessage(&msg);
						DispatchMessageA(&msg);
						continue;
					}

					on_main_loop();
				}
			}

		public:
			//@note: use for get size from wnd_handle
			vec2_t<int> get_window_size() const {
				RECT wnd_rect{ };
				GetClientRect(wnd_handle, &wnd_rect);
				return { wnd_rect.right - wnd_rect.left, wnd_rect.bottom - wnd_rect.top };
			}

			template <typename char_t>
			void write_clipboard(const std::basic_string_view<char_t>& str) const {
				if(!OpenClipboard(wnd_handle)) logger.log(e_log_type::error, "cant open clipboard");

				EmptyClipboard();
				HGLOBAL data{ GlobalAlloc(GMEM_DDESHARE, sizeof(char_t) * (str.length() + 1)) };
				std::memcpy(GlobalLock(data), str.data(), sizeof(char_t) * (str.length() + 1));
				GlobalUnlock(data);

				SetClipboardData(std::is_same_v<char_t, wchar_t> ? CF_UNICODETEXT : CF_TEXT, data);
				if(!CloseClipboard()) logger.log(e_log_type::error, "cant clise clipboard");
			}

			template <typename char_t>
			std::basic_string<char_t> read_clipboard() const {
				if(!OpenClipboard(wnd_handle)) logger.log(e_log_type::error, "cant open clipboard.");

				std::basic_string<char_t> clipboard{ };
				if(HANDLE data{ GetClipboardData(std::is_same_v<char_t, wchar_t> ? CF_UNICODETEXT : CF_TEXT) }) {
					clipboard = (char_t*)GlobalLock(data);
				} else logger.log(e_log_type::warning, "cant get clipboard data.");

				if(!CloseClipboard()) logger.log(e_log_type::error, "cant clise clipboard.");
				return clipboard;
			}

			virtual void on_create() { callbacks.at<e_window_callbacks::on_create>().call(); }
			virtual void on_destroy() { callbacks.at<e_window_callbacks::on_destroy>().call(); }
			virtual void on_main_loop() { callbacks.at<e_window_callbacks::on_main_loop>().call(); }
			virtual std::vector<int> on_wnd_proc(HWND _wnd_handle, UINT msg, WPARAM w_param, LPARAM l_param) { return callbacks.at<e_window_callbacks::on_wnd_proc>().call(_wnd_handle, msg, w_param, l_param); }

		private:
			static LRESULT WINAPI wnd_proc(HWND _wnd_handle, UINT msg, WPARAM w_param, LPARAM l_param) {
				if(c_window* window{ (c_window*)GetWindowLongPtrA(_wnd_handle, 0) }) {
					const std::vector<int>& results{ window->on_wnd_proc(_wnd_handle, msg, w_param, l_param) };
					if(const auto& first_result{ std::ranges::find_if(results, [](const int& result) { return result != -1; }) };
						first_result != results.end())
						return *first_result;
				}

				if(msg == WM_CLOSE) PostQuitMessage(0);
				return DefWindowProcA(_wnd_handle, msg, w_param, l_param);
			}
		};
	}
}