#include <iostream>

#include "MyApplication.hpp"
#include "logging/ConsoleLogger.hpp"

int main() {
  auto logger = std::shared_ptr<Logger::Logger>(new Logger::ConsoleLogger("stdout"));
  
  // init graphics library
  const unsigned int W = 800, H = 600;
  const std::string TITLE = "SFML_IMGUI_TEST";
  
  Application::Framework framework(new Application::MyApplication(W,H,TITLE,logger));
  framework.run();
  
  return 0;
}
