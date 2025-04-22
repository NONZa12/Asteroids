#include <SFML/Graphics.hpp>
#include <iostream>

#include "Headers/Global.hpp"
#include "Headers/Bullet.hpp"

Bullet::Bullet(sf::Vector2f position, float angle) :
	position(),
	angle()
{
	this->position = position;
	this->angle = angle;
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
	window.draw(bullet, tranform);
}

void Bullet::Update(float deltatime)
{
	float radian = angle * (gbl::PI / 180.f);

	position.x += cos(radian) * deltatime * gbl::bullet::BULLET_SPEED;
	position.y += sin(radian) * deltatime * gbl::bullet::BULLET_SPEED;
}