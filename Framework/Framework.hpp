#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "../logging/Logger.hpp"

namespace Application
{
  class Application;
  
  class Framework
  {
    public:
      Framework(Application* const application);
      ~Framework();
      
      int run();
      
      std::shared_ptr<Logger::Logger> getLogger() const
      {
        return this->logger;
      }
    
      inline void setApplication(std::unique_ptr<Application> application)
      {
        this->app = std::move(application);
      }
      
      [[ nodiscard ]]
      inline std::shared_ptr<sf::RenderWindow> getWindow() const
      {
        return window;
      }
  
    protected:
      std::unique_ptr<Application> app;
      
      std::shared_ptr<sf::RenderWindow> window;
      std::shared_ptr<Logger::Logger> logger;
    
      const unsigned int TARGET_FRAMERATE;
      const sf::Color DEFAULT_COLOR;
      
      unsigned int handleEvents();
      void update(const sf::Time& elapsed);
      void draw();
  
    private:
      sf::Clock clk;
      sf::Text fpsCounter;
      sf::Font font;
    
      ImGuiViewport* viewPort;
  };
  
} // Application

