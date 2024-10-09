#include <iostream>

#include <null-sdk/memory/module/module.h>

class c_kernel32_dll : public ntl::c_dll {
public: using c_dll::c_dll;
public:
    c_export<void(LPSYSTEM_INFO lpSystemInfo)> get_native_system_info{ "kernel32.dll", "GetNativeSystemInfo" };
    c_export<BOOL(DWORD dwFreq, DWORD dwDuration)> beep{ this, "Beep" };
    c_export<void(DWORD dwMilliseconds)> sleep{ "kernel32.dll", "Sleep" };
} kernel32{ "kernel32.dll" };

int main() {
    try {
        SYSTEM_INFO sys_info{ };
        std::cout << std::format("sys_info.dwPageSize == {}\n", sys_info.dwPageSize);
        kernel32.get_native_system_info(&sys_info);
        std::cout << std::format("sys_info.dwPageSize == {}\n", sys_info.dwPageSize);

        {
            ntl::c_dll _kernel32("kernel32.dll");
            ntl::c_dll::c_export<BOOL(DWORD dwFreq, DWORD dwDuration)> beep(&_kernel32, "Beep");
            beep(750, 300);
        }

        {
            ntl::c_dll::c_export<BOOL(DWORD dwFreq, DWORD dwDuration)> beep("kernel32.dll", "Beep");
            beep(750, 300);
        }

        {
            ntl::c_dll::c_export<BOOL(DWORD dwFreq, DWORD dwDuration)> beep(ntl::c_dll("kernel32.dll").get_export("Beep"));
            beep(750, 300);
        }

        kernel32.beep(750, 300);
        kernel32.sleep(1000);
        kernel32.beep(750, 500);
    } catch(const std::exception &exception) {
        std::cout << exception.what() << std::endl;
    }
}