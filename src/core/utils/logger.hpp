#pragma once

namespace nfsu2::log {
class Logger {
  public:
    static void Initialize(const char *logFileName, bool createConsole = false);

    static void Shutdown();

    static void Print(const char *level, const char *format, ...);
};
} // namespace nfsu2::log

#define LOG_INFO(...) nfsu2::log::Logger::Print("INFO", __VA_ARGS__)
#define LOG_WARN(...) nfsu2::log::Logger::Print("WARN", __VA_ARGS__)
#define LOG_ERROR(...) nfsu2::log::Logger::Print("ERR ", __VA_ARGS__)
