#include "SimpleWeakAI.h"
#include "../logging/logging.h"
#include "../core/Game.h"

namespace novazero
{
	namespace ai
	{
		SimpleWeakAI::SimpleWeakAI()
			: Collider(0), Deleteable("simpleWeakAI"), TimeEffected()
		{
			Collider::m_ID = n2dGameGetID();
			TimeEffected::m_ID = n2dGameGetID();

			auto cleanID = n2dAddUpdater(SimpleWeakAI::Update, this);
			m_CleanUpdaters.push_back(cleanID);
		}

		void SimpleWeakAI::EnableAI(bool isEnabled)
		{
			if (isEnabled)
				m_PatrolIndex = 0;
			else
				m_PatrolIndex = -1;
		}

		void SimpleWeakAI::ResetAI()
		{
			m_PatrolIndex = m_LoopStartIndex;
		}

		void SimpleWeakAI::AddSprite(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer, bool makeCopy)
		{
			SetPosition(position);
			Positional::LinkPositionalDrawable(new Sprite(assetName, position, size, layer, makeCopy));
			m_DeleteName = assetName;
		}

		void SimpleWeakAI::AddPatrolPointWithFunction(Vec2* point, std::function<void()> func)
		{
			m_PatrolPoints.push_back(point);
			m_MoveFunctions.push_back(func);
		}

		void SimpleWeakAI::AddPatrolPointWithFunction(Vec2 point, std::function<void()> func)
		{
			Vec2* v = new Vec2(point.x, point.y);
			m_PatrolPoints.push_back(v);
			m_MoveFunctions.push_back(func);
		}

		/* Clears all patrol points */
		void SimpleWeakAI::ClearPatrol()
		{
			if((int)m_PatrolPoints.size() > 0)
				m_PatrolPoints.clear();
			
			if ((int)m_MoveFunctions.size() > 0)
				m_MoveFunctions.clear();

			m_PatrolIndex = 0;
		}

		void SimpleWeakAI::RemovePatrolPointWithFunction(Vec2* point)
		{
			int idx = -1;
			for (size_t i = 0; i < m_PatrolPoints.size(); i++)
			{
				if (m_PatrolPoints[i] == point)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1) return;

			m_PatrolPoints.erase(m_PatrolPoints.begin() + idx);
			m_MoveFunctions.erase(m_MoveFunctions.begin() + idx);
		}

		void SimpleWeakAI::SetAllPatrol(std::vector<Vec2*> points, std::vector<std::function<void()>> funcs)
		{
			LOG(LVL_WARNING, "Function Set All Patrol not implemented.");
			return;

			if (points.size() != funcs.size())
			{
				LOG(LVL_WARNING, "Weak AI cannot set patrol points.");
				return;
			}

			m_PatrolPoints.clear();
			m_MoveFunctions.clear();

			m_PatrolPoints = points;
			m_MoveFunctions = funcs;

			EnableAI(true);

		}

		void SimpleWeakAI::SetAllPatrolPoints(std::vector<Vec2*> points)
		{
			ClearPatrol();
			m_PatrolPoints = points;
			EnableAI(true);
		}

		void SimpleWeakAI::Update()
		{
			if (!m_Alive) return;

			Sprite* sprite = GetSprite();

			if (sprite)
			{
				sprite->SetPosition(GetPosition());
			}

			if (m_DelayMS > 0)
			{
				m_DelayMS = (float)(m_DelayMS - n2dDeltaTime);
				return;
			}

			if (!m_UsingPatrolSpeedOverride)
			{
				m_DelayMS = (float)m_DelayMaxMS * (float)(1 / (n2dTimeScale * GetTimeInfluence()));
			}
			else
			{
				m_DelayMS = (*m_PatrolSpeedRef) * (float)(1 / (n2dTimeScale * GetTimeInfluence()));
			}
			
			if ((m_MemoryMovement.x != 0 || m_MemoryMovement.y != 0) && m_PatrolIndex == -1 && m_ContinueAfterPatrolComplete)
			{
				SetPosition(Vec2(GetX() + m_MemoryMovement.x, GetY() + m_MemoryMovement.y));
				return;
			}

			if (m_PatrolIndex == -1 && (int)m_PatrolPoints.size() > 0)
			{
				if(f_OnPatrolComplete)
					f_OnPatrolComplete();
			}

			if (OutOfBounds(GetDrawable()))
			{
				DestroySelf();
				return;
			}

			if (m_LoopMoving && m_PatrolIndex == -1)
			{
				m_PatrolIndex = m_LoopStartIndex;
				return;
			}

			if (m_PatrolIndex == -1) 
				return;

			if (m_PatrolIndex >= (int)m_MoveFunctions.size()) return;

			m_MoveFunctions[m_PatrolIndex]();
		}

		// Using Linear moving
		void SimpleWeakAI::LinearPatrolMove()
		{
			if (m_PatrolIndex == -1)
			{
				if (m_LoopMoving) 
				{
					m_PatrolIndex = 0;
				}
			}

			if (m_PatrolIndex < (int)m_PatrolPoints.size())
			{
				//                   end vector (target)       -     currentPosition
				Vec2 currentPos = GetPosition();
				Vec2 targetPos = Vec2((*(m_PatrolPoints.at(m_PatrolIndex))).x, (*(m_PatrolPoints.at(m_PatrolIndex))).y);
				Vec2 dirNormVector = targetPos;

				dirNormVector.subtract(currentPos).normalize();

				if (m_UsingPatrolSpeedOverride)
				{
					dirNormVector.scale(*m_PatrolSpeedRef * n2dTimeScale * GetTimeInfluence());
				}
				else
				{
					dirNormVector.scale(2.f * n2dTimeScale * GetTimeInfluence());
				}

				Vec2 newPos = currentPos.add(dirNormVector);

				const float tolerance = 3.f;
				bool reachedTarget = Vec2::Distance(targetPos, newPos) <= tolerance;

				if (reachedTarget)
				{
					m_PatrolIndex++;
					if (m_PatrolIndex >= (int)m_PatrolPoints.size())
					{
						m_PatrolIndex = -1;
						return;
					}
				}
				else
				{
					m_MemoryMovement = dirNormVector;
					SetPosition(newPos);
				}
			}
		}

		void SimpleWeakAI::DestroySelf()
		{
			CleanUpdaters();

			SceneManager::s_CollisionManager->RemoveCollider(this);

			if (GetSprite())
				GetSprite()->DestroySelf();

			SetDeleted(true);
		}
	}
}