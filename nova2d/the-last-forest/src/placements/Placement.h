#pragma once
#include "graphics/Image.h"
#include "../scenes/Scenes.h"
#include "ai/SimpleWeakAI.h"

namespace thelastforest
{
	namespace placements
	{
		using namespace novazero::graphics;
		using namespace novazero::ai;
		using namespace scenes;

		class Placement :
			public SimpleWeakAI
		{

		private:

			unsigned int m_HumanDelay = 0;

		public:

			Placement() {};
			Placement(GridTypes type, unsigned int humanDelay,
				unsigned int gridPos, Vec2Int size, unsigned char layer);

		};
	}
}