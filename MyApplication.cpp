#include "MyApplication.hpp"

namespace Application
{
  MyApplication::MyApplication()
    : Application(),
    m_bouncySquare{sf::RectangleShape(sf::Vector2f(32.0f, 32.0f))},
    m_bouncySquareSpeed{100.0f, 60.0f},
    m_huePerSecond{60.0f},
    m_demoWindowOpen{false}
  {
    sf::Color fillColor = sf::Color(0xB0, 0xFF, 0x20);
    m_bouncySquare.setFillColor(fillColor);
    m_bouncySquare.setOutlineColor(sf::Color::Black);
    m_bouncySquare.setOutlineThickness(4.0f);
    m_bouncySquare.setPosition(static_cast<float>(getSize().x) / 2.0f, static_cast<float>(getSize().y) / 2.0f);
  
    m_colorf[0] = static_cast<float>(fillColor.r) / 0xff;
    m_colorf[1] = static_cast<float>(fillColor.g) / 0xff;
    m_colorf[2] = static_cast<float>(fillColor.b) / 0xff;
  }
  
  void MyApplication::handleEvent(const sf::Event& ev)
  {
  }
  
  void MyApplication::update(const sf::Time& elapsed)
  {
    sf::Vector2f pos = m_bouncySquare.getPosition();
    // bounce it off the wall.
    if (
      (m_bouncySquareSpeed.x < 0.0f && pos.x < 0.0f) // left wall
      || (m_bouncySquareSpeed.x > 0.0f && (pos.x + m_bouncySquare.getSize().x ) > static_cast<float>(getSize().x)) // right wall
      )
    {
      m_bouncySquareSpeed.x = -m_bouncySquareSpeed.x;
    }
    if (
      (m_bouncySquareSpeed.y < 0.0f && pos.y < 0.0f) // top wall
      || (m_bouncySquareSpeed.y > 0.0f && (pos.y + m_bouncySquare.getSize().y) > static_cast<float>(getSize().y)) // bottom wall
      )
    {
      m_bouncySquareSpeed.y = -m_bouncySquareSpeed.y;
    }
  
    // make sure bouncy square stays within boundaries when resized.
    if (static_cast<float>(getSize().x) < (pos.x + m_bouncySquare.getSize().x))
    {
      pos.x = static_cast<float>(getSize().x) - m_bouncySquare.getSize().x;
    }
    if (static_cast<float>(getSize().y) < (pos.y + m_bouncySquare.getSize().y))
    {
      pos.y = static_cast<float>(getSize().y) - m_bouncySquare.getSize().y;
    }
    m_bouncySquare.setPosition(pos);
    
    // move the square by its velocity
    m_bouncySquare.move(m_bouncySquareSpeed.x * elapsed.asSeconds(), m_bouncySquareSpeed.y * elapsed.asSeconds());
    pos = m_bouncySquare.getPosition();
    
    // ImGui stuff here
    ImGui::Begin("Settings");
    ImGui::Text("%s", fmt::format("{0:>.5} FPS", (1.0f / elapsed.asSeconds())).c_str());
    ImGui::Checkbox("Demo Window", &m_demoWindowOpen);
    ImGui::SliderFloat("Speed X", &m_bouncySquareSpeed.x, -200.0f, +200.0f);
    ImGui::SliderFloat("Speed Y", &m_bouncySquareSpeed.y, -200.0f, +200.0f);
    ImGui::SliderFloat("Position X", &pos.x, 0.0f, static_cast<float>(getSize().x) - m_bouncySquare.getSize().x);
    ImGui::SliderFloat("Position Y", &pos.y, 0.0f, static_cast<float>(getSize().y) - m_bouncySquare.getSize().y);
    ImGui::ColorEdit3("Color", m_colorf);
    ImGui::SliderFloat("Hue Change Speed (°/s)", &m_huePerSecond, -720.0f, +720.0f);
    ImGui::End();
    
    // set new position
    m_bouncySquare.setPosition(pos);
    
    // set new m_color
    // create m_color object to update hue
    m_color.SetRGB(m_colorf[0], m_colorf[1], m_colorf[2]);
    float h = m_color.GetH();
    h += m_huePerSecond * elapsed.asSeconds();
    [[ unlikely ]]
    while (h > 360.0f || h < 0.0f)
    {
      h += h > 360.0f ? -360.0f : 360.0f;
    }
    m_color.SetH(h);
    m_colorf[0] = m_color.GetR();
    m_colorf[1] = m_color.GetG();
    m_colorf[2] = m_color.GetB();
    m_bouncySquare.setFillColor(sf::Color(static_cast<unsigned char>(m_colorf[0] * 0xff),
                                          static_cast<unsigned char>(m_colorf[1] * 0xff),
                                          static_cast<unsigned char>(m_colorf[2] * 0xff)));
    
    if (m_demoWindowOpen)
    {
      ImGui::ShowDemoWindow(&m_demoWindowOpen);
    }
  }
  
  void MyApplication::draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    // apply the entity's transform -- combine it with the one that was passed by the caller
    states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
  
    target.draw(m_bouncySquare, states);
  }
} // Application