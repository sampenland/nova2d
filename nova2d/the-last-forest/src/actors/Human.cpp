#include "Human.h"
#include "physics/Collision.h"
#include "physics/Collider.h"
#include "../scenes/AllScenes.h"
#include "../GameDesigner.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace novazero::physics;
		using namespace scenes;
		using namespace placements;

		Human::Human(Vec2 position, Vec2Int size, unsigned char layer)
		{			
			AddSprite("human", position, size, layer, true);

			GetSprite()->AddAnimation("walk", 0, 2, 8, true, nullptr);
			GetSprite()->AddAnimation("chop", 2, 2, 5, true, nullptr);
			GetSprite()->AddAnimation("powerup", 4, 2, 2, true, nullptr);

			GetSprite()->ChangeAnimation("walk");
			GetSprite()->StartAnimation();

			ConfigureCollider(GetSprite(), 0, "human");

			// Configure move speed
			Configure(g_HumanMoveSpeed, false);

			// Program walk downwards
			AddPatrolPointWithFunction(Vec2(position.x, position.y + m_Step), GetLinearPatrolMove());

			// Start walk
			EnableAI(true);

			m_ThinkTimer = new Timer(m_ThinkSpeed, true, n2dMakeFunc(Human::ThinkNextMove, this));

		}

		void Human::ThinkNextMove()
		{
			if (m_Waiting) return;

			ClearPatrol();
			
			float nX = GetX();
			float nY = GetY();

			int gridPosition = AllScenes::GetTileFromPosition(
				Vec2(nX, nY), 142, 88, 9, 9);

			if (m_StepDown)
				nY += m_Step;
			else
				nY -= m_Step;

			if (gridPosition >= 0)
			{
				GridTypes stepToType;
				int steppingTo;
				if (m_StepDown)
				{
					stepToType = AllScenes::GetGridTypeFromStep(gridPosition, Facing::Down);
					steppingTo = AllScenes::GetGridPositionFromStep(gridPosition, Facing::Down);
				}
				else
				{
					stepToType = AllScenes::GetGridTypeFromStep(gridPosition, Facing::Up);
					steppingTo = AllScenes::GetGridPositionFromStep(gridPosition, Facing::Up);
				}

				if (stepToType != GridTypes::Free && steppingTo >= 0)
				{
					HandleStepTo(steppingTo, stepToType);
					return;
				}
				else if (steppingTo < 0)
				{
					PowerUp();

					return;
				}
			}
			else
			{
				AddPatrolPointWithFunction(
					Vec2(nX, nY), GetLinearPatrolMove());
				
				return;
			}

			AddPatrolPointWithFunction(
				Vec2(nX, nY), GetLinearPatrolMove());
		}

		void Human::PowerUp()
		{
			m_MaxAttacks++;
			m_Attacks = m_MaxAttacks;

			if (!GetSprite())
			{
				LOG(LVL_NFE, "No Sprite on human, power up.");
				return;
			}

			switch (m_MaxAttacks)
			{
			case 1:
				GetSprite()->ClearTint();
			case 2:
				GetSprite()->Tint("human-yellow");
				break;
			case 3:
				GetSprite()->Tint("human-blue");
				break;
			default:
				GetSprite()->Tint("human-red");
				break;
			}

			m_Waiting = true;
			GetSprite()->ChangeAnimation("powerup");

			auto f = new auto ([=]() {
				GetSprite()->ChangeAnimation("walk");
				m_Waiting = false;
			});

			Timer* t = new Timer(2000.f, false, *f);

			m_StepDown = true;
		}

		void Human::HandleStepTo(unsigned int gridPos, GridTypes type)
		{
			if (m_Attacks <= 0)
			{
				m_StepDown = false;
				return;
			}

			Timer* chopDelay = nullptr;
			
			Placement* placement = AllScenes::GetPlacementAt(gridPos);

			if (!placement) return;

 			switch (type)
			{
			case GridTypes::Free:
				break;
			case GridTypes::PTree:

				GetSprite()->ChangeAnimation("chop");
				m_Waiting = true;
				chopDelay = new Timer(4000.f, false, ([=]() {

					m_Waiting = false;
					m_Attacks -= 1;
					GetSprite()->ChangeAnimation("walk");
					bool placementDestroyed = placement->UseDelay(m_AttackStrength);

					if (placementDestroyed)
					{
						m_StepDown = false;
					}

				}));

				break;
			case GridTypes::DeadPTree:
				break;
			case GridTypes::Tree:

				m_Waiting = true;
				GetSprite()->ChangeAnimation("chop");
				chopDelay = new Timer(2000.f, false, ([=]() {

					m_Waiting = false;
					m_Attacks -= 1;
					GetSprite()->ChangeAnimation("walk");
					bool placementDestroyed = placement->UseDelay(m_AttackStrength);

					if (placementDestroyed)
					{
						m_StepDown = false;
					}

				}));

				break;
			case GridTypes::Grass:
				break;
			case GridTypes::Water:
				break;
			case GridTypes::Sun:
				break;
			case GridTypes::Blocked:
				break;
			}
		}

		void Human::OnCollision(Collision* collision)
		{
			
		}

		void Human::DestroySelf()
		{
			CleanUpdaters();
			SimpleWeakAI::DestroySelf();
		}
	}
}