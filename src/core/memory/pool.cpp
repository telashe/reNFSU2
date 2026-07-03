#include "pool.hpp"
#include "core/hook/macros.hpp"
#include "core/utils/logger.hpp"
#include "refs.hpp"

void __thiscall nfsu2::memory::cMemoryPool::Constructor(void *startAddr,
                                                        int size,
                                                        const char *name) {
    auto *pFunc = (void(__thiscall *)(cMemoryPool *, void *, int,
                                      const char *))0x004402c0;
    pFunc(this, startAddr, size, name);
}

// @original: 0x00440360
void nfsu2::memory::InitializeMainPool() {
    if (!refs::IsMainPoolInitialized()) {
        LOG_INFO("Initializing main memory pool...");

        refs::CurrentMemoryPool() = refs::MainMemoryPoolObj();

        refs::MainMemoryPoolObj()->Constructor(nullptr, 0, "Main Pool");

        refs::IsMainPoolInitialized() = true;
        LOG_INFO("Main memory pool initialized successfully.");
    }
}

NFSU2_HOOK_CDECL(InitializeMainPool, 0x00440360, void) {
    nfsu2::memory::InitializeMainPool();
}
