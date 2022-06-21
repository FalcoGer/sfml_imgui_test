#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Framework.hpp"
#include "../logging/ConsoleLogger.hpp"


namespace Application
{
  class Application : public sf::Transformable, public sf::Drawable
  {
    public:
      Application()
      : target{std::make_shared<sf::RenderTexture>()}, logger{std::make_shared<Logger::ConsoleLogger>("Application")}
      {
      }
      
      virtual ~Application() = default;
      
      virtual void handleEvent(const sf::Event& ev) = 0;
      virtual void update(const sf::Time& elapsed) = 0;
      
      [[ nodiscard ]]
      inline sf::Vector2u getSize() const { return target->getSize(); }
      inline void setSize(const sf::Vector2u& size)
      {
        [[ unlikely ]]
        if (target->getSize().x != size.x || target->getSize().y != size.y)
        {
          // only create a new render texture if necessary
          target->create(size.x, size.y);
        }
      }
      
      inline void setTarget(std::shared_ptr<sf::RenderTexture> target)
      {
        this->target = std::move(target);
      }
      
      [[ nodiscard ]]
      inline std::shared_ptr<sf::RenderTexture> getTarget() const { return this->target; }
      
      [[ nodiscard ]]
      inline std::shared_ptr<Logger::Logger> getLogger() const { return this->logger; }
  
    protected:
      std::shared_ptr<sf::RenderTexture> target;
      std::shared_ptr<Logger::Logger> logger;
  };
}



