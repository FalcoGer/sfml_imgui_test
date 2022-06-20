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
        const std::string name;

    protected:
        typedef std::experimental::source_location sl;
        
        [[nodiscard]]
        static const std::string format(const std::string& message, const bool& includeTrace, const sl& loc);
    public:
        typedef spdlog::level::level_enum LogLevel;
        
        explicit Logger(const std::string& name);
        
        virtual ~Logger() = default;;

        virtual void log(const std::string& message, const LogLevel& level = LogLevel::info, const bool& includeTrace = false, const sl& loc = sl::current()) = 0;
        virtual void setLevel(const LogLevel&) = 0;
    
        [[nodiscard]]
        const std::string getName() const {
          return this->name;
        }
    };
}

