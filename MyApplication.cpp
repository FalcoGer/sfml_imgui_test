//
// Created by paul on 20.06.22.
//

#include "MyApplication.hpp"

namespace Application
{
  MyApplication::MyApplication(
    const unsigned int width,
    const unsigned int height,
    const std::string& title,
    std::shared_ptr<Logger::Logger> logger
  )
    : Application(sf::Vector2i(width, height), title, logger),
    bouncySquare{sf::RectangleShape(sf::Vector2f(32.0f, 32.0f))},
    bouncySquareSpeed{100.0f, 60.0f}
  {
    bouncySquare.setFillColor(sf::Color::White);
    bouncySquare.setOutlineColor(sf::Color::Black);
    bouncySquare.setOutlineThickness(4.0f);
    bouncySquare.setPosition(getSize().x/2.0f, getSize().y/2.0f);
  }
  
  void MyApplication::handleSFMLEvent(const sf::Event& ev)
  {
    if (ev.type == sf::Event::Resized)
    {
      // make sure bouncy square stays within boundaries when resized.
      sf::Vector2f pos = bouncySquare.getPosition();
      if (ev.size.width < (pos.x + bouncySquare.getSize().x))
      {
        pos.x = ev.size.width - bouncySquare.getSize().x;
      }
      if (ev.size.height < (pos.y + bouncySquare.getSize().y))
      {
        pos.y = ev.size.height - bouncySquare.getSize().y;
      }
      bouncySquare.setPosition(pos);
    }
  }
  
  unsigned int MyApplication::handleImGUIEvents()
  {
    return 0;
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
    
    // move the square by it's velocity
    bouncySquare.move(bouncySquareSpeed.x * elapsed.asSeconds(), bouncySquareSpeed.y * elapsed.asSeconds());
  }
  
  void MyApplication::draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
  
    target.draw(bouncySquare, states);
  }
} // Application