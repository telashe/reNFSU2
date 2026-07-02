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
NFSU2_HOOK_CDECL(Shutdown, 0x005cf960, void, void) {
    return g_hook_Shutdown.CallOriginal();
}

void nfsu2::app::Shutdown() { Detour_Shutdown(); }
