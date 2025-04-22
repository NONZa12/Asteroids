#pragma once

class Bullet
{
	float angle;
	float death_timer;

	sf::Vector2f position;
	

public:
	Bullet(sf::Vector2f position, float angle);

	bool is_dead() const;

	void Draw(sf::RenderWindow& window);
	void Update(float deltatime);


};