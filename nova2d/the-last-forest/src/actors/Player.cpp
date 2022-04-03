#include "Player.h"
#include "../scenes/AllScenes.h"
#include "../placements/Placement.h"
#include "../GameDesigner.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace scenes;
		using namespace placements;

		unsigned int Player::s_HighlightedGridPos = 0;
		GridTypes Player::s_HoldingItem = GridTypes::Free;
		bool Player::s_ReadyToPlace = false;

		Player::Player(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer)
			: UDRLController(assetName, position, size, layer)
		{
			SetPosition(position);

			ConfigureMove(5.f);
			ConfigureMoveBounds(Rect(142, 0, Game::s_Width - (2 * 142) - size.x, Game::s_Height - 2 * 88));

			m_Highlight = new Image("highlight", Vec2(0, 0), Vec2Int(142, 88), 11);
			Highlight();

			s_HoldingItem = GridTypes::Free;
			m_HoldingItem = new Image("highlight", Vec2(0, 0), Vec2Int(71, 70), 10);
			m_HoldingItem->SetVisible(false);

		}

		void Player::Update()
		{
			Highlight();
			HoldItem();
			PlaceItem();
		}

		void Player::Highlight()
		{
			if (n2dIsKeyDown(SDLK_w))
				m_Hightlighter = HighlighterPosition::Up;

			if (n2dIsKeyDown(SDLK_s))
				m_Hightlighter = HighlighterPosition::Down;

			if (n2dIsKeyDown(SDLK_d))
				m_Hightlighter = HighlighterPosition::Right;

			if (n2dIsKeyDown(SDLK_a))
				m_Hightlighter = HighlighterPosition::Left;

			Vec2 highlightPos;
			highlightPos.x = 0;
			highlightPos.y = 0;

			Vec2 pos = GetCenter();
			switch (m_Hightlighter)
			{
			case HighlighterPosition::Up:
				highlightPos = AllScenes::SnapToGrid(
					Vec2(pos.x, pos.y - 88), 142, 88, 9, 9);
				break;
			case HighlighterPosition::Down:
				highlightPos = AllScenes::SnapToGrid(
					Vec2(pos.x, pos.y + 88), 142, 88, 9, 9);
				break;
			case HighlighterPosition::Right:
				highlightPos = AllScenes::SnapToGrid(
					Vec2(pos.x + 142, pos.y), 142, 88, 9, 9);
				break;
			case HighlighterPosition::Left:
				highlightPos = AllScenes::SnapToGrid(
					Vec2(pos.x - 142, pos.y), 142, 88, 9, 9);
				break;
			}

			s_HighlightedGridPos = AllScenes::GetTileFromPosition(
				highlightPos, 142, 88, 9, 9);

			m_Highlight->SetPosition(highlightPos);
			
			if(m_HoldingItem) 
				m_HoldingItem->SetPosition(Vec2(highlightPos.x + 35.5f, highlightPos.y));
		}

		void Player::HoldItem()
		{
			if (s_HoldingItem != GridTypes::Free)
			{
				m_HoldingItem->SetVisible(true);
				m_HoldingItem->SetEnabled(true);

				switch (s_HoldingItem)
				{
				case GridTypes::Water:
					m_HoldingItem->SwapTexture("water");
					break;
				case GridTypes::Sun:
					m_HoldingItem->SwapTexture("sun");
					break;
				case GridTypes::Tree:
					m_HoldingItem->SwapTexture("tree");
					break;
				}

			}
			else
			{
				m_HoldingItem->SetVisible(false);
				m_HoldingItem->SetEnabled(false);
			}
		}

		void Player::PlaceItem()
		{
			if (s_HoldingItem != GridTypes::Free && s_ReadyToPlace)
			{
				if (n2dIsKeyDown(SDLK_SPACE))
				{
					Placement* placement = nullptr;

					switch (s_HoldingItem)
					{
					case GridTypes::Tree:

						if (AllScenes::GetGridPositionType(s_HighlightedGridPos) == GridTypes::Free)
						{
							placement = new Placement(GridTypes::Tree,
								2, s_HighlightedGridPos, Vec2Int(71, 70), 2);

							AllScenes::SetPlacementAt(placement, s_HighlightedGridPos);
							s_HoldingItem = GridTypes::Free;
						}

						break;

					case GridTypes::Sun:

						placement = AllScenes::GetPlacementAt(s_HighlightedGridPos);
						if (placement)
						{
							placement->AddResource(true, g_AddSunLightVal);
						}

						s_HoldingItem = GridTypes::Free;

						break;

					case GridTypes::Water:
						
						placement = AllScenes::GetPlacementAt(s_HighlightedGridPos);
						if (placement)
						{
							placement->AddResource(false, g_AddWaterVal);
						}

						s_HoldingItem = GridTypes::Free;

						break;
					}
				}
			}
		}

		void Player::PickupItem(GridTypes type)
		{
			s_ReadyToPlace = false;
			s_HoldingItem = type;

			Timer* readyToPlace = new Timer(1000, false, [=]() {
				s_ReadyToPlace = true;
			});
		}
	}
}