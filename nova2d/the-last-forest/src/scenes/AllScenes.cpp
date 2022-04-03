#include "AllScenes.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace placements;

		Trees* AllScenes::s_Trees[7];
		GridTypes AllScenes::s_Grid[81];
		Placement* AllScenes::s_Placements[81];

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
			float column = (int)(position.x + 1) / tileWidth; // 1 and 4 are padding
			float row = (int)(position.y + 4) / tileHeight;
		
			return column + (row * columns);
		}

		Vec2 AllScenes::GetTopLeftOfGridCell(
			unsigned int tileWidth, unsigned int tileHeight,
			unsigned int columns, unsigned int rows)
		{
			return Vec2(4 + tileWidth * columns, 1 + tileHeight * rows); // 1 and 4 are padding
		}

		Vec2 AllScenes::GetPositionFromTile(unsigned int gridPosition, unsigned int columns)
		{
			unsigned int col = gridPosition % columns;
			unsigned int row = gridPosition / columns;

			return Vec2(col * 142, row * 88);

		}

		Vec2 AllScenes::SnapToGrid(Vec2 position,
			unsigned int tileWidth, unsigned int tileHeight,
			unsigned int columns, unsigned int rows)
		{
			int column = (int)(position.x + 1) / tileWidth; // 1 and 4 are padding
			int row = (int)(position.y + 4) / tileHeight;

			return Vec2(column * tileWidth + 1, row * tileHeight + 4);
		}

		void AllScenes::SetGridPosition(unsigned int gridPosition, GridTypes type)
		{
			if (s_Grid[gridPosition] == GridTypes::Free)
			{
				s_Grid[gridPosition] = type;
			}
		}

		GridTypes AllScenes::GetGridPositionType(unsigned int gridPosition)
		{
			return s_Grid[gridPosition];
		}

	}
}