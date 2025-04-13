#include "LoopManagement.hpp"
#include "GameState.hpp"
#include "MenuState.hpp"
#include <SFML/Graphics.hpp>

int main() {
    LoopManagement mainLoop;

    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(sf::VideoMode(desktopMode.width, desktopMode.height), "Runner", sf::Style::None);
    window.setFramerateLimit(200);

    std::unique_ptr<MenuState> menuState = std::make_unique<MenuState>();;
    menuState->setLoopManager(&mainLoop);
    mainLoop.changeState(std::move(menuState), window);
    mainLoop.run(window);

    return 0;
}