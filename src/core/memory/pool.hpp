#pragma once

#include <windows.h>

namespace nfsu2::memory {
class MemoryPool {
  public:
    const char *m_PoolName; // 0x00
    void *m_List1_Next;     // 0x04
    void *m_List1_Prev;
    void *m_List2_Next;
    void *m_List2_Prev;
    void *m_List3_Next;
    void *m_List3_Prev;
    int m_AllocatedBytes;
    int m_PeakBytes;
    int m_UnknownStat1;
    int m_UnknownStat2;
    int m_UnknownStat3;
    int m_UnknownStat4;
    bool m_IsActive;
    bool m_Flag2;
    char m_Pad[2];
    CRITICAL_SECTION m_Lock;

    void __thiscall Constructor(void *startAddr, int size, const char *name);
};

void InitializeMainPool();
} // namespace nfsu2::memory
