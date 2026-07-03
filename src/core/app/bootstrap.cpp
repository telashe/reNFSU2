#include "core/app/bootstrap.hpp"
#include "core/hook/macros.hpp"

// @original: 0x0043e5b0
NFSU2_HOOK_CDECL(SetupEarlyBootstrap, 0x0043e5b0, void, int argc, char **argv) {
    return g_hook_SetupEarlyBootstrap.CallOriginal(argc, argv);
}

void nfsu2::app::SetupEarlyBootstrap(int argc, char **argv) {
    return Detour_SetupEarlyBootstrap(argc, argv);
}
