#include "Tree.h"
#include "../actors/Player.h"
#include "../scenes/AllScenes.h"
#include "core/Game.h"

namespace thelastforest
{
	namespace pickups
	{
		using namespace actors;
		using namespace scenes;
		using namespace novazero::core;

		Tree::Tree(int row)
			: Pickup(5000.f), m_Row(row)
		{
			float x = Game::s_Width - 142.f + 35.5f;
			float y = 4 + (row * 88);
			AddSprite("tree", Vec2(Game::s_Width, y), Vec2Int(71, 70), 0);

			m_GridPos = AllScenes::GetTileFromPosition(
				Vec2(GetX() - 142, GetY()), 142, 88, 9, 9);

			ClearPatrol();

			Configure(1000, false);
			AddPatrolPointLinearMovement(Vec2(x, y));
			EnableAI(true);

			ConfigureOnPatrolComplete(n2dMakeFunc(Tree::StartWait, this));

			auto cleanID = n2dAddUpdater(Tree::Update, this);
			m_CleanUpdaters.push_back(cleanID);

		}

		void Tree::StartWait()
		{
			Pickup::SetVisible(true);
			Pickup::Colorize("purple", "green");

			ClearPatrol();
			EnableAI(false);
			m_DelayTimer = new Timer(m_DelayTime, false, n2dMakeFunc(Tree::DestroySelf, this));

		}

		void Tree::Update()
		{
			Pickup::Update(GetPosition());

			if (n2dIsKeyDown(SDLK_SPACE))
			{
				if (Player::s_HoldingItem == GridTypes::Free)
				{
					if (Player::s_HighlightedGridPos == m_GridPos)
					{
						Player::PickupItem(GridTypes::Tree);
						DestroySelf();
					}
				}
			}
		}

		void Tree::DestroySelf()
		{
			AllScenes::SetTreeOnRow(m_Row, false);

			CleanUpdaters();
			Pickup::DestroySelf();
			SimpleWeakAI::DestroySelf();
			SetDeleted(true);
		}
	}
}