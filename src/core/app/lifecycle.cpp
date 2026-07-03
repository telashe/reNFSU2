#include "core/app/lifecycle.hpp"
#include "core/hook/macros.hpp"
#include "core/utils/logger.hpp"

// @original: 0x0057ed10
NFSU2_HOOK_CDECL(Initialize, 0x0057ed10, void, int argc, char **argv) {
    LOG_INFO("Initializing application.");
    LOG_INFO("Command line arguments: %d", argc);

    for (int i = 0; i < argc; ++i) {
        LOG_INFO("argv[%d]: %s", i, argv[i]);
    }

    return g_hook_Initialize.CallOriginal(argc, argv);
}

void nfsu2::app::Initialize(int argc, char **argv) {
    return Detour_Initialize(argc, argv);
}

// @original: 0x005cf960
NFSU2_HOOK_CDECL(Shutdown, 0x005cf960, void) {
    LOG_INFO("Shutting down application.");

    g_hook_Shutdown.CallOriginal();

    LOG_INFO("Application shutdown complete. Goodbye!");
}

void nfsu2::app::Shutdown() { Detour_Shutdown(); }

// @original: 0x005811c0
NFSU2_HOOK_CDECL(RunMainLoop, 0x005811c0, void) {
    LOG_INFO("Entering main game loop...");

    g_hook_RunMainLoop.CallOriginal();

    LOG_INFO("Main game loop exited.");
}

void nfsu2::app::RunMainLoop() { Detour_RunMainLoop(); };
