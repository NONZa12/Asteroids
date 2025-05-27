#pragma once

class Asteroid
{
	float angle;

	sf::Vector2f position;

public:
	Asteroid();

	void Draw(sf::RenderWindow& window);
	void Update(float deltatime);
};