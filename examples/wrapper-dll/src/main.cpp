#include <iostream>
#include <format>
#include <windows.h>
import null.sdk;

class c_kernel32_dll : public memory::c_dll {
public: using c_dll::c_dll;
    memory::export_view_t<void(LPSYSTEM_INFO lpSystemInfo)> get_native_system_info{ get_export("GetNativeSystemInfo") };
    memory::export_view_t<BOOL(DWORD dwFreq, DWORD dwDuration)> beep{ get_export("Beep") };
    memory::export_view_t<void(DWORD dwMilliseconds)> sleep{ get_export("Sleep") };
} kernel32{ "kernel32.dll" };

int main() {
    try {
        SYSTEM_INFO sys_info{ };
        std::cout << std::format("sys_info.dwPageSize == {}\n", sys_info.dwPageSize);
        kernel32.get_native_system_info(&sys_info);
        std::cout << std::format("sys_info.dwPageSize == {}\n", sys_info.dwPageSize);
    } catch(const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}