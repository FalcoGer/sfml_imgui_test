//
// Created by paul on 20.06.22.
//

#include "Framework.hpp"
#include "Application.hpp"

#include "../logging/ConsoleLogger.hpp"

namespace Application
{
  Framework::Framework(Application* const application)
  : TARGET_FRAMERATE{60},
    DEFAULT_COLOR{sf::Color(0x10, 0x10, 0x30, 0xFF)},
    logger{new Logger::ConsoleLogger(application->getTitle())},
    window{new sf::RenderWindow(sf::VideoMode(application->getSize().x, application->getSize().y), application->getTitle(), sf::Style::Default)}
  {
    this->app = std::unique_ptr<Application>(application);
    // set up fps counter
    std::string fontPath = "/usr/local/share/fonts/truetype/meslolgs-nf/MesloLGS NF Regular.ttf";
    if (!font.loadFromFile(fontPath))
    {
      logger->log(fmt::format("Cound not load Font: {}", fontPath), Logger::Logger::LogLevel::critical);
      throw "Coudn't load font";
    }
    logger->log("Font loaded");
    
    fpsCounter = sf::Text("", font);
    fpsCounter.setFillColor(sf::Color::Red);
    fpsCounter.setCharacterSize(12);
    
    window->setFramerateLimit(TARGET_FRAMERATE);
    
    // initial draw before run() is ran
    window->clear(DEFAULT_COLOR);
    window->display();
  }
  
  int Framework::run()
  {
    clk.restart();
    while (this->window->isOpen())
    {
      handleEvents();
      update(clk.restart());
      draw();
    }
    return 0;
  }
  
  unsigned int Framework::handleEvents()
  {
    sf::Event ev{};
    unsigned int count = 0;
    while(window->pollEvent(ev))
    {
      count++;
      count += app->handleImGUIEvents();
      switch (ev.type)
      {
        case sf::Event::Closed:
        {
          window->close();
          break;
        }
        case sf::Event::Resized:
        {
          app->setSize(sf::Vector2i(ev.size.width, ev.size.height));
          // prevent distortion when the windows is resized
          window->setView(sf::View(sf::Rect<float>(0,0,ev.size.width, ev.size.height)));
        }
        default:
        {
          break;
        }
      }
      app->handleSFMLEvent(ev);
    }
    return count;
  }
  
  void Framework::update(const sf::Time& elapsed)
  {
    app->update(elapsed);
    fpsCounter.setString(fmt::format("{0:>.5} FPS", 1.0f / elapsed.asSeconds()));
  }
  
  void Framework::draw()
  {
    window->clear(DEFAULT_COLOR);
    // draw the application
    window->draw(*app);
    // draw the FPS counter
    window->draw(fpsCounter);
    
    window->display();
  }
} // Application