#include "core/hook/macros.hpp"
#include "core/hook/offsets.h"
#include <windows.h>

// @original: 0x00580e00
NFSU2_HOOK_STDCALL(WinMain, Offsets::WinMain, int, int hInstance,
                   int hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    return g_hook_WinMain.CallOriginal(hInstance, hPrevInstance, lpCmdLine,
                                       nCmdShow);
}
