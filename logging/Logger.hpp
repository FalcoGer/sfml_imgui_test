//
// Created by paul on 20.06.22.
//

#pragma once

#include <spdlog/spdlog.h>
#include <string>
#include <experimental/source_location>

namespace Logger
{
    class Logger
    {
    private:
    protected:
        const std::string m_name;
        typedef std::experimental::source_location sl;
        
        [[nodiscard]]
        static std::string format(std::string_view message, const bool& includeTrace, const sl& loc);
    public:
        typedef spdlog::level::level_enum LogLevel;
        
        explicit Logger(std::string_view name);
        
        virtual ~Logger() = default;

        virtual void log(std::string_view message, const LogLevel& level = LogLevel::info, const bool& includeTrace = false, const sl& loc = sl::current()) = 0;
        virtual void setLevel(const LogLevel&) = 0;
    
        [[nodiscard]]
        std::string getName() const { return m_name; }
    };
}

