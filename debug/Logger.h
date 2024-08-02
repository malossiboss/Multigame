#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <memory>
#include <main_app/MainApp.h>

namespace Debug
{
class Logger
{
public:
    bool Init(const std::string& strTitle);
    std::shared_ptr<spdlog::logger>& GetLogger() { return m_ptrLogger; }
private:
    std::shared_ptr<spdlog::logger> m_ptrLogger;
};
}

/* Log macros */
#define LOG_TRACE(...)         MainApp::GetInstance().ptrLogger->GetLogger()->trace(__VA_ARGS__)
#define LOG_INFO(...)          MainApp::GetInstance().ptrLogger->GetLogger()->info(__VA_ARGS__)
#define LOG_WARN(...)          MainApp::GetInstance().ptrLogger->GetLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...)         MainApp::GetInstance().ptrLogger->GetLogger()->error(__VA_ARGS__)
#define LOG_CRITICAL(...)      MainApp::GetInstance().ptrLogger->GetLogger()->critical(__VA_ARGS__)
