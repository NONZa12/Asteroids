#include <SFML/Graphics.hpp>

#include "Headers/Global.hpp"
#include "Headers/Game.hpp"
#include "Headers/Bullet.hpp"

Game::Game() :
	window(sf::VideoMode({ gbl::screen::WIDTH*2, gbl::screen::HEIGHT*2 }), "Asteroids", sf::Style::Close),
	deltatime(0),
	generator(static_cast<unsigned int>(seed.getElapsedTime().asMicroseconds()))

{
	window.setView(sf::View(sf::FloatRect({0,0}, { gbl::screen::WIDTH, gbl::screen::HEIGHT})));

	has_focus = window.hasFocus();

	generate_asteroids();
}

bool Game::isOpen()
{
	return window.isOpen();
}

void Game::Draw()
{
	if (has_focus)
	{
		window.clear();

		for (Asteroid& asteroid : asteroids)
		{
			asteroid.Draw(window);
		}
		player.Draw(window);

		window.display();

	}
}

void Game::Handle_event()
{
	while (const std::optional event = window.pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			window.close();
		}
	}
}

void Game::Update(float deltatime)
{
	player.Update(deltatime);
}

void Game::generate_asteroids()
{
	asteroids.clear();

	for (unsigned int a = 0; a < gbl::asteroid::ASTEROID_TOTAL; a++)
	{
		unsigned int random_x = 0;
		unsigned int random_y = 0;
		unsigned int random_angle = 0;

		do
		{
			std::uniform_int_distribution<unsigned int> distribution_x(0, gbl::screen::WIDTH - 64);
			random_x = distribution_x(generator);

			std::uniform_int_distribution<unsigned int> distribution_y(0, gbl::screen::HEIGHT - 64);
			random_y = distribution_y(generator);

			std::uniform_int_distribution<unsigned int> distribution_angle(0, 359);
			random_angle = distribution_angle(generator);
		}
		while (random_x > 0.5f * gbl::screen::WIDTH - gbl::player::PLAYER_SAFEZONE &&
				random_x < gbl::player::PLAYER_SAFEZONE + 0.5f * gbl::screen::WIDTH &&
				random_y > 0.5f * gbl::screen::HEIGHT - gbl::player::PLAYER_SAFEZONE &&
				random_y < gbl::player::PLAYER_SAFEZONE + 0.5f * gbl::screen::HEIGHT);

			asteroids.push_back(Asteroid(sf::Vector2f(static_cast<float>(random_x), static_cast<float>(random_y)), static_cast<float>(random_angle)));
	}
}