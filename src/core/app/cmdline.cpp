#include "core/app/cmdline.hpp"
#include "core/hook/macros.hpp"

// @original: 0x004fef60
NFSU2_HOOK_CDECL(BootToDebugMenu, 0x004fef60, void, void) {
    return g_hook_BootToDebugMenu.CallOriginal();
}

void nfsu2::app::BootToDebugMenu() { Detour_BootToDebugMenu(); }
