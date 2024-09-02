namespace ntl {
    auto&& c_module::load_resources(this auto&& self) {
        static const auto to_string{
            [](const char* name) {
                return
                    (std::uint64_t)name & 0xFFFF0000
                    ? std::string(name) | std::views::transform([](char c) { return std::tolower(c); }) | std::ranges::to<std::string>()
                    : std::format("#{}", (std::uint16_t)name); //@note: https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-findresourcea#remarks
            }
        };

        static const auto enum_names{
            [](HMODULE module, LPCSTR type, LPSTR name, LONG_PTR param) -> BOOL {
                std::vector<resource_t>* resources = (std::vector<resource_t>*)param;
                resource_t new_resource(to_string(name), to_string(type), { module });

                //@note: of course, you can clean up self.resources, but because of this you will have to reload previously loaded resources
                //       to be honest, i do not know what is more expensive in performance, and i somehow do not want to do tests, so let it be so
                if(auto found = std::ranges::find_if(*resources, [&](const resource_t& resource) { return resource.name == new_resource.name && resource.type == new_resource.type; });
                    found == resources->end()) resources->push_back(new_resource);
                return true;
            }
        };

        static const auto enum_types{
            [](HMODULE module, LPSTR type, LONG_PTR param) -> BOOL {
                EnumResourceNamesA(module, type, (ENUMRESNAMEPROCA)enum_names, param);
                return true;
            }
        };

        EnumResourceTypesA(self.pe_image.base_address, (ENUMRESTYPEPROCA)enum_types, (LONG_PTR)&self.resources);
        return self;
    }
}