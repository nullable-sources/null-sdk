#include <iostream>

#include <null-sdk/utils/memory/minhook-wrapper.h>

struct message_box_t : ntl::hook_t<message_box_t, int(WINAPI*)(HWND, LPCWSTR, LPCWSTR, UINT)> {
    static int WINAPI hook(HWND hwnd, LPCWSTR text, LPCWSTR caption, UINT type) {
        return original(hwnd, L"hooked", caption, type);
    }
};

int main() {
    ntl::minhook::initialize();

    MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

    message_box_t::setup(&MessageBoxW);

    MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

    message_box_t::disable();

    MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

    ntl::minhook::destroy();

    return 0;
}