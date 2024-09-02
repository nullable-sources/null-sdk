#pragma once
#include <Windows.h>
#include <string>

namespace ntl::encoding {
    static std::string utf16_to_ascii(std::wstring_view utf16) {
        std::string ascii(WideCharToMultiByte(CP_ACP, 0, utf16.data(), utf16.size(), 0, 0, 0, 0), '\0');
        WideCharToMultiByte(CP_ACP, 0, utf16.data(), utf16.size(), ascii.data(), ascii.length(), 0, 0);
        return ascii;
    }

    static std::wstring ascii_to_utf16(std::string_view ascii) {
        std::wstring utf16(MultiByteToWideChar(CP_ACP, 0, ascii.data(), ascii.length(), 0, 0), L'\0');
        MultiByteToWideChar(CP_ACP, 0, ascii.data(), ascii.length(), utf16.data(), utf16.length());
        return utf16;
    }

    static std::string utf16_to_utf8(std::wstring_view utf16) {
        std::string utf8(WideCharToMultiByte(CP_UTF8, 0, utf16.data(), utf16.size(), 0, 0, 0, 0), '\0');
        WideCharToMultiByte(CP_UTF8, 0, utf16.data(), utf16.size(), utf8.data(), utf8.length(), 0, 0);
        return utf8;
    }

    static std::wstring utf8_to_utf16(std::string_view utf8) {
        std::wstring utf16(MultiByteToWideChar(CP_UTF8, 0, utf8.data(), utf8.length(), 0, 0), L'\0');
        MultiByteToWideChar(CP_UTF8, 0, utf8.data(), utf8.length(), utf16.data(), utf16.length());
        return utf16;
    }
}