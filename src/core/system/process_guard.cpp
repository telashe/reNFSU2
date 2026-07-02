#include "core/system/process_guard.hpp"
#include "core/hook/macros.hpp"
#include "core/hook/offsets.h"

// @original: 0x005b7b20
NFSU2_HOOK_CDECL(CheckProcessCount, Offsets::CheckProcessCount, bool,
                 char *exeName, int maxInstances) {
    return g_hook_CheckProcessCount.CallOriginal(exeName, maxInstances);
}

bool nfsu2::system::CheckProcessCount(char *exeName, int maxInstances) {
    return Detour_CheckProcessCount(exeName, maxInstances);
}
