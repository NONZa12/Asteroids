#include <SFML/Graphics.hpp>
#include <iostream>

#include "Headers/Global.hpp"
#include "Headers/Bullet.hpp"

Bullet::Bullet(sf::Vector2f _position, float _angle) :
	angle(_angle),
	death_timer(gbl::bullet::BULLET_LIFE),
	position(_position),
	origin(3, 2)
{

}

bool Bullet::is_dead() const
{
	return death_timer <= 0;
}

float Bullet::get_x() const
{
	return position.x;
}

float Bullet::get_y() const
{
	return position.y;
}

float Bullet::get_radius() const
{
	return 5 - origin.x;
}

void Bullet::die()
{
	death_timer = 0;
}

void Bullet::Draw(sf::RenderWindow& window)
{
	sf::Transform tranform;
	tranform.translate(position).rotate(sf::degrees(angle));

	sf::Texture texture;
	if (!texture.loadFromFile("Source/Resources/Images/bullet.png"))
	{
		std::cerr << "Error loading BULLET texture" << std::endl;
	}

	sf::Sprite bullet(texture);
	bullet.setOrigin(origin);

	window.draw(bullet, tranform);
}

void Bullet::Update(float deltatime)
{

	float radian = angle * (gbl::PI / 180.f);

	position.x += cos(radian) * deltatime * gbl::bullet::BULLET_SPEED;
	position.y += sin(radian) * deltatime * gbl::bullet::BULLET_SPEED;

	if (death_timer > 0)
	{
		death_timer -= deltatime;
	}
}