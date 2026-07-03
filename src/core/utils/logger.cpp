#include "core/utils/logger.hpp"
#include <cstdarg>
#include <stdio.h>
#include <windows.h>

namespace nfsu2::log {
static FILE *s_LogFile = nullptr;

void Logger::Initialize(const char *logFileName, bool createConsole) {
    fopen_s(&s_LogFile, logFileName, "w");

    if (createConsole) {
        AllocConsole();
        FILE *dummy;
        freopen_s(&dummy, "CONOUT$", "w", stdout);
        freopen_s(&dummy, "CONOUT$", "w", stderr);
    }

    if (s_LogFile) {
        LOG_INFO("==========================");
        LOG_INFO("reNFSU2 Log System Booted!");
        LOG_INFO("==========================");
    }
}

void Logger::Shutdown() {
    if (s_LogFile) {
        LOG_INFO("Closing log system...");
        fclose(s_LogFile);
        s_LogFile = nullptr;
    }
}

void Logger::Print(const char *level, const char *format, ...) {
    if (!s_LogFile)
        return;

    SYSTEMTIME st;
    GetLocalTime(&st);

    fprintf(s_LogFile, "[%02d:%02d:%02d.%03d] [%s] ", st.wHour, st.wMinute,
            st.wSecond, st.wMilliseconds, level);

    printf("[%02d:%02d:%02d.%03d] [%s] ", st.wHour, st.wMinute, st.wSecond,
           st.wMilliseconds, level);

    va_list args;
    va_start(args, format);
    vfprintf(s_LogFile, format, args);
    vprintf(format, args);
    va_end(args);

    fprintf(s_LogFile, "\n");
    printf("\n");

    fflush(s_LogFile);
}
} // namespace nfsu2::log
