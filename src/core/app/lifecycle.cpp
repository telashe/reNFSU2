#include "core/app/lifecycle.hpp"
#include "core/hook/macros.hpp"

// @original: 0x0057ed10
NFSU2_HOOK_CDECL(Initialize, 0x0057ed10, void, HINSTANCE hInstance,
                 HINSTANCE hPrevInstance) {
    return g_hook_Initialize.CallOriginal(hInstance, hPrevInstance);
}

void nfsu2::app::Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance) {
    return Detour_Initialize(hInstance, hPrevInstance);
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
