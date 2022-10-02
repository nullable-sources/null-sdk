#pragma once
#include <utils/memory/address.h>
#include <minhook/include/MinHook.h>

namespace memory {
	enum class e_hook_type {
		standard,
		proxy
	};

	template <typename hook_class_t, typename prototype_t, e_hook_type type = e_hook_type::standard>
	struct hook_t {
	protected:
		static inline address_t hooked_address{ };
		static inline prototype_t original{ };

	public:
		static MH_STATUS setup(address_t address) {
			hooked_address = address;
			if constexpr(type == e_hook_type::standard) {
				if(MH_STATUS status{ MH_CreateHook(address, &hook_class_t::hook, (LPVOID*)&original) }; status != MH_OK) return status;
			} else if constexpr(type == e_hook_type::proxy) {
				if(MH_STATUS status{ MH_CreateHook(address, &hook_class_t::proxy, (LPVOID*)&original) }; status != MH_OK) return status;
			}
			if(MH_STATUS status{ MH_EnableHook(address) }; status != MH_OK) return status;
			return MH_OK;
		}

		static MH_STATUS disable() { return MH_DisableHook(hooked_address); }
	};

	namespace minhook {
		static MH_STATUS initialize() { return MH_Initialize(); }
		static MH_STATUS destroy() { return MH_Uninitialize(); }
	}
}