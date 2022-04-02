#pragma once
#include "../actors/Trees.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace actors;

		enum class GridTypes
		{
			Free,
			PTree, // persistent tree
			DeadPTree, // dead persistent tree
			Tree,
			Grass,
			Water,
			Sun

		};

		class AllScenes
		{
		public:
			static Trees* s_Trees[7];
			static GridTypes s_Grid[81];

			static void NewGame();

			static unsigned int GetTileFromPosition(Vec2 position,
				unsigned int tileWidth, unsigned int tileHeight,
				unsigned int columns, unsigned int rows);

			static Vec2 GetTopLeftOfGridCell(
				unsigned int tileWidth, unsigned int tileHeight,
				unsigned int columns, unsigned int rows);

			static Vec2 SnapToGrid(Vec2 position,
				unsigned int tileWidth, unsigned int tileHeight,
				unsigned int columns, unsigned int rows);
		};
	}
}