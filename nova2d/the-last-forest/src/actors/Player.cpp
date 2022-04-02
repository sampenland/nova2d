#include "Player.h"
#include "../scenes/AllScenes.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace scenes;

		Player::Player(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer)
			: UDRLController(assetName, position, size, layer)
		{
			ConfigureMove(5.f);
			ConfigureMoveBounds(Rect(142, 0, Game::s_Width - (2 * 142) - size.x, Game::s_Height - 2 * 88));

			m_Highlight = new Image("highlight", Vec2(0, 0), Vec2Int(142, 88), 11);
			Highlight();

		}

		void Player::Update()
		{
			Highlight();
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

			Vec2 highlightPos = Vec2(100, 100);

			switch (m_Hightlighter)
			{
			case HighlighterPosition::Up:
				highlightPos = AllScenes::SnapToGrid(
					Vec2(GetX(), GetY() - 88), 142, 88, 9, 9);
				break;
			case HighlighterPosition::Down:
				highlightPos = AllScenes::SnapToGrid(
					Vec2(GetX(), GetY() + 88), 142, 88, 9, 9);
				break;
			case HighlighterPosition::Right:
				highlightPos = AllScenes::SnapToGrid(
					Vec2(GetX() + 142, GetY()), 142, 88, 9, 9);
				break;
			case HighlighterPosition::Left:
				highlightPos = AllScenes::SnapToGrid(
					Vec2(GetX() - 142, GetY()), 142, 88, 9, 9);
				break;
			}

			m_Highlight->SetPosition(highlightPos);
		}
	}
}