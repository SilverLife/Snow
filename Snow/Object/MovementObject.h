// ☕ Привет
#pragma once

#include "../Shared/ConsoleHelper/ConsoleHelper.h"
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

			Point Position() const { return _position; }
			Point MotionSign() const { return _motion_sign; }


			void Move(Point new_position)
			{
				_position = new_position;
			}

			void Reverse()
			{
				_motion_sign._x *= -1;
				_motion_sign._y *= -1;
				//_movement_line.ConfigureByTwoPoints(_position, _position + _motion_sign);
			}

			// Повернуть направляющую линию относительно оси Ox
			void RotateMovementLineByX()
			{
				double angle = Shared::Geometry::AngleBetweenLineAndPoint(_movement_line, BasisPointX);
				if (_motion_sign._x * _motion_sign._y < 0)
				{
					angle *= -1;
				}
				_movement_line.Rotate(2*angle, _position);
				_motion_sign._y *= -1;
			}

			// Повернуть направляющую линию относительно оси Oy
			void RotateMovementLineByY()
			{
				double angle = Shared::Geometry::AngleBetweenLineAndPoint(_movement_line, BasisPointY);
				if (_motion_sign._x * _motion_sign._y > 0)
				{
					angle *= -1;
				}
				_movement_line.Rotate(2 * angle, _position);
				_motion_sign._x *= -1;
			}
		};
	}
}