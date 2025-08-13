#pragma once

#include <random>

#include "Headers/Player.hpp"
#include "Headers/Asteroid.hpp"

class Game
{
	Player player;

	bool has_focus;

	float deltatime;

	std::vector<Asteroid> asteroids;

	std::default_random_engine generator;

	sf::RenderWindow window;
	
	sf::Clock seed;

	sf::Texture background_texture;

	sf::RectangleShape background;

public:
	Game();

	bool isOpen();

	void Draw();
	void Handle_event();
	void Update(float deltatime);
	void generate_asteroids();
};