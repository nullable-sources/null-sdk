module;
#include <windows.h>
#include <vector>
#include <memory>
#include <string>
export module null.sdk:memory.win_module.dll;

import :utils.logger;
import :memory.win_module;
import :memory.address;
import :memory.pe_image;
import :memory.calling_convention;
import :memory.dll_export;

export namespace memory {
    class c_dll : public c_module {
    public: using c_module::c_module;
        std::unordered_map<std::string, std::unique_ptr<i_export>> stored_exports{ };

    private:
        virtual std::unique_ptr<i_export> instance_export(std::string_view export_name) {
            if(export_name.empty()) {
                utils::logger(utils::e_log_type::error, "export name is empty.");
                return nullptr;
            }

            const address_t address{ GetProcAddress(pe_image.base_address, export_name.data()) };
            if(!address) utils::logger(utils::e_log_type::warning, "cant get \"{}\" export address.", export_name);

            return std::make_unique<i_export>(address);
        }

    public:
        i_export* get_export(const std::string& export_name) {
	        if(auto finded{ stored_exports.find(export_name) }; finded != stored_exports.end()) {
                return finded->second.get();
	        }

            stored_exports[export_name] = instance_export(export_name);
            return stored_exports[export_name].get();
        }
    };
}