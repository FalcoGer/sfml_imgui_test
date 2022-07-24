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
      sf::RectangleShape m_bouncySquare;
      sf::Vector2f m_bouncySquareSpeed;
      float m_colorf[3] = {1.0f, 1.0f, 1.0f};
    
      float m_huePerSecond;
      Color m_color;
      
      bool m_demoWindowOpen;
  };
  
} // Application
