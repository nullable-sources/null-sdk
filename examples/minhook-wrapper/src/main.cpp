#include <iostream>
#include <windows.h>
import null.sdk;

struct message_box_t : public memory::hook_t<message_box_t, int(WINAPI*)(HWND, LPCWSTR, LPCWSTR, UINT)> {
public:
    static int WINAPI hook(HWND hwnd, LPCWSTR text, LPCWSTR caption, UINT type) {
        return original(hwnd, L"hooked", caption, type);
    }
};

int main() {
    memory::minhook::initialize();

    MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

    message_box_t::setup(&MessageBoxW);

    MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

    message_box_t::disable();

    MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

    memory::minhook::destroy();

    return 0;
}