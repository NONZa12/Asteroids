#pragma once

class Bullet
{
	float angle;
	float death_timer;

	sf::Vector2f position;	
	sf::Vector2f origin;

public:
	Bullet(sf::Vector2f _position, float _angle);

	bool is_dead() const;

	float get_x() const;
	float get_y() const;
	float get_radius() const;

	void die();
	void Draw(sf::RenderWindow& window);
	void Update(float deltatime);
};