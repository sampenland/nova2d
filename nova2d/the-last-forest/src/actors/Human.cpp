#include "Human.h"
#include "physics/Collision.h"
#include "physics/Collider.h"
#include "../scenes/AllScenes.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace novazero::physics;
		using namespace scenes;
		using namespace placements;

		Human::Human(Vec2 position, Vec2Int size, unsigned char layer)
		{			
			AddSprite("human", position, size, layer);

			ConfigureCollider(GetSprite(), 0, "human");

			ConfigureAliveBounds(Rect(0, -90, Game::s_Width, Game::s_Height + 88));

			// Configure move speed
			Configure(1500, false);

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
					AddPatrolPointWithFunction(
						Vec2(nX, nY), GetLinearPatrolMove());

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

		void Human::HandleStepTo(unsigned int gridPos, GridTypes type)
		{
			Timer* chopDelay = nullptr;
			
			Placement* placement = AllScenes::GetPlacementAt(gridPos);

			if (!placement) return;

 			switch (type)
			{
			case GridTypes::Free:
				break;
			case GridTypes::PTree:
				break;
			case GridTypes::DeadPTree:
				break;
			case GridTypes::Tree:

				m_Waiting = true;
				chopDelay = new Timer(2000.f, false, ([=]() {

					m_Waiting = false;
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