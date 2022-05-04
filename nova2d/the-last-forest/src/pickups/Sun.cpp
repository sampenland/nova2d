#include "Sun.h"
#include "../actors/Player.h"
#include "../scenes/AllScenes.h"

namespace thelastforest
{
	namespace pickups
	{
		using namespace actors;
		using namespace scenes;

		Sun::Sun(int row)
			: Pickup(5000.f), m_Row(row)
		{
			float x = 35.5f;
			float y = 4 + (row * 88);
			AddSprite("sun", Vec2(-142, y), Vec2Int(71, 70), 0);

			m_GridPos = AllScenes::GetTileFromPosition(
				Vec2(GetX() + 142 + 35.5f, GetY()), 142, 88, 9, 9);

			ClearPatrol();

			Configure(1000, false);
			AddPatrolPointLinearMovement(Vec2(x, y));
			EnableAI(true);

			ConfigureOnPatrolComplete(n2dMakeFunc(Sun::StartWait, this));

			auto cleanID = n2dAddUpdater(Sun::Update, this);
			m_CleanUpdaters.push_back(cleanID);

		}

		void Sun::StartWait()
		{
			Pickup::SetVisible(true);

			ClearPatrol();
			EnableAI(false);
			m_DelayTimer = new Timer(m_DelayTime, false, n2dMakeFunc(Sun::DestroySelf, this));
		}

		void Sun::Update()
		{
			Pickup::Update(GetPosition());

			if (n2dIsKeyDown(SDLK_SPACE))
			{
				if (Player::s_HoldingItem == GridTypes::Free)
				{
					if (Player::s_HighlightedGridPos == m_GridPos)
					{
						Player::PickupItem(GridTypes::Sun);
						DestroySelf();
					}
				}
			}
		}

		void Sun::DestroySelf()
		{
			AllScenes::SetResourceOnRow(m_Row, false);

			CleanUpdaters();

			Pickup::DestroySelf();
			SimpleWeakAI::DestroySelf();
			SetDeleted(true);
		}
	}
}