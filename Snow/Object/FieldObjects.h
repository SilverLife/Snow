// ☕ Привет
#pragma once

#include "../CommonDefines.h"
#include "../Shared/CommonStructs/Ticker.h"
#include "MovementObject.h"

namespace Snow
{
	namespace Object
	{
		enum class FieldObject : char
		{
			Empty = 0,
			Ball = 1,
			UndestructbleWall = 2,
			Wall = 3,
			DeathHole = 4,
			Count
		};




		class Ball : public Shared::CommonStructs::TickerInt, public MovementObject
		{
		public:
			Ball(Point start_position, Point motion_direction, int speed)
				: MovementObject(start_position, motion_direction)
				, Shared::CommonStructs::TickerInt(speed)
			{}
		};
	}
}