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
      Framework(const unsigned int W, const unsigned int H, const std::string& TITLE, std::unique_ptr<Application> application);
      ~Framework();
      
      int run();
    
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
    
      const unsigned int TARGET_FRAMERATE;
      const sf::Color DEFAULT_COLOR;
      
      unsigned int handleEvents();
      void update(const sf::Time& elapsed);
      void draw();
  
    private:
      sf::Clock clk;
  };
  
} // Application

