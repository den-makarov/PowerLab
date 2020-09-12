#include "logger.h"

Logger* Logger::m_instance = nullptr;
QString Logger::ERROR = "LOGGER ERROR";

Logger::Logger(QObject *parent) : QObject(parent)
{

}
