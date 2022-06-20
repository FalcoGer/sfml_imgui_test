#include <iostream>

#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_sdlrenderer.h"

#include "logging/ConsoleLogger.hpp"

int main() {
  auto logger = std::unique_ptr<Logger::Logger>(new Logger::ConsoleLogger("stdout"));
  
  // init SDL
  
  
  return 0;
}
