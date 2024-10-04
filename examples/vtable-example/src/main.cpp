#include <print>
#include <memory>

#include <null-sdk/memory/vtable.h>
#include <null-sdk/memory/minhook-wrapper.h>

class i_example_interface {
public:
    virtual void method1() = 0;
    virtual void method2() = 0;
};

class c_first_implementation : public i_example_interface {
public:
    void method1() override { std::print("first method1\n"); }
    void method2() override { std::print("first method2\n"); }
};

class c_second_implementation : public i_example_interface {
public:
    void method1() override { std::print("second method1\n"); }
    void method2() override { std::print("second method2\n"); }
};

struct example_hook_t : public ntl::minhook::hook_t<example_hook_t, void(*)(i_example_interface*)> {
public:
    static void hook(i_example_interface* self) {
        std::print("[hooked] ");
        original(self);
    }
};

struct example_vtable_hook_t : public ntl::minhook::vtable_hook_t<example_vtable_hook_t, 0, void(*)(i_example_interface*)> {
public:
    static void hook(i_example_interface* self) {
        std::print("[vtable hooked] ");
        original(self);
    }
};

void main() {
    ntl::minhook::initialize();

    std::array<std::unique_ptr<c_first_implementation>, 2> first_implementations{ };
    for(auto& ptr : first_implementations)
        ptr = std::make_unique<c_first_implementation>();

    std::unique_ptr<c_second_implementation> second_implementation = std::make_unique<c_second_implementation>();

    {
        std::print("call\n");
        std::print("first implementation[0]:  "); ntl::vtable_t::func_t<0, void()>::call(first_implementations[0].get());
        std::print("first implementation[1]:  "); ntl::vtable_t::func_t<0, void()>::call(first_implementations[1].get());
        std::print("second implementation:    "); ntl::vtable_t::func_t<0, void()>::call(second_implementation.get());
    }

    {
        std::print("\nhook for all vtable\n");
        example_hook_t::setup(ntl::vtable_t::get(first_implementations[0].get(), 0));

        std::print("first implementation[0]:  "); ntl::vtable_t::func_t<0, void()>::call(first_implementations[0].get());
        std::print("first implementation[1]:  "); ntl::vtable_t::func_t<0, void()>::call(first_implementations[1].get());
        std::print("second implementation:    "); ntl::vtable_t::func_t<0, void()>::call(second_implementation.get());

        example_hook_t::disable();
    }

    {
        std::print("\nhook for instance\n");
        example_vtable_hook_t::initialize(first_implementations[0].get(), 2);
        example_vtable_hook_t::setup(first_implementations[0].get());

        std::print("first implementation[0]:  "); ntl::vtable_t::func_t<0, void()>::call(first_implementations[0].get());
        std::print("first implementation[1]:  "); ntl::vtable_t::func_t<0, void()>::call(first_implementations[1].get());
        std::print("second implementation:    "); ntl::vtable_t::func_t<0, void()>::call(second_implementation.get());
    }

    ntl::minhook::destroy();
}
