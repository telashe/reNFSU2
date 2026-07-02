#pragma once

namespace nfsu::time {
extern float &g_SecondsPerTick;
extern int &g_TimerShift;

void InitTimer(void);
} // namespace nfsu::time
