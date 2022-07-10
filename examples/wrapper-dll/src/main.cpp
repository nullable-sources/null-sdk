#include <iostream>
#include <null-sdk.h>

//https://docs.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress
class c_kernel32_dll : public utils::wrapper::dll::i_dll {
public:
    c_method<void(LPSYSTEM_INFO lpSystemInfo)> get_native_system_info{ this, "GetNativeSystemInfo" };
} kernel32{ "kernel32.dll" };

int main() {
    try {
        kernel32.load();

        SYSTEM_INFO sys_info{ };
        std::cout << std::format("sys_info.dwPageSize == {}\n", sys_info.dwPageSize);

        kernel32.get_native_system_info(&sys_info);

        std::cout << std::format("sys_info.dwPageSize == {}\n", sys_info.dwPageSize);

    } catch(const std::exception& exception) {
        std::cout << exception.what() << std::endl;
    }
}