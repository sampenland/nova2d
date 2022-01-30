#include "SimpleFollower.h"

namespace novazero
{
	namespace ai
	{
		using namespace core;
		using namespace maths;
		using namespace graphics;

		SimpleFollower::SimpleFollower(Positional* target, const float moveUpdateDelay)
			:  Collider(0), m_MoveSpeed(2)
		{
			m_Target = target;
			m_UpdateDirectionDelay = moveUpdateDelay / 1000;

			m_AliveBounds = Rect(0, 0, Game::s_Width, Game::s_Height);
			m_DelayTime = m_UpdateDirectionDelay;

			auto id = n2dAddUpdater(SimpleFollower::UpdateFollower, this);
			m_CleanUpdaters.push_back(id);
		}

		SimpleFollower::~SimpleFollower()
		{
			
		}

		void SimpleFollower::AddSprite(std::string assetName, Vec2Int position, Vec2Int size, char layer)
		{
			m_Sprite = new Sprite(assetName, position, size, layer);
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
			float speed = m_MoveSpeed * n2dTimeScale;

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
					int lookAtAngle = Vec2Int::LookAtAngle(Vec2Int((int)newX, (int)newY), m_Target->GetPosition(), m_LookAtDegAdd);
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

			m_Sprite->SetPosition(Vec2Int((int)newX, (int)newY));

		}

		void SimpleFollower::DestroySelf()
		{
			if (m_Destroyed) return;

			m_Destroyed = true;
			m_Alive = false;

			CleanUpdaters();

			if (m_UsingCollider)
			{
				SceneManager::s_CollisionManager->RemoveCollider(this);
			}
			
			if (m_Sprite)
				m_Sprite->DestroySelf();

			m_DeleteNow = 1;
		}

		void SimpleFollower::OnCollision(Collision* collision)
		{

		}
	}
}