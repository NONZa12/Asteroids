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

bool Player::is_dead() const
{
	return dead;
}

float Player::get_x() const
{
	return position.x;
}

float Player::get_y() const
{
	return position.y;
}

float Player::get_radius() const
{
	return 16 - origin.x;
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
			float dx_bullet = bullet.get_x() - asteroid.get_x();
			float dy_bullet = bullet.get_y() - asteroid.get_y();

			float distance_fromcircle_bullet = dx_bullet * dx_bullet + dy_bullet * dy_bullet;
			float radiusSum_bullet = bullet.get_radius() + asteroid.get_radius();

			if (distance_fromcircle_bullet <= radiusSum_bullet * radiusSum_bullet)
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

		float dx_player = get_x() - asteroid.get_x();
		float dy_player = get_y() - asteroid.get_y();

		float distance_fromcircle_player = dx_player * dx_player + dy_player * dy_player;
		float radiusSum_player = get_radius() + asteroid.get_radius();

		if (distance_fromcircle_player <= radiusSum_player * radiusSum_player)
		{
			dead = 1;
		}
	}
}

void Player::reset()
{
	position.x = 0.5f * gbl::screen::WIDTH;
	position.y = 0.5f * gbl::screen::HEIGHT;

	shoot_timer = 0;

	bullets.clear();
}