//
// Created by paul on 20.06.22.
//

#include "ConsoleLogger.hpp"

#include <fmt/format.h>

namespace Logger {
    
    void ConsoleLogger::log(std::string_view message, const LogLevel& level, const bool& includeTrace,
                            const sl& loc) {
      this->sink->log(level, Logger::format(message, includeTrace, loc));
    }
    
    ConsoleLogger::ConsoleLogger(const std::string &name)
        : Logger(name), sink{ std::move(spdlog::stdout_color_mt(name)) } {
      this->sink->set_level(LogLevel::info);
    }
    
    ConsoleLogger::~ConsoleLogger() = default;
}