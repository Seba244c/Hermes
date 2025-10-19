#include "Log.h"

namespace Hermes {
std::shared_ptr<spdlog::logger> Log::s_Logger;
std::shared_ptr<spdlog::logger> Log::s_QMLLogger;
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
    s_QMLLogger = std::make_shared<spdlog::logger>("QML/", consoleSink);
    s_QMLLogger->set_level(spdlog::level::trace);
    s_QMLLogger->flush_on(spdlog::level::trace);

    INFO("Logging Init ;)");
}

QmlLogger::QmlLogger(QQuickItem *iParent) : QQuickItem(iParent) {}

void QmlLogger::Trace(const QString &iDataToLog) const {
    Log::GetQMLLogger()->log(spdlog ::level ::trace, iDataToLog.toStdString());
}
void QmlLogger::Info(const QString &iDataToLog) const {
    Log::GetQMLLogger()->log(spdlog ::level ::info, iDataToLog.toStdString());
}
void QmlLogger::Warn(const QString &iDataToLog) const {
    Log::GetQMLLogger()->log(spdlog ::level ::warn, iDataToLog.toStdString());
}
void QmlLogger::Error(const QString &iDataToLog) const {
    Log::GetQMLLogger()->log(spdlog ::level ::err, iDataToLog.toStdString());
}
void QmlLogger::Critical(const QString &iDataToLog) const {
    Log::GetQMLLogger()->log(spdlog ::level ::critical,
                             iDataToLog.toStdString());
}
} // namespace Hermes
