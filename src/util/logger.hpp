#pragma once

#include <mutex>
#include <set>
#include <string>
#include <sstream>
#include "util/singleton.hpp"

enum class LogLevel { // in order
	DEBUG = 0,
	INFO = 1,
	WARNING = 2,
	ERR = 3
};

class Logger : public Singleton<Logger> {
	friend class Singleton<Logger>;

	std::mutex log_mutex;

	LogLevel m_log_level;

	Logger();

	std::string get_timestamp(); 
	std::string get_log_level(LogLevel level); 

public:

	void set_min_log_level(LogLevel level);

	void logi(LogLevel lvl, const std::string& str);

	template<typename... LogArgs>
	void log(LogLevel lvl, LogArgs&&... args) { 
		std::ostringstream merge;
		(merge << ... << args);  // fold expression (C++17)
		logi(lvl, merge.str());
	}
};