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


			const auto[width, height] = _field.Size();
			for (PointCoordType i = 3; i < width - 3; i++)
			{
				for (PointCoordType j = height - 3; j >= height - 10; j--)
				{
					_field.SetObject({ i,j }, FieldObject::Wall);
				}
			}

			const auto balls_count = 5;
			const auto work_width = _field.Size()._width - 6;
			const auto step = work_width / balls_count;
			for (int i = 0; i < balls_count; i++)
			{
				const Point pos = { static_cast<PointCoordType>(3 + i * step), static_cast<PointCoordType>(5) };
				_balls.emplace_back(pos, Point{ -1,1 });
				_field.SetObject(pos, FieldObject::Ball);
			}

			for (PointCoordType i = work_width / 2 - 4; i < work_width / 2 + 4; i++)
			{
				_player_block.emplace_back(Point{ i, static_cast<PointCoordType>(2) });
				_field.SetObject(Point{ i, static_cast<PointCoordType>(2) }, FieldObject::UndestructbleWall);
			}
		}

		void SnowGame::MoveBalls()
		{
			const auto MoveBall = [this](Object::Ball& ball)
			{
				const Point position_motion_x = ball.Position() + ball.GetMotionX();
				const Point position_motion_y = ball.Position() + ball.GetMotionY();

				const bool is_obtacle_x = _field.IsObstacle(position_motion_x);
				if (is_obtacle_x)
				{
					ball.ReverseMotionX();
				}
				const bool is_obtacle_y = _field.IsObstacle(position_motion_y);
				if (is_obtacle_y)
				{
					ball.ReverseMotionY();
				}

				if (_field.IsWall(position_motion_x))
				{
					DestructWall(position_motion_x);
				}
				if (_field.IsWall(position_motion_y))
				{
					DestructWall(position_motion_y);
				}

				if (!is_obtacle_x && !is_obtacle_y)
				{
					const auto new_position = ball.GetNewPosition();

					if (_field.IsEmpty(new_position))
					{
						_field.MoveObject(ball.Position(), new_position);
						ball.Move();
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
						ball.ReverseMotionX();
						ball.ReverseMotionY();
					}

					return;
				}
			};

			for (unsigned int i = 0; i < _balls.size(); i++)
			{
				MoveBall(_balls[i]);
			}
		}

		void  SnowGame::DestructWall(Point position)
		{
			_field.SetObject(position, FieldObject::Empty);
		}

		void SnowGame::Action()
		{
			std::this_thread::sleep_for(std::chrono::microseconds(2));
			static int tick = 0;
			if (tick++ > 30)
			{
				tick = 0;
				MoveBalls();
			}

			if (_platform_offset != 0)
			{
				MovePlatform(_platform_offset < 0);
			}
		}

		void SnowGame::MovePlatform(bool to_left)
		{
			if (to_left)
			{
				if (_field.IsEmpty(_player_block.front() - Point{ 1, 0 }))
				{
					for (unsigned int i = 0; i < _player_block.size(); i++)
					{
						_field.MoveObject(_player_block[i], _player_block[i] - Point{1, 0});
						_player_block[i] -= Point{ 1, 0 };
					}
				}
			}
			else
			{
				if (_field.IsEmpty(_player_block.back() + Point{ 1, 0 }))
				{
					for (int i = _player_block.size() - 1; i >= 0; i--)
					{
						_field.MoveObject(_player_block[i], _player_block[i] + Point{ 1, 0 });
						_player_block[i] += Point{ 1, 0 };
					}
				}
			}
		}

		void SnowGame::OnKeyPressed(char ch)
		{
			switch (ch)
			{
			case 'a': _platform_offset = -1; break;
			case 'd': _platform_offset = 1; break;
			case 27 : _is_game_active = false; break;
			}
		}
	}
}	