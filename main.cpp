#include <iostream>

#include "MyApplication.hpp"
#include "logging/ConsoleLogger.hpp"

int main() {
  // init graphics library
  const unsigned int W = 800, H = 600;
  const std::string TITLE = "SFML_IMGUI_TEST";
  
  Application::Framework framework(W, H, TITLE, new Application::MyApplication());
  framework.run();
  
  return 0;
}
