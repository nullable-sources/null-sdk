#include <iostream>
#include <null-sdk.h>

int wnd_proc_1(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
    std::cout << "wnd proc 1" << std::endl;
    return -1;
}

int wnd_proc_2(HWND hwnd, UINT msg, WPARAM w_param, LPARAM l_param) {
    std::cout << "wnd proc 2" << std::endl;
    return -1;
}

int main(HINSTANCE instance) {
    utils::win::c_window window{ instance };

    window.callbacks.add<int(HWND, UINT, WPARAM, LPARAM)>(utils::e_window_callbacks::wnd_proc, wnd_proc_1);
    window.callbacks.add<int(HWND, UINT, WPARAM, LPARAM)>(utils::e_window_callbacks::wnd_proc, wnd_proc_2);

    try {
        window.create();
        window.main_loop([&]() { std::cout << window.time_data.time << std::endl; });
        window.destroy();
    } catch(const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    return 0;
}