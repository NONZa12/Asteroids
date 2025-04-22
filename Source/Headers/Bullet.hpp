#pragma once

class Bullet
{
	float angle;

	sf::Vector2f position;
	

public:
	Bullet(sf::Vector2f position, float angle);

	void Draw(sf::RenderWindow& window);
	void Update(float deltatime);


};