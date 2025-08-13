#include <SFML/Graphics.hpp>
#include <iostream>

#include "Headers/Global.hpp"
#include "Headers/Game.hpp"
#include "Headers/Bullet.hpp"
#include "Headers/Drawtext.hpp"

Game::Game() :
	window(sf::VideoMode({ gbl::screen::WIDTH*2, gbl::screen::HEIGHT*2 }), "Asteroids", sf::Style::Close),
	deltatime(0),
	generator(static_cast<unsigned int>(seed.getElapsedTime().asMicroseconds()))

{
	window.setView(sf::View(sf::FloatRect({0,0}, { gbl::screen::WIDTH, gbl::screen::HEIGHT})));

	if (!background_texture.loadFromFile("Source/Resources/Images/background.png"))
	{
		std::cerr << "Error loading BACKGROUND texture" << std::endl;
	}
	background.setTexture(&background_texture);
	background.setSize({ gbl::screen::WIDTH, gbl::screen::HEIGHT });

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

		window.draw(background);

		if (asteroids.empty())
		{
			draw_text({gbl::screen::WIDTH * 0.5f, gbl::screen::HEIGHT * 0.5f - 25.f}, "WIN!!! PRESS R TO RESTART", window);
		}
		else if (player.is_dead() == 0)
		{
			for (Asteroid& asteroid : asteroids)
			{
				asteroid.Draw(window);
			}

			player.Draw(window);
		}
		else
		{
			draw_text({ gbl::screen::WIDTH * 0.5f, gbl::screen::HEIGHT * 0.5f - 25.f}, "LOSE!!! PRESS R TO RESTART", window);
		}

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
	has_focus = window.hasFocus();

	if (has_focus)
	{

		if (asteroids.size() > 0 && player.is_dead() == 0)
		{

			for (Asteroid& asteroid : asteroids)
			{
				asteroid.Update(deltatime);
			}

			player.Update(deltatime);
			player.CheckCollision(asteroids);

			for (unsigned int i = 0; i < asteroids.size(); i++)
			{
				if (asteroids[i].is_dead())
				{
					asteroids.erase(i + asteroids.begin());

					i--;
				}
			}
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R))
		{
			generate_asteroids();

			player.reset();
		}
	}
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