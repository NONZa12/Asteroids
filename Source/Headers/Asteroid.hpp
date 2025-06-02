#pragma once

class Asteroid
{
	float angle;

	sf::Vector2f position;

public:
	Asteroid( sf::Vector2f _position, float _angle);

	void Draw(sf::RenderWindow& window);
	void Update(float deltatime);
};