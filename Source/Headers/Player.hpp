#pragma once

#include "Headers/Bullet.hpp"
#include "Headers/Asteroid.hpp"

class Player
{
	bool dead;

	float angle;
	float shoot_timer;

	sf::Vector2f position;
	sf::Vector2f origin;

	std::vector<Bullet> bullets;

public:
	Player();

	void Draw(sf::RenderWindow& window);
	void Update(float deltatime);
	void CheckCollision(std::vector<Asteroid>& asteroids);
};
