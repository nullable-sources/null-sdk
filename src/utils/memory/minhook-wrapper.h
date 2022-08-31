#pragma once
#include <utils/memory/address.h>
#include <minhook/include/MinHook.h>

namespace memory::minhook {
	template <typename hook_class_t, typename prototype_t>
	struct hook_t {
	protected:
		static inline address_t hooked_address{ };
		static inline prototype_t original{ };

	public:
		static MH_STATUS setup(address_t address) {
			hooked_address = address;
			if(MH_STATUS status{ MH_CreateHook(address, &hook_class_t::hook, (void**)&original) }; status != MH_OK) return status;
			if(MH_STATUS status{ MH_EnableHook(address) }; status != MH_OK) return status;
			return MH_OK;
		}

		static MH_STATUS disable() {
			return MH_DisableHook(hooked_address);
		}
	};

	static MH_STATUS initialize() {
		return MH_Initialize();
	}

	static MH_STATUS destroy() {
		return MH_Uninitialize();
	}
}