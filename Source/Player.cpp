#include <SFML/Graphics.hpp>
#include <iostream>

#include "Headers/Global.hpp"
#include "Headers/Player.hpp"

Player::Player() :
	dead(0),
	angle(0),
	shoot_timer(0),
	position(gbl::screen::WIDTH / 2, gbl::screen::HEIGHT / 2),
	origin(6.5, 6.5)
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

	for (unsigned int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].is_dead())
		{
			bullets.erase(i + bullets.begin());

			i--;
		}
	}

	if (dead == 0)
	{

		if (shoot_timer > 0)
		{
			shoot_timer -= deltatime;
		}

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
			float radian = angle * (gbl::PI / 180.f);

			position.x += cos(radian) * deltatime * gbl::player::PLAYER_SPEED;
			position.y += sin(radian) * deltatime * gbl::player::PLAYER_SPEED;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && shoot_timer <= 0)
		{
			shoot_timer = gbl::player::SHOOT_DELAY;

			float radian = angle * (gbl::PI / 180.f);
			sf::Vector2f bullet_position = position + sf::Vector2f(
				cos(radian) * deltatime * gbl::bullet::BULLET_OFFSET,
				sin(radian) * deltatime * gbl::bullet::BULLET_OFFSET
			);

			bullets.push_back(Bullet(bullet_position, angle));
		}
	}
	
}

void Player::CheckCollision(std::vector<Asteroid>& asteroids)
{
	for (Asteroid& asteroid : asteroids)
	{
		if (asteroid.is_dead() == 1)
		{
			continue;
		}

		for (Bullet& bullet : bullets)
		{
			if (bullet.is_dead() == 1)
			{
				continue;
			}

			// delta between asteroid and bullet.
			float dx = bullet.get_x() - asteroid.get_x();
			float dy = bullet.get_y() - asteroid.get_y();

			float distance_fromcircle = dx * dx + dy * dy;
			float radiusSum = bullet.get_radius() + asteroid.get_radius();

			if (distance_fromcircle <= radiusSum * radiusSum)
			{

				bullet.die();
				asteroid.hit();
			}
		}

		if (dead == 1)
		{
			continue;
		}
		//for check collision of player and asteroids
	}
}