#pragma once

namespace gbl
{
		constexpr float PI = 3.141592653589793116f;

		namespace player
		{
			constexpr float PLAYER_SPEED = 150.f;
			constexpr float TURN_SPEED = 175.f;
			constexpr float SHOOT_DELAY = 0.3f;
			constexpr unsigned int PLAYER_SAFEZONE = 45;
		}

		namespace bullet
		{
			constexpr float BULLET_OFFSET = 50.f;
			constexpr float BULLET_SPEED = 300.f;
			constexpr float BULLET_LIFE = 5.f;
		}

		namespace asteroid
		{
			constexpr unsigned int ASTEROID_TOTAL = 10;
			constexpr float ASTEROID_SPEED = 50.f;
		}

		namespace screen
		{
			constexpr unsigned short WIDTH = 640;
			constexpr unsigned short HEIGHT = 432;
		}
}