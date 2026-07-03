#include "core/app/bootstrap.hpp"
#include "core/hook/macros.hpp"

NFSU2_HOOK_CDECL(SetupEarlyBootstrap, 0x0043e5b0, void, int argc, char **argv) {
    return g_hook_SetupEarlyBootstrap.CallOriginal(argc, argv);
}

// @original: 0x0043e5b0
void nfsu2::app::SetupEarlyBootstrap(int argc, char **argv) {
    return Detour_SetupEarlyBootstrap(argc, argv);
}

// @original: 0x00440360
NFSU2_HOOK_CDECL(FUN_00440360, 0x00440360, void, void) {
    return g_hook_FUN_00440360.CallOriginal();
}

// @original: 0x006fbe2c
NFSU2_HOOK_CDECL(FUN_006fbe2c, 0x006fbe2c, void, void) {
    return g_hook_FUN_006fbe2c.CallOriginal();
}

// @original: 0x006f57ea
NFSU2_HOOK_CDECL(FUN_006f57ea, 0x006f57ea, void, void) {
    return g_hook_FUN_006f57ea.CallOriginal();
}

// @original: 0x006f5c91
NFSU2_HOOK_CDECL(FUN_006f5c91, 0x006f5c91, void, int a1) {
    return g_hook_FUN_006f5c91.CallOriginal(a1);
}

// @original: 0x005b7a70
NFSU2_HOOK_CDECL(FUN_005b7a70, 0x005b7a70, void, void) {
    return g_hook_FUN_005b7a70.CallOriginal();
}

/*
Hooking this causes a crash. Probably we should pass some arguments
NFSU2_HOOK_CDECL(FUN_005c0d30, 0x005c0d30, int, void) {
    return g_hook_FUN_005c0d30.CallOriginal();
}
*/
