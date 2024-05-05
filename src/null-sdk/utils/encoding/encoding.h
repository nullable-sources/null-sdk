#pragma once
#include "../win/win.h"
#include "base85.h"

namespace utils::encoding {
	static std::string utf8_to_ascii(std::wstring_view utf8) {
		std::string ascii(WideCharToMultiByte(CP_UTF8, 0, utf8.data(), utf8.size(), 0, 0, 0, 0), '\0');
		WideCharToMultiByte(CP_UTF8, 0, utf8.data(), utf8.size(), ascii.data(), ascii.length(), 0, 0);
		return ascii;
	}

	static std::wstring ascii_to_utf8(std::string_view ascii) {
		std::wstring utf8(MultiByteToWideChar(CP_ACP, 0, ascii.data(), ascii.length(), 0, 0), L'\0');
		MultiByteToWideChar(CP_ACP, 0, ascii.data(), ascii.length(), utf8.data(), utf8.length());
		return utf8;
	}

	static std::wstring utf8_to_utf16(std::string_view utf8) {
		std::wstring utf16(MultiByteToWideChar(CP_UTF8, 0, utf8.data(), utf8.length(), 0, 0), L'\0');
		MultiByteToWideChar(CP_UTF8, 0, utf8.data(), utf8.length(), utf16.data(), utf16.length());
		return utf16;
	}
}