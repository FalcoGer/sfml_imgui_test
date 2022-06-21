//
// Created by paul on 20.06.22.
//

#include "Framework.hpp"
#include "Application.hpp"

#include "../logging/ConsoleLogger.hpp"

namespace Application
{
  Framework::Framework(const unsigned int W, const unsigned int H, const std::string& TITLE, Application* const application)
  : TARGET_FRAMERATE{60},
    DEFAULT_COLOR{sf::Color(0x10, 0x10, 0x30, 0xFF)},
    window{new sf::RenderWindow(sf::VideoMode(W, H), TITLE, sf::Style::Default)}
  {
    this->app = std::unique_ptr<Application>(application);
    // set up fps counter
    std::string fontPath = "resources/fonts/MesloLGS NF Regular.ttf";
    app->getLogger()->log("Font loaded");
    
    window->setFramerateLimit(TARGET_FRAMERATE);
    
    // setup ImGui
    if (!ImGui::SFML::Init(*window, false))
    {
      std::string err = "Couldn't initialize ImGui";
      app->getLogger()->log(err, Logger::Logger::LogLevel::critical);
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
    
    // setup font
    io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 12.0f);
    if (!ImGui::SFML::UpdateFontTexture())
    {
      std::string err = fmt::format("Couldn't update texture atlas, Font file: {}", fontPath);
      app->getLogger()->log(err, Logger::Logger::LogLevel::critical);
      throw err;
    }
    
    // initial draw before run() is running
    window->clear(DEFAULT_COLOR);
    window->display();
    
    app->getTarget()->clear(DEFAULT_COLOR);
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
          // app resize is handled by "Main" window in update
          
          // prevent distortion when the window is resized
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
    ImGui::SFML::Update(*window, elapsed);
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    // this needs to be beneath the dockspace generation for it to be dockable
    app->update(elapsed);
    
    ImGui::Begin("Main");
    ImVec2 imSize = ImGui::GetContentRegionAvail();
    app->setSize(sf::Vector2u(imSize.x, imSize.y));
    ImGui::Image(*(app->getTarget()));
    ImGui::End();
  }
  
  void Framework::draw()
  {
    // draw the application
    app->getTarget()->clear(DEFAULT_COLOR);
    app->getTarget()->draw(*app);
    app->getTarget()->display();
    
    // draw the window
    window->clear(DEFAULT_COLOR);
    ImGui::SFML::Render(*window);
  
    window->display();
  }
} // Application