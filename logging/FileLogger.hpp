//
// Created by paul on 20.06.22.
//

#pragma once

#include "Logger.hpp"
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Logger {
    class FileLogger : public Logger
    {
    private:
      const std::string filePath;
      decltype(spdlog::basic_logger_st<spdlog::async_factory>("", "")) sink;
    protected:
    public:
      FileLogger(const std::string& name, const std::string& filePath, const bool& truncate = false);
      
      void log(const std::string &message, const LogLevel& level = LogLevel::info, const bool& includeTrace = false, const sl& loc = sl::current()) override;
  
      inline void setLevel(const LogLevel &level) override
      {
        this->sink->set_level(level);
      }
    };
}
