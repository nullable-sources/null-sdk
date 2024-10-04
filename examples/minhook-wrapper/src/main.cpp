#include <polyhook2/IHook.hpp>
#include <polyhook2/Detour/NatDetour.hpp>

#include <iostream>

#include <null-sdk/memory/minhook-wrapper.h>
#include <null-sdk/memory/polyhook-wrapper.h>

#ifdef NULLSDK_POLYHOOK_EXIST
struct message_box_t : ntl::polyhook::hook_t<message_box_t, int(WINAPI*)(HWND, LPCWSTR, LPCWSTR, UINT)> {
    static int WINAPI hook(HWND hwnd, LPCWSTR text, LPCWSTR caption, UINT type) {
        return original(hwnd, L"hooked", caption, type);
    }
};

struct printf_t : ntl::polyhook::hook_t<printf_t, int(__cdecl*)(const char*, ...)> {
    static int __cdecl hook(const char* format, ...) {
        return original("hooked printf\n");
    }
};
#else
struct message_box_t : ntl::minhook::hook_t<message_box_t, int(WINAPI*)(HWND, LPCWSTR, LPCWSTR, UINT)> {
    static int WINAPI hook(HWND hwnd, LPCWSTR text, LPCWSTR caption, UINT type) {
        return original(hwnd, L"hooked", caption, type);
    }
};

struct printf_t : ntl::minhook::hook_t<printf_t, int(__cdecl*)(const char*, ...)> {
    static int __cdecl hook(const char* format, ...) {
        return original("hooked printf\n");
    }
};
#endif

int main() {
#ifndef NULLSDK_POLYHOOK_EXIST
    ntl::minhook::initialize();
#endif


    printf("Not hooked...\n");
    MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

    message_box_t::setup(&MessageBoxW);
    printf_t::setup(&printf);

    printf("Not hooked...\n");
    MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

    message_box_t::disable();
    printf_t::disable();

    printf("Not hooked...\n");
    MessageBoxW(NULL, L"Not hooked...", L"MinHook Sample", MB_OK);

#ifndef NULLSDK_POLYHOOK_EXIST
        ntl::minhook::destroy();
#endif

    return 0;
}