#include "SimpleFollower.h"

namespace novazero
{
	namespace ai
	{
		using namespace core;
		using namespace maths;
		using namespace graphics;

		SimpleFollower::SimpleFollower(Positional* target, const float moveUpdateDelay)
			:  Collider(0), Deleteable("simpleFollower"), m_MoveSpeed(2)
		{
			m_Target = target;
			m_UpdateDirectionDelay = moveUpdateDelay / 1000;

			m_AliveBounds = Rect(0, 0, Game::s_Width, Game::s_Height);
			m_DelayTime = m_UpdateDirectionDelay;

			auto id = n2dAddUpdater(SimpleFollower::Update, this);
			m_CleanUpdaters.push_back(id);
		}

		SimpleFollower::~SimpleFollower()
		{
			DestroySelf();
		}

		void SimpleFollower::AddSprite(std::string assetName, Vec2Int position, Vec2Int size, char layer)
		{
			m_Sprite = new Sprite(assetName, position, size, layer);
		}

		void SimpleFollower::Configure(int moveSpeed)
		{
			m_MoveSpeed = moveSpeed;
		}

		void SimpleFollower::ConfigureTarget(Positional* target)
		{
			m_Target = target;
		}

		void SimpleFollower::Update()
		{
			if (m_Target == nullptr) return;

			OutOfBounds(m_Sprite);

			if (!CheckAlive()) return;

			if (m_DelayTime > 0)
			{
				m_DelayTime = (float)(m_DelayTime - Game::s_DeltaTime);
				return;
			}

			m_DelayTime = m_UpdateDirectionDelay;

			int x = m_Sprite->GetX();
			int y = m_Sprite->GetY();

			int newX = x < m_Target->GetX() + m_TargetOffset.x ? x + m_MoveSpeed : x - m_MoveSpeed;
			int newY = y < m_Target->GetY() + m_TargetOffset.y ? y + m_MoveSpeed : y - m_MoveSpeed;

			if (x == m_Target->GetX() + m_TargetOffset.x) newX = x;
			if (y == m_Target->GetY() + m_TargetOffset.y) newY = y;

			if (m_LookAtTarget)
			{
				int lookAtAngle = Vec2Int::LookAtAngle(Vec2Int(newX, newY), m_Target->GetPosition(), m_LookAtDegAdd);
				m_Sprite->SetAngle(lookAtAngle);
			}

			m_Sprite->SetPosition(Vec2Int(newX, newY));

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
				delete m_Sprite;
		}

		void SimpleFollower::OnCollision(Collision* collision)
		{

		}
	}
}