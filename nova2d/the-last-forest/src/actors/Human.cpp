#include "Human.h"
#include "../scenes/AllScenes.h"
#include "../GameDesigner.h"
#include "utils/timeline/events/TimelineExecuteEvent.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace novazero::physics;
		using namespace scenes;
		using namespace placements;
		using namespace novazero::utils::events;

		Human::Human(Vec2 position, unsigned int column, unsigned int startAttacks, Vec2Int size, unsigned char layer)
		{			
			m_Column = column;

			m_MaxAttacks = startAttacks;
			m_Attacks = startAttacks;

			AddSprite("human", position, size, layer, true);

			switch (m_MaxAttacks)
			{
			case 1:
				GetSprite()->ClearTint();
				break;
			case 2:
				GetSprite()->Tint("human-yellow");
				break;
			case 3:
				GetSprite()->Tint("human-blue");
				break;
			case 4:
				GetSprite()->Tint("human-red");
				break;
			}

			GetSprite()->AddAnimation("walk", 0, 2, 8, true, nullptr);
			GetSprite()->AddAnimation("chop", 2, 2, 5, true, nullptr);
			GetSprite()->AddAnimation("powerup", 4, 2, 2, true, nullptr);
			GetSprite()->AddAnimation("dead", 6, 1, 5, false, nullptr);

			GetSprite()->ChangeAnimation("walk");
			GetSprite()->StartAnimation();

			// Configure move speed
			Configure(g_HumanMoveSpeed, false);

			// Program walk downwards
			AddPatrolPointLinearMovement(Vec2(position.x, position.y + m_Step));

			// Start walk
			EnableAI(true);

			m_ThinkTimer = new Timer(m_ThinkSpeed, true, n2dMakeFunc(Human::ThinkNextMove, this));

		}

		void Human::ThinkNextMove()
		{
			if (m_Waiting || !IsEnabled()) return;

			ClearPatrol();
			
			float nX = GetX();
			float nY = GetY();

			int gridPosition = AllScenes::GetTileFromPosition(
				Vec2(nX, nY), 142, 88, 9, 9);

			GridTypes currentGridType = AllScenes::GetGridPositionType(gridPosition);

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

				if (!m_StepDown && currentGridType == GridTypes::Tree)
				{
					if (m_Attacks <= 0) 
					{
						Die();
						return;
					}
				}
				else if (stepToType != GridTypes::Free && steppingTo >= 0)
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
				AddPatrolPointLinearMovement(
					Vec2(nX, nY));
				
				return;
			}

			AddPatrolPointLinearMovement(
				Vec2(nX, nY));
		}

		void Human::PowerUp()
		{
			if (!GetSprite())
			{
				LOG(LVL_NFE, "No Sprite on human, power up.", __FILE__, __LINE__);
				return;
			}

			if (m_MaxAttacks >= 4)
			{
				m_StepDown = true;
				GetSprite()->ChangeAnimation("walk");
				return;
			}

			m_MaxAttacks++;
			m_Attacks = m_MaxAttacks;
			
			n2dAudioPlayOnce(false, "powerUp");

			switch (m_MaxAttacks)
			{
			case 1:
				GetSprite()->ClearTint();
				break;
			case 2:
				GetSprite()->Tint("human-yellow");
				break;
			case 3:
				GetSprite()->Tint("human-blue");
				break;
			case 4:
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

		void Human::Die()
		{
			if (GetSprite())
			{
				GetSprite()->StopAnimation();
				GetSprite()->ChangeAnimation("dead");
				SetEnabled(false);

				n2dAudioPlayOnce(false, "humanDie");

				Timer* t = new Timer(5000, false, n2dMakeFunc(Human::DestroySelf, this));
			}
		}

		void Human::HandleStepTo(unsigned int gridPos, GridTypes type)
		{
			if (m_MaxAttacks >= 4 && m_Attacks <= 0)
			{
				Die();
				return;
			}

			if (m_Attacks <= 0)
			{
				m_StepDown = false;

				float nX = GetX();
				float nY = GetY() - m_Step;

				AddPatrolPointLinearMovement(Vec2(nX, nY));

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
						n2dAudioPlayOnce(false, "deadTree");
					}

				}));

				break;
			case GridTypes::DeadPTree:
				break;
			case GridTypes::Tree:

				m_Waiting = true;
				GetSprite()->ChangeAnimation("chop");
				n2dAudioPlayOnce(false, "chop");
				chopDelay = new Timer(2000.f, false, ([=]() {

					m_Waiting = false;
					m_Attacks -= 1;
					GetSprite()->ChangeAnimation("walk");
					bool placementDestroyed = placement->UseDelay(m_AttackStrength);
					if (placementDestroyed)
					{
						if (m_Attacks <= 0)
						{
							m_StepDown = false;
						}
						else
						{
							m_StepDown = true;
						}
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

		void Human::DestroySelf()
		{
			AllScenes::SetHumanOnColumn(m_Column, false);
			CleanUpdaters();
			SimpleWeakAI::DestroySelf();
		}
	}
}