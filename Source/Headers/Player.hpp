#pragma once

class Bullet;

class Player
{
	float angle;
	float shoot_timer;

	sf::Vector2f position;
	sf::Vector2f origin;

	std::vector<Bullet> bullets;

public:
	Player();

	void Draw(sf::RenderWindow& window);
	void Update(float deltatime);
};
