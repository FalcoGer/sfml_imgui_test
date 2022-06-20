#pragma once

#include "Framework/Framework.hpp"
#include "Framework/Application.hpp"

namespace Application
{
  
  class MyApplication : public Application
  {
    public:
      MyApplication() = delete;
      MyApplication(const unsigned int width, const unsigned int height, const std::string& title, std::shared_ptr<Logger::Logger> logger);
      ~MyApplication() = default;
    
      void handleEvent(const sf::Event& ev) override;
      void update(const sf::Time& elapsed) override;
  
    protected:
      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
      sf::RectangleShape bouncySquare;
      sf::Vector2f bouncySquareSpeed;
      float colorf[3] = {1.0f, 1.0f, 1.0f};
      
      bool demoWindowOpen;
  };
  
} // Application
