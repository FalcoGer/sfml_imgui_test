#include <stdexcept>

#include "MyApplication.hpp"
#include "logging/ConsoleLogger.hpp"

int main() {
  const unsigned int W = 800, H = 600;
  const std::string TITLE = "SFML_IMGUI_TEST";
  
  try
  {
    Application::Framework framework(W, H, TITLE, std::make_unique<Application::MyApplication>());
    framework.run();
  }
  catch (std::string& err)
  {
    Logger::ConsoleLogger("Exception").log(fmt::format("Unhandled Exception: {}", err), Logger::Logger::LogLevel::critical);
    return 1;
  }
  catch (std::exception& err)
  {
    Logger::ConsoleLogger("Exception").log(fmt::format("Unhandled Exception: {}", err.what()), Logger::Logger::LogLevel::critical);
    return 1;
  }
  
  return 0;
}
