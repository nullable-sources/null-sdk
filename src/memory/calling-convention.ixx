module;

export module null.sdk:memory.calling_convention;

export namespace memory {
    struct stdcall_t { };
    struct cdecl_t { };
    struct fastcall_t { };

    template <typename convention_t, typename return_t, typename ...args_t>
    struct calling_convention_prototype_t { using prototype_t = return_t(args_t...); };

    template <typename return_t, typename ...args_t>
    struct calling_convention_prototype_t<stdcall_t, return_t, args_t...> { using prototype_t = return_t(__stdcall*)(args_t...); };

    template <typename return_t, typename ...args_t>
    struct calling_convention_prototype_t<cdecl_t, return_t, args_t...> { using prototype_t = return_t(__cdecl*)(args_t...); };

    template <typename return_t, typename ...args_t>
    struct calling_convention_prototype_t<fastcall_t, return_t, args_t...> { using prototype_t = return_t(__fastcall*)(args_t...); };
}