//
// Created by paul on 20.06.22.
//

#include "FileLogger.hpp"
#include <fstream>

namespace Logger
{
    void FileLogger::log(const std::string &message, const Logger::Logger::LogLevel &level,
                                 const bool& includeTrace, const Logger::Logger::sl &loc)
    {
      this->sink->log(level, Logger::format(message, includeTrace, loc));
    }
    
    FileLogger::FileLogger(const std::string& name, const std::string &filePath, const bool &truncate)
    : Logger(name), sink{spdlog::basic_logger_st(name, filePath, truncate)}
    {
      this->sink->set_level(LogLevel::info);
    }
}
