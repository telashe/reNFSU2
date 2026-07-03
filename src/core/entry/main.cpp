#include "core/hook/macros.hpp"
#include <stdio.h>
#include <windows.h>

// @original: 0x00580e00
NFSU2_HOOK_STDCALL(main, 0x00580e00, int, int argc, char **argv) {
    return g_hook_main.CallOriginal(argc, argv);
}
