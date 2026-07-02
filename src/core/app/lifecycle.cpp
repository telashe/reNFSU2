#include "core/app/lifecycle.hpp"
#include "core/hook/macros.hpp"
#include "core/hook/offsets.h"

// @original: 0x0057ed10
NFSU2_HOOK_CDECL(Initialize, Offsets::Initialize, void, HINSTANCE hInstance,
                 HINSTANCE hPrevInstance) {
    return g_hook_Initialize.CallOriginal(hInstance, hPrevInstance);
}

void nfsu2::app::Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance) {
    return Detour_Initialize(hInstance, hPrevInstance);
}
