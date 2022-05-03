import std.core;
import null.sdk;

enum class _enum {
    first,
    second
};

template<> struct utils::enum_reflection::range<_enum> {
    static constexpr int min = 0, max = 1;
};

int main() {
    std::cout << utils::enum_reflection::name(_enum::first) << std::endl;
    std::cout << utils::enum_reflection::name<_enum::second>() << std::endl;

    for(std::string_view str : utils::enum_reflection::names<_enum>())
        std::cout << str << std::endl;

    std::cout << utils::enum_reflection::count<_enum>();
}