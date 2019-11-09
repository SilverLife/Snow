// ☕ Привет
#pragma once

#include <array>

#include "../CommonDefines.h"

namespace Snow
{
	namespace GameLogic::Movement
	{
		static Point GetNextPosition(Point cur_pos, const Line& aim_line, Point aim_sign)
		{
			const auto [x_sign, y_sign] = aim_sign;
			if (x_sign == 0)
			{
				return { cur_pos._x, cur_pos._y + y_sign };
			}
			if (y_sign == 0)
			{
				return { cur_pos._x + x_sign, cur_pos._y };
			}

			std::array<Point, 3> candidate_points =
			{
				Point{ cur_pos._x + x_sign, cur_pos._y },
				Point{ cur_pos._x,          cur_pos._y + y_sign },
				Point{ cur_pos._x + x_sign, cur_pos._y + y_sign }
			};

			std::array<double, 3> candidate_points_distance_to_line =
			{
				aim_line.Distance(candidate_points[0]),
				aim_line.Distance(candidate_points[1]),
				aim_line.Distance(candidate_points[2])
			};

			if (candidate_points_distance_to_line[0] < candidate_points_distance_to_line[1])
			{
				if (candidate_points_distance_to_line[0] < candidate_points_distance_to_line[2])
				{
					return candidate_points[0];
				}
				return  candidate_points[2];
			}
			if (candidate_points_distance_to_line[1] < candidate_points_distance_to_line[2])
			{
				return candidate_points[1];
			}
			return candidate_points[2];
		}

		static Point GetNextPosition(Point cur_pos, Point aim_pos)
		{
			const Line aim_line(cur_pos, aim_pos);

			return GetNextPosition(cur_pos, aim_line, aim_pos);
		}

		static std::vector<Point> GetPath(Point start_pos, Point end_pos)
		{
			const Line aim_line(start_pos, end_pos);
			std::vector<Point> result;
			result.reserve(std::abs(end_pos._x - start_pos._x) + std::abs(end_pos._y - start_pos._y));
			result.push_back(start_pos);
			const auto aim_sign = SignCoordinates(end_pos - start_pos);
			while (result.back() != end_pos)
			{
				result.emplace_back(GameLogic::Movement::GetNextPosition(result.back(), aim_line, aim_sign));
			}
			return result;
		}
	}
}