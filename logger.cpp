#include "logger.h"

Logger* Logger::m_instance = nullptr;
QString Logger::ERROR = "LOGGER ERROR";

/**
 * @brief Logger::Logger
 * @param parent
 */
Logger::Logger(QObject *parent) : QObject(parent)
{

}
