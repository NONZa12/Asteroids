#pragma once

namespace gbl
{
		constexpr float PI = 3.14159265359f;

		namespace player
		{
			constexpr float PLAYER_SPEED = 200.f;
			constexpr float TURN_SPEED = 150.f;
			constexpr float SHOOT_DELAY = 0.3f;
		}

		namespace bullet
		{
			constexpr float BULLET_SPEED = 300.f;
			constexpr float BULLET_LIFE = 5.f;
		}
}