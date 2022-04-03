#include "AllScenes.h"

namespace thelastforest
{
	namespace scenes
	{
		using namespace placements;

		Placement* AllScenes::s_Placements[81];
		bool AllScenes::s_HumanOnColumn[8];

		void AllScenes::NewGame()
		{
			// make everything free
			for (int i = 0; i < 81; i++)
				s_Placements[i] = nullptr;

			for (int i = 0; i < 8; i++)
				s_HumanOnColumn[i] = false;
		}

		bool AllScenes::HumanOnColumn(int col)
		{
			return s_HumanOnColumn[col];
		}

		void AllScenes::SetHumanOnColumn(int col, bool val)
		{
			s_HumanOnColumn[col] = val;
		}

		void AllScenes::SetPlacementAt(Placement* placement, unsigned int gridPosition)
		{
			if (gridPosition < 0 || gridPosition > 80) return;
			if (s_Placements[gridPosition])
				s_Placements[gridPosition]->DestroySelf();

			s_Placements[gridPosition] = placement;
		}

		Placement* AllScenes::GetPlacementAt(unsigned int gridPosition)
		{
			if (gridPosition < 0 || gridPosition > 80) return nullptr;
			return s_Placements[gridPosition];
		}

		int AllScenes::GetTileFromPosition(Vec2 position, 
			unsigned int tileWidth, unsigned int tileHeight,
			unsigned int columns, unsigned int rows)
		{
			int row = 0;
			int col = 0;

			if (position.x < 0 || position.y < 0 || position.x > Game::s_Width || position.y > Game::s_Height)
			{
				return -1;
			}

			col = (int)(position.x + 1) / tileWidth; // 1 and 4 are padding
			row = (int)(position.y + 4) / tileHeight;

			return col + (row * columns);
		}

		Vec2 AllScenes::GetTopLeftOfGridCell(
			unsigned int tileWidth, unsigned int tileHeight,
			unsigned int columns, unsigned int rows)
		{
			return Vec2((float)4 + tileWidth * columns, (float)1 + tileHeight * rows); // 1 and 4 are padding
		}

		Vec2 AllScenes::GetPositionFromTile(unsigned int gridPosition, unsigned int columns)
		{
			unsigned int col = gridPosition % columns;
			unsigned int row = gridPosition / columns;

			return Vec2((float)col * 142, (float)row * 88);

		}

		Vec2 AllScenes::SnapToGrid(Vec2 position,
			unsigned int tileWidth, unsigned int tileHeight,
			unsigned int columns, unsigned int rows)
		{
			int column = (int)(position.x + 1) / tileWidth; // 1 and 4 are padding
			int row = (int)(position.y + 4) / tileHeight;

			return Vec2((float)column * tileWidth + 1, (float)row * tileHeight + 4);
		}

		GridTypes AllScenes::GetGridTypeFromStep(unsigned int gridPosition, Facing step)
		{
			int gridPos = GetGridPositionFromStep(gridPosition, step);

			if (gridPos == -1)
			{
				return GridTypes::Blocked;
			}

			return GetGridPositionType(gridPos);
		}

		int AllScenes::GetGridPositionFromStep(unsigned int gridPosition, Facing step)
		{
			int stepToPos = gridPosition;
			switch (step)
			{
			case Facing::Up:
				stepToPos -= 9;
				break;
			case Facing::Down:
				stepToPos += 9;
				break;
			case Facing::Left:
				stepToPos -= 1;
				break;
			case Facing::Right:
				stepToPos += 1;
				break;
			default:
				stepToPos += 9;
				break;
			}

			if (stepToPos < 0)
			{
				return -1;
			}
			else if (stepToPos > 80)
			{
				return 99;
			}

			return stepToPos;
		}

		GridTypes AllScenes::GetGridPositionType(unsigned int gridPosition)
		{
			if (gridPosition < 0 || gridPosition > 80) return GridTypes::Blocked;
			if (!s_Placements[gridPosition]) return GridTypes::Free;
			return s_Placements[gridPosition]->GetType();
		}
	}
}