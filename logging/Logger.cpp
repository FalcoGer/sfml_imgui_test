//
// Created by paul on 20.06.22.
//

# include "Logger.hpp"

namespace Logger
{
  Logger::Logger(std::string_view name)
    : m_name{name}
  {
    
  }
  
  std::string Logger::format(std::string_view message, const bool& includeTrace, const Logger::sl& loc)
  {
    if (!includeTrace)
    {
      return fmt::format("{0}", message);
    }
    else
    {
      if (!message.empty())
      {
        return fmt::format(
          "\"{4}\" from {0}() @ {1}[{2}:{3}]", loc.function_name(), loc.file_name(), loc.line(),
          loc.column(), message
        );
      }
      else
      {
        return fmt::format(
          "{0}() @ {1}[{2}:{3}]", loc.function_name(), loc.file_name(), loc.line(), loc.column(),
          message
        );
      }
    }
  }
}