#include <SFML/Graphics.hpp>

#include "Headers/Game.hpp"

int main()
{
    Game game;

    sf::Clock clock;

    while (game.isOpen())
    {
        float deltatime = clock.restart().asSeconds();

        game.Handle_event();

        game.Update(deltatime);
        game.Draw();
    }
}