#include "Human.h"
#include "physics/Collision.h"
#include "physics/Collider.h"
#include "Trees.h"

namespace thelastforest
{
	namespace actors
	{
		using namespace novazero::physics;

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
			ClearPatrol();
			
			float nX = GetX();
			float nY = GetY();
			
			if (m_StepDown)
				nY += m_Step;
			else
				nY -= m_Step;

			AddPatrolPointWithFunction(
				Vec2(nX, nY), GetLinearPatrolMove()
			);
		}

		void Human::HandleCollision(Collider* other)
		{
			m_HandlingCollision = true;

			if (other->m_ColliderName == "ptree")
			{
				m_StepDown = false;
				m_ThinkTimer->ResetAndEnable(1000.f);
				
				auto treeChop = new auto ([=]() {
					((Trees*)other)->DestroySelf();
				});
				Timer* t = new Timer(600.f, false, *treeChop);
			}
		}

		void Human::OnCollision(Collision* collision)
		{
			if (m_HandlingCollision) return;

			// Pause thinking
			m_ThinkTimer->SetEnabled(false);

			if (collision->m_ColliderA->m_ColliderName == "human")
			{
				HandleCollision(collision->m_ColliderB);
			}
			else if (collision->m_ColliderB->m_ColliderName == "human")
			{
				HandleCollision(collision->m_ColliderA);
			}

		}

		void Human::DestroySelf()
		{
			SetDeleted(true);
		}
	}
}