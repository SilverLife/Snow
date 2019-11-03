// ☕ Привет
#pragma once

#include "../CommonDefines.h"

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


		class Ball
		{
			Point _position;
			Point _motion_direction;
		public:
			Ball(Point start_position, Point motion_direction)
				: _position(start_position)
				, _motion_direction(motion_direction)
			{}

			Point Position() const { return _position; }

			Point GetNewPosition() const { return _position + _motion_direction; }

			void Move() { _position += _motion_direction; }

			Point Motion() const { return _motion_direction; }

			void ReverseMotionX() { _motion_direction._x *= -1; }
			void ReverseMotionY() { _motion_direction._y *= -1; }

			Point GetMotionX() const { return { _motion_direction._x, 0 }; }
			Point GetMotionY() const { return { 0, _motion_direction._y }; }
		};
	}
}