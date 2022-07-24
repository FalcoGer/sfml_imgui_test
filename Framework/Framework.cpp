#include <stdexcept>

#include "Framework.hpp"
#include "Application.hpp"

namespace Application
{
  Framework::Framework(const unsigned int W, const unsigned int H, const std::string& TITLE, std::unique_ptr<Application> application)
  : mpt_window{std::make_shared<sf::RenderWindow>(sf::VideoMode(W, H), TITLE, sf::Style::Default)},
    TARGET_FRAMERATE{60},
    DEFAULT_COLOR{sf::Color(0x10, 0x10, 0x30, 0xFF)}
  {
    this->mpt_app = std::move(application);
    const std::string fontPath = "resources/fonts/MesloLGS NF Regular.ttf";
    
    mpt_window->setFramerateLimit(TARGET_FRAMERATE);
    
    // setup ImGui
    if (!ImGui::SFML::Init(*mpt_window, false))
    {
      std::string err = "Couldn't initialize ImGui";
      mpt_app->getLogger()->log(err, Logger::Logger::LogLevel::critical);
      throw std::runtime_error(err);
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
      mpt_app->getLogger()->log(err, Logger::Logger::LogLevel::critical);
      throw std::runtime_error(err);
    }
    
    // initial draw before run() is running
    mpt_window->clear(DEFAULT_COLOR);
    mpt_window->display();
    
    mpt_app->getTarget()->clear(DEFAULT_COLOR);
  }
  
  Framework::~Framework()
  {
    ImGui::SFML::Shutdown(*mpt_window);
  }
  
  int Framework::run()
  {
    m_clk.restart();
    while (this->mpt_window->isOpen())
    {
      handleEvents();
      update(m_clk.restart());
      draw();
    }
    return 0;
  }
  
  unsigned int Framework::handleEvents()
  {
    sf::Event ev{};
    unsigned int count = 0;
    while(mpt_window->pollEvent(ev))
    {
      count++;
      ImGui::SFML::ProcessEvent(ev);
      switch (ev.type)
      {
        case sf::Event::Closed:
        {
          mpt_window->close();
          break;
        }
        case sf::Event::Resized:
        {
          // mpt_app resize is handled by "Main" mpt_window in update
          
          // prevent distortion when the mpt_window is resized
          mpt_window->setView(sf::View(sf::Rect<float>(0, 0, static_cast<float>(ev.size.width),
                                                       static_cast<float>(ev.size.height))));
        }
        default:
        {
          break;
        }
      }
      mpt_app->handleEvent(ev);
    }
    return count;
  }
  
  void Framework::update(const sf::Time& elapsed)
  {
    ImGui::SFML::Update(*mpt_window, elapsed);
    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
    // this needs to be beneath the dockspace generation for it to be dockable
    mpt_app->update(elapsed);
    
    ImGui::Begin("Main");
    ImVec2 imSize = ImGui::GetContentRegionAvail();
    mpt_app->setSize(sf::Vector2u(static_cast<unsigned int>(imSize.x), static_cast<unsigned int>(imSize.y)));
    ImGui::Image(*(mpt_app->getTarget()));
    ImGui::End();
  }
  
  void Framework::draw()
  {
    // draw the application
    mpt_app->getTarget()->clear(DEFAULT_COLOR);
    mpt_app->getTarget()->draw(*mpt_app);
    mpt_app->getTarget()->display();
    
    // draw the mpt_window
    mpt_window->clear(DEFAULT_COLOR);
    ImGui::SFML::Render(*mpt_window);
  
    mpt_window->display();
  }
} // Application