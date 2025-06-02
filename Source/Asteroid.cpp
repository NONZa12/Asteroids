#include <SFML/Graphics.hpp>
#include <iostream>

#include "Headers/Asteroid.hpp"
#include "Headers/Global.hpp"

Asteroid::Asteroid(sf::Vector2f _position, float _angle) :
	angle(_angle),
	position(_position)
{

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

	window.draw(asteroid, transform);
}

void Asteroid::Update(float deltatime)
{

}