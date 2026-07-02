#include "core/hook/hook.hpp"
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        nfsu2::hook::HookManager::Instance().InstallAll();
    }

    return TRUE;
}
