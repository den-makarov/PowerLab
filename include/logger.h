#ifndef LOGGER_H
#define LOGGER_H

#include <string>

#include <QObject>
#include <QDebug>

class Logger : public QObject
{
  Q_OBJECT
public:
  enum class Level {
    INFO,
    DEBUG,
    WARNING,
    CRITICAL,
    PANIC
  };

  static Logger* instance(QObject *parent = nullptr) {
    if(!m_instance) {
      m_instance = new Logger(parent);
    }
    return m_instance;
  }

  Logger& debug(const std::string& module) {
    m_level = Level::DEBUG;
    m_module = module;
    return *this;
  }

  const char* module() const {
    return m_module.data();
  }

  Level level() const {
    return m_level;
  }

private:

  std::string m_module = "UNDEFINED";
  static Logger* m_instance;
  Level m_level = Level::DEBUG;

  explicit Logger(QObject *parent = nullptr);
};

template <class T>
Logger& operator<<(Logger& log, T t) {
  switch (log.level()) {
  case Logger::Level::INFO:
    qInfo() << "[" << log.module() << "]" << "INFO" << t;
    break;
  case Logger::Level::DEBUG:
    qDebug() << "[" << log.module() << "]" << "DEBUG" << t;
    break;
  case Logger::Level::WARNING:
    qDebug() << "[" << log.module() << "]" << "WARNING" << t;
    break;
  case Logger::Level::CRITICAL:
    qCritical() << "[" << log.module() << "]" << "CRITICAL" << t;
    break;
  case Logger::Level::PANIC:
    qCritical() << "[" << log.module() << "]" << "PANIC" << t;
    break;
  }

  return log;
}

#endif // LOGGER_H
