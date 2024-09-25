#pragma once
#include <minhook/include/MinHook.h>

#include "vtable.h"

namespace ntl {
    template <typename prototype_t>
    class i_hook {
    protected:
        static inline prototype_t original{ };
    };

    template <typename hook_class_t, typename prototype_t>
    struct hook_t : public i_hook<prototype_t> {
    protected:
        static inline address_t hooked_address{ };

    public:
        static MH_STATUS setup(const address_t& address) {
            hooked_address = address;
            if(MH_STATUS status = MH_CreateHook(address, &hook_class_t::hook, (LPVOID*)&i_hook<prototype_t>::original); status != MH_OK) return status;
            if(MH_STATUS status = MH_EnableHook(address); status != MH_OK) return status;
            return MH_OK;
        }

        static inline MH_STATUS disable() { return MH_DisableHook(hooked_address); }
    };

    template <typename hook_class_t, typename prototype_t>
    struct proxy_hook_t : public i_hook<prototype_t> {
    protected:
        static inline address_t hooked_address{ };

    public:
        static MH_STATUS setup(address_t address) {
            hooked_address = address;
            if(MH_STATUS status = MH_CreateHook(address, &hook_class_t::hook_proxy, (LPVOID*)&i_hook<prototype_t>::original); status != MH_OK) return status;
            if(MH_STATUS status = MH_EnableHook(address); status != MH_OK) return status;
            return MH_OK;
        }

        static inline MH_STATUS disable() { return MH_DisableHook(hooked_address); }
    };

    template <typename hook_class_t, std::size_t method_index, typename prototype_t>
    struct vtable_hook_t : public i_hook<prototype_t> {
    protected:
        static inline vtable_t::copied_t copied_vtable{ };

    public:
        static bool initialized() { return !copied_vtable.empty(); }
        static void initialize(address_t address, std::size_t methods_count) {
            i_hook<prototype_t>::original = vtable_t::get(address, method_index);
            copied_vtable = vtable_t::copy(address, methods_count);
            copied_vtable.replace(method_index, &hook_class_t::hook);
        }

        static void setup(address_t address) { copied_vtable.override(address); }
        static inline void disable(address_t address) { return copied_vtable.restore(address); }
    };

    namespace minhook {
        static inline MH_STATUS initialize() { return MH_Initialize(); }
        static inline MH_STATUS destroy() { return MH_Uninitialize(); }
    }
}