#include "core/app/lifecycle.hpp"
#include "core/hook/macros.hpp"

// @original: 0x0057ed10
NFSU2_HOOK_CDECL(Initialize, 0x0057ed10, void, int argc, char **argv) {
    return g_hook_Initialize.CallOriginal(argc, argv);
}

void nfsu2::app::Initialize(int argc, char **argv) {
    return Detour_Initialize(argc, argv);
}

// @original: 0x005cf960
NFSU2_HOOK_CDECL(Shutdown, 0x005cf960, void) {
    return g_hook_Shutdown.CallOriginal();
}

void nfsu2::app::Shutdown() { Detour_Shutdown(); }

// @original: 0x005811c0
NFSU2_HOOK_CDECL(RunMainLoop, 0x005811c0, void) {
    return g_hook_RunMainLoop.CallOriginal();
}

void nfsu2::app::RunMainLoop() { Detour_RunMainLoop(); };
