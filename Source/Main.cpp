#include <SFML/Graphics.hpp>

#include "Headers/Player.hpp"
#include "Headers/Bullet.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1200, 900 }), "Asteroids", sf::Style::Close | sf::Style::Titlebar);

    sf::Clock clock;

    Player player;

    while (window.isOpen())
    {
        float deltatime = clock.restart().asSeconds();

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

		player.Update(deltatime);


        window.clear();
        player.Draw(window);
        window.display();
    }
}