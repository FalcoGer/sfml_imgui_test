#include "MyApplication.hpp"

namespace Application
{
  MyApplication::MyApplication()
    : Application(),
    bouncySquare{sf::RectangleShape(sf::Vector2f(32.0f, 32.0f))},
    bouncySquareSpeed{100.0f, 60.0f}
  {
    bouncySquare.setFillColor(sf::Color::White);
    bouncySquare.setOutlineColor(sf::Color::Black);
    bouncySquare.setOutlineThickness(4.0f);
    bouncySquare.setPosition(getSize().x/2.0f, getSize().y/2.0f);
  }
  
  void MyApplication::handleEvent(const sf::Event& ev)
  {
  }
  
  void MyApplication::update(const sf::Time& elapsed)
  {
    sf::Vector2f pos = bouncySquare.getPosition();
    sf::Vector2f squareSize = bouncySquare.getSize();
    // bounce it off the wall.
    if (
      (bouncySquareSpeed.x < 0.0f && pos.x < 0.0f) // left wall
      || (bouncySquareSpeed.x > 0.0f && (pos.x + squareSize.x ) > getSize().x) // right wall
      )
    {
      bouncySquareSpeed.x = -bouncySquareSpeed.x;
    }
    if (
      (bouncySquareSpeed.y < 0.0f && pos.y < 0.0f) // top wall
      || (bouncySquareSpeed.y > 0.0f && (pos.y + squareSize.y) > getSize().y) // bottom wall
      )
    {
      bouncySquareSpeed.y = -bouncySquareSpeed.y;
    }
  
    // make sure bouncy square stays within boundaries when resized.
    if (target->getSize().x < (pos.x + bouncySquare.getSize().x))
    {
      pos.x = target->getSize().x - bouncySquare.getSize().x;
    }
    if (target->getSize().y < (pos.y + bouncySquare.getSize().y))
    {
      pos.y = target->getSize().y - bouncySquare.getSize().y;
    }
    bouncySquare.setPosition(pos);
    
    // move the square by it's velocity
    bouncySquare.move(bouncySquareSpeed.x * elapsed.asSeconds(), bouncySquareSpeed.y * elapsed.asSeconds());
    // set new color
    bouncySquare.setFillColor(sf::Color(colorf[0]*0xFF, colorf[1]*0xFF, colorf[2]*0xFF));
    
    // ImGui stuff here
    ImGui::Begin("Window");
    ImGui::Checkbox("Demo Window", &demoWindowOpen);
    ImGui::SliderFloat("Speed X", &bouncySquareSpeed.x, -200.0f, +200.0f);
    ImGui::SliderFloat("Speed Y", &bouncySquareSpeed.y, -200.0f, +200.0f);
    ImGui::ColorEdit3("Color", colorf);
    ImGui::End();
    
    if (demoWindowOpen)
    {
      ImGui::ShowDemoWindow(&demoWindowOpen);
    }
  }
  
  void MyApplication::draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
  
    target.draw(bouncySquare, states);
  }
} // Application