#include <Windows.h>
import null.sdk;

bool wnd_proc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
    std::cout << "wnd proc" << std::endl;
    return false;
}

int main(HINSTANCE instance) {
    utils::win::c_window window{ instance };

    window.callbacks.set<bool(HWND, UINT, WPARAM, LPARAM)>(utils::e_window_callbacks::wnd_proc, wnd_proc);

    try {
        window.create();
        window.main_loop([&]() { std::cout << window.time_data.time << std::endl; });
        window.destroy();
    } catch (std::exception exp) {
        std::cout << exp.what() << std::endl;
    }

    return 0;
}