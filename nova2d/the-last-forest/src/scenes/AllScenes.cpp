#include "../scenes/AllScenes.h"

namespace thelastforest
{
	namespace scenes
	{
		Trees* AllScenes::s_Trees[7];
		GridTypes AllScenes::s_Grid[81];

		void AllScenes::NewGame()
		{
			// make everything free
			for (int i = 0; i < 81; i++)
				s_Grid[i] = GridTypes::Free;

			// bottom row are trees
			for (int i = 79; i > 72; i--)
				s_Grid[i] = GridTypes::PTree;
		}

		unsigned int AllScenes::GetTileFromPosition(Vec2 position, 
			unsigned int tileWidth, unsigned int tileHeight,
			unsigned int columns, unsigned int rows)
		{
			float column = (position.x + 1) / tileWidth; // 1 and 4 are padding
			float row = (position.y + 4) / tileHeight;

			return row * columns - (columns - column);
		}

		Vec2 AllScenes::GetTopLeftOfGridCell(
			unsigned int tileWidth, unsigned int tileHeight,
			unsigned int columns, unsigned int rows)
		{
			return Vec2(4 + tileWidth * columns, 1 + tileHeight * rows); // 1 and 4 are padding
		}

		Vec2 AllScenes::SnapToGrid(Vec2 position,
			unsigned int tileWidth, unsigned int tileHeight,
			unsigned int columns, unsigned int rows)
		{
			int column = (int)(position.x + 1) / tileWidth; // 1 and 4 are padding
			int row = (int)(position.y + 4) / tileHeight;

			return Vec2(column * tileWidth + 1, row * tileHeight + 4);
		}

	}
}