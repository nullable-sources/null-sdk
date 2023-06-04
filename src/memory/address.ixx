module;
#include <vector>
#include <ranges>
#include <algorithm>
export module null.sdk:memory.address;

export namespace memory {
    struct address_t {
    public:
        std::uintptr_t address{ };

    public:
        address_t() { }
        address_t(const auto& value) : address{ (std::uintptr_t)value } { }

    public:
        template <typename cast_t> cast_t cast() const { return (cast_t)address; }

        auto& deref(int steps = 1) { for(; steps >= 1; steps--) address = *cast<std::uintptr_t*>(); return *this; }
        auto derefed(int steps = 1) const { return address_t{ *this }.deref(steps); }

        auto& offset(const std::intptr_t& offset) { address += offset; return *this; }
        auto& offset(const std::vector<std::intptr_t>& offsets) { std::ranges::for_each(offsets, [&](const std::intptr_t& _offset) { address += _offset; }); return *this; }
        auto offseted(const std::intptr_t& offset) const { return address_t{ *this }.offset(offset); }
        auto offseted(const std::vector<std::intptr_t>& offsets) const { return address_t{ *this }.offset(offsets); }

        auto& jump(const std::intptr_t& offset) {
			address_t return_address{ offseted(offset) };
            address = return_address.offset({ return_address.derefed().cast<std::int32_t>(), sizeof(std::uint32_t) });
            return *this;
        }
        auto jumped(const std::intptr_t& offset) const { return address_t{ *this }.jump(offset); }

    public:
        template <typename cast_t> operator cast_t() const { return cast<cast_t>(); }
        operator bool() const { return address; }
    };

    struct vtable_t : private address_t {
    public:
        std::uintptr_t* get() { return *cast<std::uintptr_t**>(); }
        std::uintptr_t operator[](const int& idx) { return get()[idx]; }

        template <typename funtion_t>
        funtion_t function(const int& index) {
            return (funtion_t)(get()[index]);
        }
    };
}