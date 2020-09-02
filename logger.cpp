#include "logger.h"

Logger* Logger::m_instance = nullptr;

Logger::Logger(QObject *parent) : QObject(parent)
{

}
