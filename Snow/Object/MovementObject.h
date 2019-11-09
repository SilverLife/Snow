// ☕ Привет
#pragma once

#include "../GameLogic/Movement.h"

namespace Snow
{
	namespace Object
	{
		class MovementObject
		{
			Line _movement_line;
			Point _position;
			Point _motion_sign;

		public:
			MovementObject(Point start_position, Point aim)
				: _movement_line(start_position, start_position + aim)
				, _position(start_position)
				, _motion_sign(Shared::Geometry::SignCoordinates(aim))
			{}

			Point GetNewPosition() const
			{
				return GameLogic::Movement::GetNextPosition(_position, _movement_line, _motion_sign);
			}

			void Move(Point new_position)
			{
				_position = new_position;
			}
		};
	}
}