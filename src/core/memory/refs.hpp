#pragma once
#include "pool.hpp"

namespace nfsu2::memory::refs {
inline bool &IsMainPoolInitialized() { return *(bool *)0x00828510; }

inline cMemoryPool *&CurrentMemoryPool() { return *(cMemoryPool **)0x00828154; }

inline cMemoryPool *MainMemoryPoolObj() { return (cMemoryPool *)0x00828218; }
} // namespace nfsu2::memory::refs
