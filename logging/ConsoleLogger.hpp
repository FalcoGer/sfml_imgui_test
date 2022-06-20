//
// Created by paul on 20.06.22.
//

#pragma once

#include "Logger.hpp"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Logger {
    class ConsoleLogger : public Logger {
    private:
        decltype(spdlog::stdout_color_mt("")) sink;
    protected:
    public:
        explicit ConsoleLogger(const std::string&);
        ~ConsoleLogger() override;

        void log(const std::string& message, const LogLevel& level = LogLevel::info, const bool& includeTrace = false, const sl& loc = sl::current()) override;

        inline void setLevel(const LogLevel &level) override
        {
            this->sink->set_level(level);
        }
    };

}