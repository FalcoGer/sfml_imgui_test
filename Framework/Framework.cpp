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
    this->app->setWindow(window);
    // set up fps counter
    std::string fontPath = "resources/fonts/MesloLGS NF Regular.ttf";
    if (!font.loadFromFile(fontPath))
    {
      std::string err = fmt::format("Couldn't not load Font: {}", fontPath);
      logger->log(err, Logger::Logger::LogLevel::critical);
      throw err;
    }
    logger->log("Font loaded");
    
    fpsCounter = sf::Text("", font);
    fpsCounter.setFillColor(sf::Color::Red);
    fpsCounter.setCharacterSize(12);
    
    window->setFramerateLimit(TARGET_FRAMERATE);
    
    // setup ImGui
    if (!ImGui::SFML::Init(*window))
    {
      std::string err = "Couldn't initialize ImGui";
      logger->log(err, Logger::Logger::LogLevel::critical);
      throw err;
    }
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Viewports
  
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();
    
    // initial draw before run() is running
    window->clear(DEFAULT_COLOR);
    window->display();
  }
  
  Framework::~Framework()
  {
    ImGui::SFML::Shutdown(*window);
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
      ImGui::SFML::ProcessEvent(ev);
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
      app->handleEvent(ev);
    }
    return count;
  }
  
  void Framework::update(const sf::Time& elapsed)
  {
    fpsCounter.setString(fmt::format("{0:>.5} FPS", 1.0f / elapsed.asSeconds()));
    
    ImGui::SFML::Update(*window, elapsed);
    // TODO: Re-Enable dockspace when figured out how to render into viewPort
    // ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    // this needs to be beneath the dockbar for it to be dockable
    app->update(elapsed);
    
    // ImGui::Begin("Main");
    // viewPort = ImGui::GetWindowViewport();
    // ImGui::End();
  }
  
  void Framework::draw()
  {
    window->clear(DEFAULT_COLOR);
    // draw the application
    // TODO: Draw application into viewPort somehow?
    window->draw(*app);
    // draw the FPS counter
    window->draw(fpsCounter);
    ImGui::SFML::Render(*window);
    window->display();
  }
} // Application