#include "Logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Debug
{

bool Logger::Init(const std::string& strTitle)
{
    spdlog::set_pattern("%^[%d.%m.%Y %T] %n: %v%$");
    m_ptrLogger = spdlog::stdout_color_mt(strTitle);
    m_ptrLogger->set_level(spdlog::level::trace);

    m_ptrLogger->enable_backtrace(50);
    return true;
}

}
