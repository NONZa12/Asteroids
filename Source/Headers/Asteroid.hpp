#pragma once

class Asteroid
{
	int hit_timer;

	bool dead;

	float angle;

	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f origin;

public:
	Asteroid(sf::Vector2f _position, float _angle);

	bool is_dead() const;

	float get_x() const;
	float get_y() const;
	float get_radius() const;

	void Draw(sf::RenderWindow& window);
	void Update(float deltatime);
	void hit();
};