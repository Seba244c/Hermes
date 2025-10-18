#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Hermes {
class Log {
  public:
    static void Init();

    static std::shared_ptr<spdlog::logger> &GetLogger() { return s_Logger; }

  private:
    static std::shared_ptr<spdlog::logger> s_Logger;
};
} // namespace Hermes

#define TRACE(...) SPDLOG_LOGGER_TRACE(::Hermes::Log::GetLogger(), __VA_ARGS__)
#define INFO(...) SPDLOG_LOGGER_INFO(::Hermes::Log::GetLogger(), __VA_ARGS__)
#define WARN(...) SPDLOG_LOGGER_WARN(::Hermes::Log::GetLogger(), __VA_ARGS__)
#define ERROR(...) SPDLOG_LOGGER_ERROR(::Hermes::Log::GetLogger(), __VA_ARGS__)
#define CRITICAL(...)                                                          \
    SPDLOG_LOGGER_CRITICAL(::Hermes::Log::GetLogger(), __VA_ARGS__)
