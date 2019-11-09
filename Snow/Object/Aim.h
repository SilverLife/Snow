// ☕ Привет
#pragma once

#include "../CommonDefines.h"

#include "../Shared/ConsoleHelper/ConsoleHelper.h"
#include "../GameLogic/Movement.h"

namespace Snow
{
	namespace Object
	{
		class Aim
		{
			Point _position;
			Point _aim;

			std::vector<Point> _cur_aim_path;

			void DrawCurAim(char ch)
			{
				Shared::ConsoleHelper::Console().Print(_cur_aim_path.front(), ch, Shared::ConsoleHelper::Color::Blue);
				for (unsigned int i = 0; i < _cur_aim_path.size() - 1; i++)
				{
					Shared::ConsoleHelper::Console().Print(_cur_aim_path[i], ch);
				}
				Shared::ConsoleHelper::Console().Print(_cur_aim_path.back() , ch, Shared::ConsoleHelper::Color::Yellow);
			}

		public:
			Aim(Point position, Point aim)
			: _position(position)
			, _aim(aim)
			, _cur_aim_path(GameLogic::Movement::GetPath(_position, _aim))
			{
				DrawCurAim('*');
			}

			void MoveAim(char ch)
			{
				switch (ch)
				{
				case 'a': _aim._x--; break;
				case 'd': _aim._x++; break;
				case 'w': _aim._y--; break;
				case 's': _aim._y++; break;
				}

				DrawCurAim(' ');
				_cur_aim_path = GameLogic::Movement::GetPath(_position, _aim);
				DrawCurAim('*');
			}
		};
	}
}