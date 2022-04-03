#pragma once
#include "../actors/Trees.h"
#include "../scenes/Scenes.h"
#include "../placements/Placement.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace actors;
		using namespace placements;

		class AllScenes
		{

		public:

			static Trees* s_Trees[7];
			static GridTypes s_Grid[81];
			static Placement* s_Placements[81];

			static void NewGame();

			static unsigned int GetTileFromPosition(Vec2 position,
				unsigned int tileWidth, unsigned int tileHeight,
				unsigned int columns, unsigned int rows);

			static Vec2 GetTopLeftOfGridCell(
				unsigned int tileWidth, unsigned int tileHeight,
				unsigned int columns, unsigned int rows);

			static Vec2 GetPositionFromTile(unsigned int gridPosition, unsigned int columns);

			static Vec2 SnapToGrid(Vec2 position,
				unsigned int tileWidth, unsigned int tileHeight,
				unsigned int columns, unsigned int rows);

			static void SetGridPosition(unsigned int gridPosition, GridTypes type);
			static GridTypes GetGridPositionType(unsigned int gridPosition);
		};
	}
}