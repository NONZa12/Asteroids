#include <SFML/Graphics.hpp>
#include <iostream>

#include "Headers/Asteroid.hpp"
#include "Headers/Global.hpp"

Asteroid::Asteroid(sf::Vector2f _position, float _angle) :
	hit_timer(gbl::asteroid::ASTEROID_HIT_DURATION),
	dead(0),
	angle(_angle),
	position(_position),
	origin(32, 30)
{
	float radian = angle * (gbl::PI / 180.f);
	velocity.x = cos(radian) * gbl::asteroid::ASTEROID_SPEED;
	velocity.y = sin(radian) * gbl::asteroid::ASTEROID_SPEED;
}

bool Asteroid::is_dead() const
{
	return dead;
}

float Asteroid::get_x() const
{
	return position.x;
}

float Asteroid::get_y() const
{
	return position.y;
}

float Asteroid::get_radius() const
{
	return 64 - origin.x;
}

void Asteroid::Draw(sf::RenderWindow& window)
{
	sf::Transform transform;
	transform.translate(position).rotate(sf::degrees(angle));

	sf::Texture texture;
	if (!texture.loadFromFile("Source/Resources/Images/asteroid.png"))
	{
		std::cerr << "Error loading BULLET texture" << std::endl;
	}

	sf::Sprite asteroid(texture);
	asteroid.setOrigin(origin);

	window.draw(asteroid, transform);
}

void Asteroid::Update(float deltatime)
{
	if (hit_timer <= gbl::asteroid::ASTEROID_HIT_DURATION)
	{
		if (hit_timer > 0)
		{
			hit_timer--;
		}
		else
		{
			dead = 1;
			std::cout << "dead";
		}
	}

	position += velocity * deltatime;

	if (position.x < 0.f || position.x > gbl::screen::WIDTH)
	{
		velocity.x *= -1;
	}

	if (position.y < 0.f || position.y > gbl::screen::HEIGHT)
	{
		velocity.y *= -1;
	}
}

void Asteroid::hit()
{
	if (hit_timer == gbl::asteroid::ASTEROID_HIT_DURATION)
	{
		hit_timer--;
	}
}