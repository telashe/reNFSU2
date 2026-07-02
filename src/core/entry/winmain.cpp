#include "core/hook/macros.hpp"
#include <windows.h>

// @original: 0x00580e00
NFSU2_HOOK_STDCALL(WinMain, 0x00580e00, int, int hInstance, int hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
    return g_hook_WinMain.CallOriginal(hInstance, hPrevInstance, lpCmdLine,
                                       nCmdShow);
}
