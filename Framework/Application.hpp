#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "imgui.h"

#include "../logging/Logger.hpp"
#include "Framework.hpp"


namespace Application
{
  class Application : public sf::Transformable, public sf::Drawable
  {
    public:
      Application() = delete;
      explicit Application(const sf::Vector2i size, const std::string& title, std::shared_ptr<Logger::Logger> logger)
      : size{size}, title{title}, logger{logger}
      {
      }
      
      virtual ~Application() = default;
      
      virtual void handleSFMLEvent(const sf::Event& ev) = 0;
      virtual unsigned int handleImGUIEvents() = 0;
      virtual void update(const sf::Time& elapsed) = 0;
      
      [[ nodiscard ]]
      inline sf::Vector2i getSize() const { return size; }
      inline void setSize(const sf::Vector2i& size) { this->size = size; }
      
      [[ nodiscard ]]
      inline std::string getTitle() const { return title; }
  
    protected:
      std::shared_ptr<Logger::Logger> logger;
      std::string title;
      sf::Vector2i size;
  };
}



