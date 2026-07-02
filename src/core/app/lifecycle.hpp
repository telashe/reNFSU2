#pragma once

#include <windows.h>

namespace nfsu2::app {
void Initialize(HINSTANCE hInstance, HINSTANCE hPrevInstance);
void Shutdown(void);
void RunMainLoop(void);
} // namespace nfsu2::app
