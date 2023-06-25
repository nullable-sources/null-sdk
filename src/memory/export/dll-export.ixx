module;
#include <string_view>
#include <memory>
export module null.sdk:memory.dll_export;

import :memory.address;
import :memory.calling_convention;
import :utils.logger;

export namespace memory {
    class i_export : public address_t { };

    template <typename, typename = void>
    class c_export;

    template <typename return_t, typename ...args_t>
    class c_export<return_t(args_t...)> : public i_export {
    public:
        using prototype_t = calling_convention_prototype_t<stdcall_t, return_t, args_t...>::prototype_t;

    public:
        return_t call(args_t... args) const {
            if (!address) {
                utils::logger(utils::e_log_type::error, "export address is empty.");
                return return_t{ };
            }
            return ((prototype_t)address)(args...);
        }
    };
}