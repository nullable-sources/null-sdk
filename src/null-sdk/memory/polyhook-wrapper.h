#pragma once
#ifdef NULLSDK_POLYHOOK_EXIST
#include "address.h"

#include <polyhook2/IHook.hpp>
#include <polyhook2/Detour/ADetour.hpp>
#include <polyhook2/Detour/ILCallback.hpp>
#include <polyhook2/Detour/NatDetour.hpp>

namespace ntl::polyhook {
    template <typename hook_class_t, typename prototype_t>
    struct hook_t {
    protected:
        static inline std::unique_ptr<PLH::NatDetour> detour{ };
        static inline prototype_t original{ };
        static inline address_t hooked_address{ };

    public:
        static inline void reconfigure_detour() { }
        static bool setup(const address_t& address) {
            hooked_address = address;
            detour = std::make_unique<PLH::NatDetour>(address.cast<std::uint64_t>(), (uint64_t)hook_class_t::hook, (uint64_t*)&original);
            hook_class_t::reconfigure_detour();
            return detour->hook();
        }

        static bool disable() { return detour->unHook(); }
    };

    template <typename hook_class_t, typename prototype_t>
    struct proxy_hook_t {
    protected:
        static inline std::unique_ptr<PLH::NatDetour> detour{ };
        static inline prototype_t original{ };
        static inline address_t hooked_address{ };

    public:
        static inline void reconfigure_detour() { }
        static bool setup(address_t address) {
            hooked_address = address;
            detour = std::make_unique<PLH::NatDetour>(address.cast<std::uint64_t>(), (uint64_t)hook_class_t::hook_proxy, (uint64_t*)&original);
            hook_class_t::reconfigure_detour();
            return detour->hook();
        }

        static inline bool disable() { return detour->unHook(); }
    };
}
#endif