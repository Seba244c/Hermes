#include "Log.h"

namespace Hermes {
std::shared_ptr<spdlog::logger> Log::s_Logger;
void Log::Init() {
    auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    consoleSink->set_pattern("%^[%T] [thread %t] (%n%s:%#)%$ %v");
    consoleSink->set_color(spdlog::level::info, "\033[42m\033[30m");
    consoleSink->set_color(spdlog::level::warn, "\033[43m\033[30m");
    consoleSink->set_color(spdlog::level::err, "\033[41m\033[30m");
    consoleSink->set_color(spdlog::level::critical,
                           "\033[4m\033[1m\033[41m\033[33m");
    consoleSink->set_level(spdlog::level::trace);
    s_Logger = std::make_shared<spdlog::logger>("Hermes/", consoleSink);
    s_Logger->set_level(spdlog::level::trace);
    s_Logger->flush_on(spdlog::level::trace);

    INFO("Logging Init ;)");
}
} // namespace Hermes
