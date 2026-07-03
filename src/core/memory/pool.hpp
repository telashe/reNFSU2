#pragma once

#include <cstdint>
#include <windows.h>

namespace nfsu2::memory {
struct MemoryNode {
    MemoryNode *next;
    MemoryNode *prev;
};

#pragma pack(push, 4)
class MemoryPool {
  public:
    const char *m_poolName;
    MemoryNode m_freeList;
    MemoryNode m_allocatedList;
    MemoryNode m_largeBlockList;
    int32_t m_allocatedBytes;
    int32_t m_peakBytes;
    int32_t m_totalSize;
    int32_t m_numAllocations;
    int32_t m_numFrees;
    int32_t m_unknownStat3;
    int32_t m_unknownStat4;

    bool m_isActive;
    bool m_isInitialized;
    uint8_t m_pad[2];

    CRITICAL_SECTION m_lock;

    void __thiscall Constructor(void *startAddr, int size, const char *name);
};
#pragma pack(pop)

void InitializeMainPool();
} // namespace nfsu2::memory
