#include <iostream>
#include <null-sdk.h>

class c_kernel32_dll : public utils::wrapper::dll::i_dll {
public:
    c_method<void(LPSYSTEM_INFO lpSystemInfo)> get_native_system_info{ this, "GetNativeSystemInfo" };
} kernel32{ "kernel32.dll" };

int main() {
    try {
        SYSTEM_INFO sys_info{ };
        std::cout << std::format("sys_info.dwPageSize == {}\n", sys_info.dwPageSize);
        kernel32.get_native_system_info(&sys_info);
        std::cout << std::format("sys_info.dwPageSize == {}\n", sys_info.dwPageSize);

        utils::wrapper::dll::i_dll::c_method<BOOL(DWORD dwFreq, DWORD dwDuration)> beep{ "kernel32.dll", "Beep" };
        utils::wrapper::dll::i_dll::c_method<BOOL(DWORD dwFreq, DWORD dwDuration)> beep2{ "kernel32.dll", "Beep" };
        beep(750, 300); beep2(750, 300);

    } catch(const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}