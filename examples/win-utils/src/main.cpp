#include <Windows.h>
import null.sdk;

int wnd_proc(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
    std::cout << "wnd proc" << std::endl;
    return -1;
}

int main(HINSTANCE instance) {
    utils::win::c_window window{ instance };

    window.callbacks.set<int(HWND, UINT, WPARAM, LPARAM)>(utils::e_window_callbacks::wnd_proc, wnd_proc);

    try {
        window.create();
        window.main_loop([&]() { std::cout << window.time_data.time << std::endl; });
        window.destroy();
    } catch (std::exception exp) {
        std::cout << exp.what() << std::endl;
    }

    return 0;
}