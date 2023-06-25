module;
#include <string_view>
export module null.sdk:memory.dll_export_view;

import :memory.dll_export;
import :memory.win_module.dll;

export namespace memory {
    template <typename, typename = void>
    struct export_view_t;

    template <typename return_t, typename ...args_t>
    struct export_view_t<return_t(args_t...)> {
    private:
        c_export<return_t(args_t...)>* _export{ };

    public:
        export_view_t(c_dll& dll, const std::string& name) : _export{ dll.get_export(name) } { }
        export_view_t(c_export<return_t(args_t...)>* __export) : _export{ __export } { }
        export_view_t(i_export* __export) : _export{ (c_export<return_t(args_t...)>*)__export } { }

    public:
        return_t operator()(args_t... args) const { return _export->call(args...); }
    };
}