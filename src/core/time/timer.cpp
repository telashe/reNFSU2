#include "timer.hpp"
#include "core/hook/macros.hpp"
#include <windows.h>

namespace nfsu2::time {
float &g_SecondsPerTick = *(float *)0x00828028;
int &g_TimerShift = *(int *)0x008284e4;

// @original: 0x0043bd90 @status: done
void InitTimer() {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);

    g_TimerShift = 0;

    const float kTimerMultiplier = 1000.0f;
    const float kMax32BitTime = 2147483648.0f;
    const float kCalibrationLimit = 60000.0f;

    g_SecondsPerTick = kTimerMultiplier / (float)frequency.QuadPart;

    for (float f = g_SecondsPerTick * kMax32BitTime; f < kCalibrationLimit;
         f *= 2.0f) {
        g_TimerShift++;
    }
}
} // namespace nfsu2::time

NFSU2_HOOK_CDECL(InitTimer, 0x0043bd90, void, void) {
    nfsu2::time::InitTimer();
}
