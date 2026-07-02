#pragma once
#include "hook.hpp"

#define NFSU2_HOOK_IMPL(conv, name, address, ret, ...)                         \
    static ret conv Detour_##name(__VA_ARGS__);                                \
    static ::nfsu2::hook::FunctionHook<ret(conv *)(__VA_ARGS__)>               \
        g_hook_##name(#name, address, &Detour_##name);                         \
    static ret conv Detour_##name(__VA_ARGS__)

#define NFSU2_HOOK(name, address, ret, ...)                                    \
    NFSU2_HOOK_IMPL(__thiscall, name, address, ret, __VA_ARGS__)

#define NFSU2_HOOK_STDCALL(name, address, ret, ...)                            \
    NFSU2_HOOK_IMPL(__stdcall, name, address, ret, __VA_ARGS__)

#define NFSU2_HOOK_CDECL(name, address, ret, ...)                              \
    NFSU2_HOOK_IMPL(__cdecl, name, address, ret, __VA_ARGS__)
