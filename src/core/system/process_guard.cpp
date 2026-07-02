#include "core/system/process_guard.hpp"
#include "core/hook/macros.hpp"
#include <handleapi.h>
#include <string.h>
#include <tlhelp32.h>
#include <windows.h>

NFSU2_HOOK_CDECL(CheckProcessCount, 0x005b7b20, bool, char *exeName,
                 int maxInstances) {
    return nfsu2::system::CheckProcessCount(exeName, maxInstances);
}

// @original: 0x005b7b20 @status: done
bool nfsu2::system::CheckProcessCount(char *exeName, int maxInstances) {
    PROCESSENTRY32 pe32;
    char fileName[MAX_PATH];
    int currentInstanceCount;

    memset(&pe32, 0, sizeof(PROCESSENTRY32));

    int retries = 3;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    while (true) {
        if (hSnapshot == INVALID_HANDLE_VALUE) {
            return false;
        }

        currentInstanceCount = 0;
        pe32.dwSize = sizeof(PROCESSENTRY32);

        BOOL bResult = Process32First(hSnapshot, &pe32);

        while (bResult) {
            char *slashPos = strrchr(pe32.szExeFile, '\\');

            if (slashPos == nullptr) {
                strcpy(fileName, pe32.szExeFile);
            } else {
                strcpy(fileName, slashPos + 1);
            }

            if (_stricmp(exeName, fileName) == 0) {
                currentInstanceCount++;
            }

            bResult = Process32Next(hSnapshot, &pe32);
        }

        CloseHandle(hSnapshot);
        retries--;

        if (currentInstanceCount <= maxInstances || retries < 0) {
            break;
        }

        Sleep(1000);
        hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    }

    return currentInstanceCount > maxInstances;
}
