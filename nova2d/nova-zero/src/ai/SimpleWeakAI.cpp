#include "SimpleWeakAI.h"

namespace novazero
{
	namespace ai
	{
		SimpleWeakAI::SimpleWeakAI()
		{
			Game::AddUpdater(std::bind(&SimpleWeakAI::Update, this));
		}

		SimpleWeakAI::~SimpleWeakAI()
		{
			Game::RemoveUpdater(std::bind(&SimpleWeakAI::Update, this));

			if (m_Sprite)
				delete m_Sprite;
		}

		void SimpleWeakAI::Configure(float moveSpeed, bool loop)
		{
			m_MoveSpeed = moveSpeed;
			m_LoopMoving = loop;
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
			m_PatrolIndex = 0;
		}

		void SimpleWeakAI::AddSprite(std::string assetName, Vec2Int position, Vec2Int size, char layer)
		{
			m_Sprite = new Sprite(assetName, position, size, layer);
		}

		void SimpleWeakAI::AddPatrolPointWithFunction(Vec2Int point, f_MovePtrFunction func)
		{
			m_PatrolPoints.push_back(point);
			m_MoveFunctions.push_back(func);
		}

		void SimpleWeakAI::RemovePatrolPointWithFunction(Vec2Int point)
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

		void SimpleWeakAI::SetAllPatrol(std::vector<Vec2Int> points, std::vector<f_MovePtrFunction> funcs)
		{
			if (points.size() != funcs.size())
			{
				LOG("Weak AI cannot set patrol points.");
				return;
			}

			m_PatrolPoints = points;
			m_MoveFunctions = funcs;

		}

		void SimpleWeakAI::Update()
		{
			OutOfBounds(m_Sprite);

			if (m_LoopMoving && m_PatrolIndex == -1)
			{
				m_PatrolIndex = 0;
				return;
			}

			if (m_PatrolIndex == -1) 
				return;

			m_MoveFunctions[m_PatrolIndex]();
		}

		void SimpleWeakAI::LinearPatrolMove()
		{
			if (m_PatrolIndex == -1)
			{
				if (m_LoopMoving) 
				{
					m_PatrolIndex = 0;
				}
			}

			if (m_PatrolIndex < m_PatrolPoints.size())
			{
				int currentX = GetX();
				int currentY = GetY();
				Vec2Int endVector = m_PatrolPoints.at(m_PatrolIndex);

				int newX = currentX > endVector.x ? currentX - m_MoveSpeed : currentX + m_MoveSpeed;
				int newY = currentY > endVector.y ? currentY - m_MoveSpeed : currentY + m_MoveSpeed;

				SetPosition(newX, newY);

				if (newX == endVector.x && newY == endVector.y)
				{
					m_PatrolIndex++;
					if (m_PatrolIndex >= m_PatrolPoints.size())
					{
						m_PatrolIndex = -1;
						return;
					}
				}

			}
		}
	}
}