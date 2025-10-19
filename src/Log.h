#pragma once

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE

#include <QQuickItem>
#include <memory>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Hermes {
class Log {
  public:
    static void Init();

    static std::shared_ptr<spdlog::logger> &GetLogger() { return s_Logger; }
    static std::shared_ptr<spdlog::logger> &GetQMLLogger() {
        return s_QMLLogger;
    }

  private:
    static std::shared_ptr<spdlog::logger> s_Logger;
    static std::shared_ptr<spdlog::logger> s_QMLLogger;
};

class QmlLogger : public QQuickItem {
    Q_OBJECT
  public:
    explicit QmlLogger(QQuickItem *iParent = 0);

    // Q_INVOKABLE log method will be called by Qml source.
    Q_INVOKABLE void Trace(const QString &iDataToLog) const;
    Q_INVOKABLE void Info(const QString &iDataToLog) const;
    Q_INVOKABLE void Warn(const QString &iDataToLog) const;
    Q_INVOKABLE void Error(const QString &iDataToLog) const;
    Q_INVOKABLE void Critical(const QString &iDataToLog) const;
};
} // namespace Hermes

#define TRACE(...) SPDLOG_LOGGER_TRACE(::Hermes::Log::GetLogger(), __VA_ARGS__)
#define INFO(...) SPDLOG_LOGGER_INFO(::Hermes::Log::GetLogger(), __VA_ARGS__)
#define WARN(...) SPDLOG_LOGGER_WARN(::Hermes::Log::GetLogger(), __VA_ARGS__)
#define ERROR(...) SPDLOG_LOGGER_ERROR(::Hermes::Log::GetLogger(), __VA_ARGS__)
#define CRITICAL(...)                                                          \
    SPDLOG_LOGGER_CRITICAL(::Hermes::Log::GetLogger(), __VA_ARGS__)
