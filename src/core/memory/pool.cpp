#include "pool.hpp"
#include "core/hook/macros.hpp"
#include "core/utils/logger.hpp"

namespace nfsu2::memory {
bool &g_IsMainPoolInitialized = *(bool *)0x00828510;
MemoryPool *&g_pCurrentMemoryPool = *(MemoryPool **)0x00828154;
MemoryPool *g_MainMemoryPoolObj = (MemoryPool *)0x00828218;
} // namespace nfsu2::memory

void __thiscall nfsu2::memory::MemoryPool::Constructor(void *startAddr,
                                                       int size,
                                                       const char *name) {
    auto *pFunc =
        (void(__thiscall *)(MemoryPool *, void *, int, const char *))0x004402c0;
    pFunc(this, startAddr, size, name);
}

// @original: 0x00440360
void nfsu2::memory::InitializeMainPool() {
    if (!g_IsMainPoolInitialized) {
        LOG_INFO("Initializing main memory pool...");

        g_pCurrentMemoryPool = g_MainMemoryPoolObj;

        g_MainMemoryPoolObj->Constructor(nullptr, 0, "Main Pool");

        g_IsMainPoolInitialized = true;
        LOG_INFO("Main memory pool initialized successfully.");
    }
}

NFSU2_HOOK_CDECL(InitializeMainPool, 0x00440360, void) {
    nfsu2::memory::InitializeMainPool();
}
