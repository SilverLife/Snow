#pragma once

#include "Shared\Geometry\Point.h"
#include "Shared\Geometry\RectangleSize.h"
#include "../Shared/Geometry/Line.h"

namespace Snow
{
	using PointCoordType = short;
	using Point = Shared::Geometry::Point<PointCoordType>;
	using Size = Shared::Geometry::RectangleSize<PointCoordType>;
	using Line = Shared::Geometry::Line<double>;

	static Point BasisPointX{ static_cast<PointCoordType>(1), static_cast<PointCoordType>(0) };
	static Point BasisPointY{ static_cast<PointCoordType>(0), static_cast<PointCoordType>(1) };
}