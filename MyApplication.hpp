#pragma once

#include "Framework/Framework.hpp"
#include "Framework/Application.hpp"
#include "Framework/Color.hpp"

namespace Application
{
  
  class MyApplication : public Application
  {
    public:
      MyApplication();
      ~MyApplication() = default;
    
      void handleEvent(const sf::Event& ev) override;
      void update(const sf::Time& elapsed) override;
  
    protected:
      void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
      sf::RectangleShape bouncySquare;
      sf::Vector2f bouncySquareSpeed;
      float colorf[3] = {1.0f, 1.0f, 1.0f};
      
      Color color;
      
      bool demoWindowOpen;
  };
  
} // Application
