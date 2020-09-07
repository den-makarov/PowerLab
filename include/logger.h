#ifndef LOGGER_H
#define LOGGER_H

#include <string>

#include <QObject>
#include <QDebug>

class Logger : public QObject
{
  Q_OBJECT
public:

  enum class Level : int {
    DEBUG,
    INFO,
    WARNING,
    CRITICAL,
    FATAL
  };

  static Logger* instance(QObject *parent = nullptr) {
    if(!m_instance) {
      m_instance = new Logger(parent);
    }
    return m_instance;
  }

  Logger& debug(const QObject *obj = nullptr) {
    m_level = Level::DEBUG;
    setModuleName(obj);
    return *this;
  }

  Logger& info(const QObject *obj = nullptr) {
    m_level = Level::INFO;
    setModuleName(obj);
    return *this;
  }

  Logger& warning(const QObject *obj = nullptr) {
    m_level = Level::WARNING;
    setModuleName(obj);
    return *this;
  }

  Logger& critical(const QObject *obj = nullptr) {
    m_level = Level::CRITICAL;
    setModuleName(obj);
    return *this;
  }

  Logger& fatal(const QObject *obj = nullptr) {
    m_level = Level::FATAL;
    setModuleName(obj);
    return *this;
  }

  const char* module() const {
    return m_module.data();
  }

  Level level() const {
    return m_level;
  }

private:
  const std::string DEFAULT_MODULE_NAME = "UNDEFINED";

  std::string m_module = DEFAULT_MODULE_NAME;
  static Logger* m_instance;
  Level m_level = Level::DEBUG;

  explicit Logger(QObject *parent = nullptr);

  void setModuleName(const QObject *obj = nullptr) {
    if(obj) {
      m_module = obj->metaObject()->className();
    } else {
      m_module = DEFAULT_MODULE_NAME;
    }
  }

  template<class T> friend QDebug operator<<(Logger& log, T t);
  static QString ERROR;
};



template <class T>
QDebug operator<<(Logger& log, T t) {
  switch (log.level()) {
  case Logger::Level::DEBUG:
    return qDebug() << "[" << log.module() << "]" << "DEBUG" << t;
    break;
  case Logger::Level::INFO:
    return qInfo() << "[" << log.module() << "]" << "INFO" << t;
    break;
  case Logger::Level::WARNING:
    return qDebug() << "[" << log.module() << "]" << "WARNING" << t;
    break;
  case Logger::Level::CRITICAL:
    return qCritical() << "[" << log.module() << "]" << "CRITICAL" << t;
    break;
  case Logger::Level::FATAL:
    return qCritical() << "[" << log.module() << "]" << "FATAL" << t;
    break;
  }
  return QDebug(&Logger::ERROR);
}

#define E_DEBUG(x) Logger::instance()->debug(x)
#define E_INFO(x) Logger::instance()->info(x)
#define E_WARNING(x) Logger::instance()->warning(x)
#define E_CRITICAL(x) Logger::instance()->critical(x)
#define E_FATAL(x) Logger::instance()->fatal(x)

#endif // LOGGER_H
