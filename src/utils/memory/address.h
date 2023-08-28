#pragma once
#include "utils/win/win.h"

//@credits: thx lagcomp/csgo_sdk for this superior code
namespace memory {
	struct address_t {
	public:
		std::uintptr_t address{ };

	public:
		address_t() { }
		address_t(const auto& value) : address{ (std::uintptr_t)value } { }

	public:
		template <typename cast_t> cast_t cast() const { return (cast_t)address; }

		template <typename self_t> auto&& deref(this self_t&& self, int steps = 1) { for(; steps >= 1; steps--) self.address = *self.cast<std::uintptr_t*>(); return self; }

		template <typename self_t> auto&& offset(this self_t&& self, std::intptr_t offset) { self.address += offset; return self; }
		template <typename self_t> auto&& offset(this self_t&& self, const std::vector<std::intptr_t>& offsets) { std::ranges::for_each(offsets, [&](std::intptr_t _offset) { self.address += _offset; }); return self; }

		template <typename self_t> auto&& jump(this self_t&& self, std::intptr_t _offset) {
			address_t return_address{ address_t{ self }.offset(_offset) };
			self.address = return_address.offset({ address_t{ return_address }.deref().cast<std::int32_t>(), sizeof(std::uint32_t) });
			return self;
		}

	public:
		template <typename cast_t> operator cast_t() const { return cast<cast_t>(); }
		operator bool() const { return address; }
	};

	struct vtable_t : private address_t {
	public:
		std::uintptr_t* get() { return *cast<std::uintptr_t**>(); }
		std::uintptr_t operator[](int idx) { return get()[idx]; }

		template <typename funtion_t>
		funtion_t function(int index) {
			return (funtion_t)(get()[index]);
		}
	};
}