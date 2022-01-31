#include "SimpleWeakAI.h"
#include "../logging/logging.h"

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

		void SimpleWeakAI::AddSprite(std::string assetName, Vec2 position, Vec2Int size, char layer)
		{
			m_Sprite = new Sprite(assetName, position, size, layer);
			m_DeleteName = assetName;
		}

		void SimpleWeakAI::AddPatrolPointWithFunction(Vec2 point, f_MovePtrFunction func)
		{
			m_PatrolPoints.push_back(point);
			m_MoveFunctions.push_back(func);
		}

		void SimpleWeakAI::ClearPatrol()
		{
			if((int)m_PatrolPoints.size() > 0)
				m_PatrolPoints.clear();
			
			if((int)m_MoveFunctions.size() > 0)
				m_MoveFunctions.clear(); // TODO: crashes here sometimes
		}

		void SimpleWeakAI::RemovePatrolPointWithFunction(Vec2 point)
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

		void SimpleWeakAI::SetAllPatrol(std::vector<Vec2> points, std::vector<f_MovePtrFunction> funcs)
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

		void SimpleWeakAI::Update()
		{
			if (!m_Alive) return;

			if (m_DelayMS > 0)
			{
				auto d = n2dDeltaTime();
				m_DelayMS = (float)(m_DelayMS - d);
				return;
			}

			m_DelayMS = (float)m_DelayMaxMS * (float)(1 / (n2dTimeScale * GetTimeInfluence()));

			if (m_PatrolIndex == -1 && (int)m_PatrolPoints.size() > 0)
			{
				if(f_OnPatrolComplete)
					f_OnPatrolComplete();
			}

			if (OutOfBounds(m_Sprite))
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

		// Using Linear moving presumes your patrol points distances
		// are divisble by 2
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
				float currentX = GetX();
				float currentY = GetY();
				Vec2 endVector = m_PatrolPoints.at(m_PatrolIndex);

				float newX = currentX > endVector.x ? currentX - 2 : currentX + 2;
				float newY = currentY > endVector.y ? currentY - 2 : currentY + 2;

				if (currentX == endVector.x) newX = endVector.x;
				if (currentY == endVector.y) newY = endVector.y;

				SetPosition(newX, newY);

				if (newX == endVector.x && newY == endVector.y)
				{
					m_PatrolIndex++;
					if (m_PatrolIndex >= (int)m_PatrolPoints.size())
					{
						m_PatrolIndex = -1;
						return;
					}
				}

			}
		}

		void SimpleWeakAI::DestroySelf()
		{
			CleanUpdaters();

			if (m_Sprite)
				m_Sprite->DestroySelf();

			m_DeleteNow = 1;
		}
	}
}