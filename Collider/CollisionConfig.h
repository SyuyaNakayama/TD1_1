#pragma once

namespace CollisionAttribute
{
	enum
	{
		Player = 0b1,
		Wall = 0b1 << 1,
		Goal = 0b1 << 2,
	};
}

namespace CollisionMask
{
	enum
	{
		Player = ~CollisionAttribute::Player,
		Wall = ~CollisionAttribute::Wall,
	};
}