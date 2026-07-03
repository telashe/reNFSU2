#include "core/hook/hook.hpp"
#include "core/utils/logger.hpp"
#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);

        nfsu2::log::Logger::Initialize("RENFSU2.LOG", true);
        LOG_INFO("DLL injected succesfully");

        nfsu2::hook::HookManager::Instance().InstallAll();
    } else if (reason == DLL_PROCESS_DETACH) {
        nfsu2::log::Logger::Shutdown();
    }

    return TRUE;
}
