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

    window.callbacks.at<utils::win::e_window_callbacks::on_create>().add([]() { std::cout << "on_create" << std::endl; });
    window.callbacks.at<utils::win::e_window_callbacks::on_destroy>().add([]() { std::cout << "on_destroy" << std::endl; });

    window.callbacks.at<utils::win::e_window_callbacks::on_wnd_proc>().add(wnd_proc_1);
    window.callbacks.at<utils::win::e_window_callbacks::on_wnd_proc>().add(wnd_proc_2);

    try {
        window.create();
        window.main_loop();
        window.destroy();
    } catch(const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }

    return 0;
}