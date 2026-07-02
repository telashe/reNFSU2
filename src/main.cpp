#include <libloaderapi.h>
#include <windows.h>
#include <MinHook.h>

DWORD WINAPI InitThread(LPVOID)
{
    MessageBoxA(nullptr, "RENFSU2.DLL Loaded!!!", "Test", MB_OK);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hModule);
        MH_Initialize();
        CreateThread(nullptr, 0, InitThread, nullptr, 0, nullptr);
    }

    return TRUE;
}
