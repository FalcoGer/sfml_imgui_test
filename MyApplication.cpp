#include "MyApplication.hpp"

namespace Application
{
  MyApplication::MyApplication()
    : Application(),
    bouncySquare{sf::RectangleShape(sf::Vector2f(32.0f, 32.0f))},
    bouncySquareSpeed{100.0f, 60.0f}
  {
    sf::Color fillColor = sf::Color(0xB0, 0xFF, 0x20);
    bouncySquare.setFillColor(fillColor);
    bouncySquare.setOutlineColor(sf::Color::Black);
    bouncySquare.setOutlineThickness(4.0f);
    bouncySquare.setPosition(getSize().x/2.0f, getSize().y/2.0f);
    
    colorf[0] = static_cast<float>(fillColor.r) / 0xff;
    colorf[1] = static_cast<float>(fillColor.g) / 0xff;
    colorf[2] = static_cast<float>(fillColor.b) / 0xff;
  }
  
  void MyApplication::handleEvent(const sf::Event& ev)
  {
  }
  
  void MyApplication::update(const sf::Time& elapsed)
  {
    sf::Vector2f pos = bouncySquare.getPosition();
    // bounce it off the wall.
    if (
      (bouncySquareSpeed.x < 0.0f && pos.x < 0.0f) // left wall
      || (bouncySquareSpeed.x > 0.0f && (pos.x + bouncySquare.getSize().x ) > getSize().x) // right wall
      )
    {
      bouncySquareSpeed.x = -bouncySquareSpeed.x;
    }
    if (
      (bouncySquareSpeed.y < 0.0f && pos.y < 0.0f) // top wall
      || (bouncySquareSpeed.y > 0.0f && (pos.y + bouncySquare.getSize().y) > getSize().y) // bottom wall
      )
    {
      bouncySquareSpeed.y = -bouncySquareSpeed.y;
    }
  
    // make sure bouncy square stays within boundaries when resized.
    if (getSize().x < (pos.x + bouncySquare.getSize().x))
    {
      pos.x = getSize().x - bouncySquare.getSize().x;
    }
    if (getSize().y < (pos.y + bouncySquare.getSize().y))
    {
      pos.y = getSize().y - bouncySquare.getSize().y;
    }
    bouncySquare.setPosition(pos);
    
    // move the square by its velocity
    bouncySquare.move(bouncySquareSpeed.x * elapsed.asSeconds(), bouncySquareSpeed.y * elapsed.asSeconds());
    pos = bouncySquare.getPosition();
    
    // ImGui stuff here
    ImGui::Begin("Settings");
    ImGui::Text("%s", fmt::format("{0:>.5} FPS", (1.0f / elapsed.asSeconds())).c_str());
    ImGui::Checkbox("Demo Window", &demoWindowOpen);
    ImGui::SliderFloat("Speed X", &bouncySquareSpeed.x, -200.0f, +200.0f);
    ImGui::SliderFloat("Speed Y", &bouncySquareSpeed.y, -200.0f, +200.0f);
    ImGui::SliderFloat("Position X", &pos.x, 0.0f, getSize().x - bouncySquare.getSize().x);
    ImGui::SliderFloat("Position Y", &pos.y, 0.0f, getSize().y - bouncySquare.getSize().y);
    ImGui::ColorEdit3("Color", colorf);
    ImGui::End();
    
    // set new position
    bouncySquare.setPosition(pos);
    
    // set new color
    // create color object to update hue
    color.SetRGB(colorf[0], colorf[1], colorf[2]);
    const float huePerSecond = 60.0f;
    float h = color.GetH();
    h += huePerSecond * elapsed.asSeconds();
    [[ unlikely ]]
    while (h > 360.0f)
    {
      h -= 360.0f;
    }
    color.SetH(h);
    colorf[0] = color.GetR();
    colorf[1] = color.GetG();
    colorf[2] = color.GetB();
    bouncySquare.setFillColor(sf::Color(colorf[0]*0xff, colorf[1]*0xff, colorf[2]*0xff));
    
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