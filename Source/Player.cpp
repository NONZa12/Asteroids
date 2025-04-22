#include <SFML/Graphics.hpp>
#include <iostream>

#include "Headers/Bullet.hpp"
#include "Headers/Global.hpp"
#include "Headers/Player.hpp"

Player::Player() :
	position(300, 300),
	angle(0),
	origin(0, 31)
{

}

void Player::Draw(sf::RenderWindow& window)
{
	for (Bullet& bullet : bullets)
	{
		bullet.Draw(window);
	}

	sf::Transform transform;
	transform.translate(position).rotate(sf::degrees(angle));

	sf::Texture texture;
	if (!texture.loadFromFile("Source/Resources/Images/player.png"))
	{
		std::cerr << "Error loading PLAYER texture" << std::endl;
	}
	sf::Sprite player(texture);
	player.setOrigin(origin);

	window.draw(player, transform);
}

void Player::Update(float deltatime)
{
	for (Bullet& bullet : bullets)
	{
		bullet.Update(deltatime);
	}

	float radian = angle * (gbl::PI / 180.f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		angle -= deltatime * gbl::player::TURN_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		angle += deltatime * gbl::player::TURN_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		position.x += cos(radian) * deltatime * gbl::player::PLAYER_SPEED;
		position.y += sin(radian) * deltatime * gbl::player::PLAYER_SPEED;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		bullets.push_back(Bullet(position, angle));
	}
	
}