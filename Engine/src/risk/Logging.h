#pragma once

#ifdef _DEBUG

#define LOG(message) risk::RiskLogger::GetLog()->Debug(message)
#define WARN(message) risk::RiskLogger::GetLog()->Warning(message)
#define ERROR(message) risk::RiskLogger::GetLog()->Error(message)

#include "RiskLogger.h"

#else
#define LOG(message)
#define WARN(message)
#define ERROR(message)
#endif
