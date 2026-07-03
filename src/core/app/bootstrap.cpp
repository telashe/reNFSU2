#include "core/app/bootstrap.hpp"
#include "core/hook/macros.hpp"
#include "core/utils/logger.hpp"

// @original: 0x0043e5b0
NFSU2_HOOK_CDECL(SetupEarlyBootstrap, 0x0043e5b0, void, int argc, char **argv) {
    return g_hook_SetupEarlyBootstrap.CallOriginal(argc, argv);
}

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
