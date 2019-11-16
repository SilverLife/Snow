// ☕ Привет
#pragma once

#include <array>

#include "../Shared/FieldData/Field.h"
#include "../Object/FieldObjects.h"
#include "../CommonDefines.h"
#include "../Shared/ConsoleHelper/ConsoleHelper.h"

using namespace Snow::Object;

namespace Snow
{
	namespace Graphics
	{
		static const std::array<unsigned char,static_cast<size_t>(Object::FieldObject::Count)> kObjectSymbols = 
		{
			' ', // Empty = 0,
			'*', // Ball = 1,
			219, // UndestructbleWall = 2,
			177, // Wall = 3,
			253  // DeathHole = 4,
		};
	   
		class GraphicField
		{
			Shared::FieldData::Field<Object::FieldObject, PointCoordType> _field;

			Point InvertPosition(Point position)
			{
				return 
				{
					position._x,
					_field.Size()._height - position._y - 1
				};
			}

		public:
			GraphicField(Size field_size)
				: _field(field_size._width, field_size._height) {}

			Snow::Size Size() const { return _field.Size(); }

			void SetObject(Point position, Object::FieldObject object)
			{
				const auto invertion_position = InvertPosition(position);
				Shared::ConsoleHelper::Console().Print(invertion_position, kObjectSymbols[static_cast<int>(object)]);
				_field.SetObject(position, object);
			}

			void MoveObject(Point old_position, Point new_position)
			{
				SetObject(new_position, _field.Object(old_position));
				SetObject(old_position, FieldObject::Empty);

			}

			bool IsEmpty(Point position) const { return _field.Object(position) == FieldObject::Empty; }

			bool IsWall(Point position) const { return _field.Object(position) == FieldObject::Wall; }

			bool IsObstacle(Point position) const
			{
				return  _field.Object(position) == FieldObject::Wall ||
					    _field.Object(position) == FieldObject::UndestructbleWall ||
						_field.Object(position) == FieldObject::Ball;
			}
			
			bool IsDeathHole(Point position) const { return _field.Object(position) == FieldObject::DeathHole; }

			void Print(Point p, char ch)
			{
				const auto invertion_position = InvertPosition(p);
				if (!_field.IsOutOfField(invertion_position))
				{
					Shared::ConsoleHelper::Console().Print(invertion_position,ch);
				}
			}
		};
	}
}