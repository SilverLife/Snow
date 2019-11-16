// ☕ Привет

#include "SnowGame.h"
#include <thread>

namespace Snow
{
	namespace GameLogic
	{
		void SnowGame::PrepareField()
		{
			const auto [width, height] = _field.Size();
			for (PointCoordType i = 0; i < width; i++)
			{
				_field.SetObject({ i, 0 }, Object::FieldObject::UndestructbleWall);
				_field.SetObject({ i, height - 1 }, Object::FieldObject::UndestructbleWall);
			}
			for (PointCoordType j = 0; j < height; j++)
			{
				_field.SetObject({ 0, j }, Object::FieldObject::UndestructbleWall);
				_field.SetObject({ width - 1, j }, Object::FieldObject::UndestructbleWall);
			}
		}

		void SnowGame::InitializeFieldObjects()
		{
			//const int balls_count = 2000;
			//for (int i = 0; i < balls_count; i++)
			//{
			//	const Point point{ std::rand() % (_field.Size()._width  - 2) + 1,
			//					   std::rand() % (_field.Size()._height - 2) + 1 };
			//
			//	if (_field.IsEmpty(point))
			//	{
			//		_balls.emplace_back(point, Point{ 1,1 });
			//		_field.SetObject(point, FieldObject::Ball);
			//	}
			//}
			//
			//const int wall_count = 200;
			//for (int i = 0; i < wall_count; i++)
			//{
			//	const Point point{ std::rand() % (_field.Size()._width - 2) + 1,
			//		std::rand() % (_field.Size()._height - 2) + 1 };
			//
			//	if (_field.IsEmpty(point))
			//	{
			//		_field.SetObject(point, FieldObject::Wall);
			//	}
			//}


			//const auto[width, height] = _field.Size();
			//for (PointCoordType i = 3; i < width - 3; i++)
			//{
			//	for (PointCoordType j = height - 3; j >= height - 10; j--)
			//	{
			//		//_field.SetObject({ i,j }, FieldObject::Wall);
			//		_field.SetObject({ std::rand()% width,std::rand() % height }, FieldObject::Wall);
			//	}
			//}

			const auto balls_count = 1;
			const auto work_width = _field.Size()._width - 6;
			const auto step = work_width / balls_count;
			for (int i = 0; i < balls_count; i++)
			{
				const Point pos = { static_cast<PointCoordType>(3 + i * step + 30), static_cast<PointCoordType>(25) };
				//const Point pos = { std::rand() % _field.Size()._width, std::rand() % _field.Size()._height };
				_balls.emplace_back(pos, Point{ -(std::rand() % 10),  (std::rand() % 10) }, std::rand() % 20 + 20);
				_field.SetObject(pos, FieldObject::Ball);
			}
		}

		void SnowGame::MoveBalls()
		{
			const auto MoveBall = [this](Object::Ball& ball)
			{
				const auto new_position = ball.GetNewPosition();

				if (ball.Position()._x != new_position._x)
				{
					// Есть движение по x, проверим нет ли там препядствия
					const Point position_motion_x = { new_position._x, ball.Position()._y };
					if (_field.IsObstacle(position_motion_x))
					{
						ball.RotateMovementLineByY();
						if (_field.IsWall(position_motion_x))
						{
							DestructWall(position_motion_x);
						}
						return;
					}
				}

				if (ball.Position()._y != new_position._y)
				{
					// Есть движение по y, проверим нет ли там препядствия
					const Point position_motion_y = { ball.Position()._x, new_position._y };
					if (_field.IsObstacle(position_motion_y))
					{
						ball.RotateMovementLineByX();
						if (_field.IsWall(position_motion_y))
						{
							DestructWall(position_motion_y);
						}
						return;
					}
				}

				// По x и y нет препядствий или движения. Проверяем новую позицию
				if (_field.IsEmpty(new_position))
				{
					_field.MoveObject(ball.Position(), new_position);
					ball.Move(new_position);
					return;
				}
				if (_field.IsDeathHole(new_position))
				{
					// TODO death hole
					return;
				}

				if (_field.IsWall(new_position))
				{
					DestructWall(new_position);
				}

				if (_field.IsObstacle(new_position))
				{
					ball.Reverse();
				}

				return;
			};

			for (unsigned int i = 0; i < _balls.size(); i++)
			{
				if (_balls[i].PerformTick())
				{
					MoveBall(_balls[i]);
				}
			}
		}

		void  SnowGame::DestructWall(Point position)
		{
			_field.SetObject(position, FieldObject::Empty);
		}

		void SnowGame::Action()
		{
			std::this_thread::sleep_for(std::chrono::microseconds(20));
			
			MoveBalls();
		}	
	}
}	