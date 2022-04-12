#include "SimpleFollower.h"
#include "../core/Game.h"

namespace novazero
{
	namespace ai
	{
		using namespace core;
		using namespace maths;
		using namespace graphics;

		SimpleFollower::SimpleFollower(Positional* target, const float moveUpdateDelayMS)
			:  Collider(0), m_MoveSpeed(2), TimeEffected()
		{
			m_Target = target;
			m_UpdateDirectionDelay = moveUpdateDelayMS;

			SetTimeEffectEnabled(false);

			m_AliveBounds = Rect(0.f, 0.f, (float)Game::s_Width, (float)Game::s_Height);
			m_DelayTime = m_UpdateDirectionDelay;

			auto id = n2dAddUpdater(SimpleFollower::UpdateFollower, this);
			Deleteable::m_CleanUpdaters.push_back(id);
		}

		void SimpleFollower::AddSprite(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer)
		{
			m_Sprite = new Sprite(assetName, position, size, layer);
			ConfigureTimeEffected(m_Sprite);
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

		void SimpleFollower::UpdateFollower()
		{
			bool waiting = false;
			if (m_WaitDelay > 0)
			{
				m_WaitDelay = (float)(m_WaitDelay - Game::s_DeltaTime);
				waiting = true;
			}

			if (m_Target == nullptr) return;

			if (OutOfBounds(m_Sprite))
			{
				DestroySelf();
				return;
			}

			if (m_DelayTime > 0)
			{
				m_DelayTime = (float)(m_DelayTime - Game::s_DeltaTime);
				return;
			}

			m_DelayTime = m_UpdateDirectionDelay;

			float x = (float)m_Sprite->GetX();
			float y = (float)m_Sprite->GetY();
			float speed = m_MoveSpeed * n2dTimeScale * GetTimeInfluence();

			float newX = x;
			float newY = y;

			if (!waiting)
			{
				newX = x < m_Target->GetX() + m_TargetOffset.x ? x + speed : x - speed;
				newY = y < m_Target->GetY() + m_TargetOffset.y ? y + speed : y - speed;

				if (x == m_Target->GetX() + m_TargetOffset.x) newX = x;
				if (y == m_Target->GetY() + m_TargetOffset.y) newY = y;

				if (m_LookAtTarget)
				{
					float lookAtAngle = Vec2Int::LookAtAngle(Vec2Int((int)newX, (int)newY), m_Target->GetPositionInt(), m_LookAtDegAdd);
					m_Sprite->SetAngle(lookAtAngle);
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

			m_Sprite->SetPosition(Vec2(newX, newY));

		}

		void SimpleFollower::DestroySelf()
		{
			if (m_Destroyed) return;

			m_Destroyed = true;
			m_Alive = false;

			Deleteable::CleanUpdaters();

			if (m_UsingCollider)
			{
				SceneManager::s_CollisionManager->RemoveCollider(this);
			}
			
			if (m_Sprite)
				m_Sprite->DestroySelf();

			Deleteable::SetDeleted(true);
		}

		void SimpleFollower::OnCollision(Collision* collision)
		{

		}
	}
}