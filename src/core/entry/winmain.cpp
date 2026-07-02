#include "core/hook/macro.hpp"
#include "core/hook/offsets.h"
#include <windows.h>

// @original: 0x00580e00
NFSU2_HOOK_STDCALL(WinMain, Offsets::WinMain, int, int hInstance,
                   int hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    MessageBoxA(nullptr, "reNFSU2 hook is active.", "Debug",
                MB_OK | MB_ICONINFORMATION);

    return g_hook_WinMain.CallOriginal(hInstance, hPrevInstance, lpCmdLine,
                                       nCmdShow);
}
