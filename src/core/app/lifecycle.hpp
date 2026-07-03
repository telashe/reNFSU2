#pragma once

#include <windows.h>

namespace nfsu2::app {
void Initialize(int argc, char **argv);
void Shutdown(void);
void RunMainLoop(void);
void SetupEarlyBootstrap(int argc, char **argv);
} // namespace nfsu2::app
