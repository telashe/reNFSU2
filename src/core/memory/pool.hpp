#pragma once

#include <cstdint>
#include <windows.h>

namespace nfsu2::memory {
struct sMemoryNode {
    sMemoryNode *pNext;
    sMemoryNode *pPrev;
};

#pragma pack(push, 4)
class cMemoryPool {
  public:
    const char *m_pPoolName;
    sMemoryNode m_FreeList;
    sMemoryNode m_AllocatedList;
    sMemoryNode m_LargeBlockList;
    int32_t m_AllocatedBytes;
    int32_t m_PeakBytes;
    int32_t m_TotalSize;
    int32_t m_NumAllocations;
    int32_t m_NumFrees;
    int32_t m_UnknownStat3;
    int32_t m_UnknownStat4;

    bool m_IsActive;
    bool m_IsInitialized;
    uint8_t m_Pad[2];

    CRITICAL_SECTION m_Lock;

    void __thiscall Constructor(void *startAddr, int size, const char *name);
};
#pragma pack(pop)

void InitializeMainPool();
} // namespace nfsu2::memory
