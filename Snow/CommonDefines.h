#pragma once

#include "Shared\Geometry\Point.h"
#include "Shared\Geometry\RectangleSize.h"

namespace Snow
{
	using PointCoordType = short;
	using Point = Shared::Geometry::Point<PointCoordType>;
	using Size = Shared::Geometry::RectangleSize<PointCoordType>;
}