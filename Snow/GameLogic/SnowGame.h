// ☕ Привет
#pragma once

#include <vector>

#include "../Graphics/GraphicField.h"
#include "../CommonDefines.h"

namespace Snow
{
	namespace GameLogic
	{
		class SnowGame
		{
			Graphics::GraphicField _field;

			std::vector<Object::Ball> _balls;

			bool _is_game_active = true;
			
			void PrepareField();

			void InitializeFieldObjects();

			void MoveBalls();

			void DestructWall(Point position);

			void MovePlatform(bool to_left);
		public:
			SnowGame(Size field_size)
				:_field(field_size)
			{
				PrepareField();
				InitializeFieldObjects();
			}

			void Action();

			bool IsGameOver() const { return !_is_game_active; }

		};
	}
}