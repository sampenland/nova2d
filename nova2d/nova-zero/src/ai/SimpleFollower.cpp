#include "SimpleFollower.h"
#include "../core/Game.h"
#include "../physics/PhySprite.h"

namespace novazero
{
	namespace ai
	{
		using namespace core;
		using namespace maths;
		using namespace graphics;

		SimpleFollower::SimpleFollower(Positional* target, const float moveUpdateDelayMS)
			: m_MoveSpeed(2)
		{
			m_Target = target;
			m_UpdateDirectionDelay = moveUpdateDelayMS;

			m_AliveBounds = Rect(0.f, 0.f, (float)Game::s_Width, (float)Game::s_Height);
			m_DelayTime = m_UpdateDirectionDelay;

			auto id = n2dAddUpdater(SimpleFollower::UpdateFollower, this);
			Deleteable::m_CleanUpdaters.push_back(id);
		}

		void SimpleFollower::ConfigureInRange(float distanceToBeInRange)
		{
			m_InRange = distanceToBeInRange;
		}

		void SimpleFollower::AddSprite(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer)
		{
			m_Sprite = new Sprite(assetName, position, size, layer);
		}

		void SimpleFollower::AddPhySprite(const std::string& assetName, Vec2 position, 
			Vec2 size, unsigned char layer, Vec2Int displaySize, const std::string& colliderName)
		{
			m_PhySprite = new PhySprite(assetName, position, size, layer, displaySize, colliderName);
		}

		void SimpleFollower::AddPhySensor(std::string colliderName, bool staticBody, Vec2 position, Vec2 size, float density, float friction)
		{
			m_Sensor = new PhySensor(colliderName, staticBody, position, size, density, friction);
		}

		void SimpleFollower::AddPhySensor(std::string colliderName, bool staticBody, Vec2 position, std::vector<Vec2> shapeVertices, const int vertexCount, float density, float friction)
		{
			m_Sensor = new PhySensor(colliderName, staticBody, position, shapeVertices, vertexCount, density, friction);
		}

		void SimpleFollower::AddPhySensor(std::string colliderName, bool staticBody,
			Vec2 position, float radius, float density, float friction)
		{
			m_Sensor = new PhySensor(colliderName, staticBody, position, radius, density, friction);
		}

		void SimpleFollower::Configure(float moveSpeed, float delayStart, Vec2Int waitTargetPos)
		{
			m_MoveSpeed = moveSpeed;
			m_WaitDelay = delayStart;
			m_WaitTarget = waitTargetPos;
		}

		void SimpleFollower::ConfigureTarget(Positional* target)
		{
			m_Target = target;
		}

		Positional* SimpleFollower::GetTarget() const
		{
			return m_Target;
		}

		void SimpleFollower::UpdateFollower()
		{
			if (!m_Sprite && !m_PhySprite)
			{
				return;
			}

			bool waiting = false;
			if (m_WaitDelay > 0)
			{
				m_WaitDelay = (float)(m_WaitDelay - Game::s_DeltaTime);
				waiting = true;
			}

			if (m_Target == nullptr) 
				return;

			if (m_PhySprite)
			{
				if (OutOfBounds(m_PhySprite))
				{
					DestroySelf();
					return;
				}
			}
			
			if(m_Sprite)
			{
				if (OutOfBounds(m_Sprite))
				{
					DestroySelf();
					return;
				}
			}

			if (m_DelayTime > 0)
			{
				m_DelayTime = (float)(m_DelayTime - Game::s_DeltaTime);
				return;
			}

			m_DelayTime = m_UpdateDirectionDelay;

			float x, y;

			if (m_PhySprite)
			{
				x = (float)m_PhySprite->GetX();
				y = (float)m_PhySprite->GetY();
			}
			else
			{
				x = (float)m_Sprite->GetX();
				y = (float)m_Sprite->GetY();
			}

			float speed = m_MoveSpeed * n2dTimeScale;

			float newX = x;
			float newY = y;

			if (!waiting)
			{
				newX = x < m_Target->GetX() + m_ScatterOffset.x ? x + speed : x - speed;
				newY = y < m_Target->GetY() + m_ScatterOffset.y ? y + speed : y - speed;

				if (x == m_Target->GetX() + m_ScatterOffset.x)
				{
					newX = x;
				}

				if (y == m_Target->GetY() + m_ScatterOffset.y)
				{
					newY = y;
				}

				Vec2 targetPos = m_Target->GetPosition();
				Vec2 currentPos = Vec2(newX, newY);

				float currentDistance = Vec2::Distance(targetPos, currentPos);
				bool atTarget = currentDistance < m_InRange;

				if (atTarget && m_DelayScatter > 25)
				{
					m_DelayScatter = 0;

					// Randomize miss
					Vec2Int size = GetSprite()->GetSize();
					m_ScatterOffset.y = n2dRandomInt(32, std::abs(m_ScatterOffset.x) + 32);
					m_ScatterOffset.x = n2dRandomInt(32, std::abs(m_ScatterOffset.y) + 32);
					
					if (n2dCoinFlip())
					{
						m_ScatterOffset.x *= -1;
					}

					if (n2dCoinFlip())
					{
						m_ScatterOffset.y *= -1;
					}
				}
				else
				{
					m_DelayScatter++;
				}

				m_MoveAngleDegrees = Vec2Int::LookAtAngle(Vec2Int((int)newX, (int)newY), m_Target->GetPositionInt(), 0);
				if (m_LookAtTarget)
				{
					float lookAtAngle = Vec2Int::LookAtAngle(Vec2Int((int)newX, (int)newY), m_Target->GetPositionInt(), m_LookAtDegAdd);
					if (m_PhySprite)
					{
						m_PhySprite->SetAngle(lookAtAngle);
					}
					
					if(m_Sprite)
					{
						m_Sprite->SetAngle(lookAtAngle);
					}
				}
			}
			else
			{
				if (!(m_WaitTarget.x == 0 && m_WaitTarget.y == 0))
				{
					newX = x < m_WaitTarget.x ? x + speed : x - speed;
					newY = y < m_WaitTarget.y ? y + speed : y - speed;
				}
			}

			Vec2 newPos = Vec2(newX, newY);
			SetPosition(newPos);

			if (m_Sensor)
			{
				m_Sensor->SetBodyPosition(Vec2(newPos.x + GetSprite()->GetWidth() / 2, newPos.y + GetSprite()->GetHeight() / 2));
			}

			if (m_PhySprite)
			{
				m_PhySprite->SetPosition(newPos);
			}
			
			if(m_Sprite)
			{
				m_Sprite->SetPosition(newPos);
			}

		}

		void SimpleFollower::DestroySelf()
		{
			if (m_Destroyed) return;

			if (m_Sprite)
				m_Sprite->DestroySelf();

			if (m_PhySprite)
				m_PhySprite->DestroySelf();

			if (m_Sensor)
				m_Sensor->DestroySelf();

			m_Destroyed = true;
			m_Alive = false;

			Deleteable::CleanUpdaters();
			Deleteable::SetDeleted(true);
		}
	}
}