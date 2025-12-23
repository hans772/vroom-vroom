#include "logger.hpp"
#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

Logger::Logger() : m_log_level(LogLevel::DEBUG) {
}

std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    time_t t = std::chrono::system_clock::to_time_t(now);

    std::tm loc_time;
    localtime_s(&loc_time, &t);

    std::ostringstream formatted_time;
    formatted_time << std::put_time(&loc_time, "%Y-%m-%d %H:%M:%S");
    return formatted_time.str();
}

std::string Logger::getLogLevel(LogLevel level) {
    switch (level) {
    case LogLevel::DEBUG: return "DEBUG";
    case LogLevel::INFO: return "INFO";
    case LogLevel::WARNING: return "WARNING";
    case LogLevel::ERR: return "ERROR";
    default: return "INVALID";
    }
}


void Logger::setMinLogLevel(LogLevel level) {
    m_log_level = level;
}

void Logger::logi(LogLevel lvl, const std::string& str) {
    if ((lvl < m_log_level)) return;

    std::lock_guard<std::mutex> lock(log_mutex);

    std::cout << '[' <<
        getTimestamp() << "] [" <<
        getLogLevel(lvl) << "] [" <<
        str << "]\n";


}