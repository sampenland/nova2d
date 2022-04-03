#pragma once
#include "../actors/Trees.h"
#include "../Enums.h"
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

			static void SetPlacementAt(Placement* placement, unsigned int gridPosition);
			static Placement* GetPlacementAt(unsigned int gridPosition);

			static int GetTileFromPosition(Vec2 position,
				unsigned int tileWidth, unsigned int tileHeight,
				unsigned int columns, unsigned int rows);

			static Vec2 GetTopLeftOfGridCell(
				unsigned int tileWidth, unsigned int tileHeight,
				unsigned int columns, unsigned int rows);

			static Vec2 GetPositionFromTile(unsigned int gridPosition, unsigned int columns);

			static Vec2 SnapToGrid(Vec2 position,
				unsigned int tileWidth, unsigned int tileHeight,
				unsigned int columns, unsigned int rows);

			static void SetGridPositionType(unsigned int gridPosition, GridTypes type);
			static GridTypes GetGridPositionType(unsigned int gridPosition);

			static GridTypes GetGridTypeFromStep(unsigned int gridPosition, Facing step);
			static int GetGridPositionFromStep(unsigned int gridPosition, Facing step);
		};
	}
}