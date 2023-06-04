module;
#include <minhook/include/MinHook.h>
export module null.sdk:memory.minhook_wrapper;

import :memory.address;

export namespace memory {
	namespace minhook {
		MH_STATUS initialize() { return MH_Initialize(); }
		MH_STATUS destroy() { return MH_Uninitialize(); }
	}

	//@note: i'm too lazy to do it somehow beautifully, through explicit template specializations or something else, at least for now, so let it be so
	template <typename hook_class_t, typename prototype_t>
	struct hook_t {
	protected:
		static inline address_t hooked_address{ };
		static inline prototype_t original{ };

	public:
		static MH_STATUS setup(const address_t& address) {
			hooked_address = address;
			if(MH_STATUS status{ MH_CreateHook(address, &hook_class_t::hook, (LPVOID*)&original) }; status != MH_OK) return status;
			return enable();
		}

		static MH_STATUS enable() { return MH_EnableHook(hooked_address); }
		static MH_STATUS disable() { return MH_DisableHook(hooked_address); }
	};

	//@note: anyway, we will call original via asm, so its type is not important
	template <typename hook_class_t>
	struct proxy_hook_t {
	protected:
		static inline address_t hooked_address{ }, original{ };

	public:
		static MH_STATUS setup(const address_t& address) {
			hooked_address = address;
			if(MH_STATUS status{ MH_CreateHook(address, &hook_class_t::hook_proxy, (LPVOID*)&original) }; status != MH_OK) return status;
			return enable();
		}

		static MH_STATUS enable() { return MH_EnableHook(hooked_address); }
		static MH_STATUS disable() { return MH_DisableHook(hooked_address); }
	};
}