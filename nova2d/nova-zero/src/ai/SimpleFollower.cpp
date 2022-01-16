#include "SimpleFollower.h"

namespace novazero
{
	namespace ai
	{
		using namespace core;
		using namespace maths;
		using namespace graphics;

		SimpleFollower::SimpleFollower(Positional* target, const float moveUpdateDelay)
			:  m_MoveSpeed(2)
		{
			m_Target = target;
			m_UpdateDirectionDelay = moveUpdateDelay / 1000;

			m_AliveBounds = Rect(0, 0, Game::s_Width, Game::s_Height);
			m_DelayTime = m_UpdateDirectionDelay;

			Game::AddUpdater(std::bind(&SimpleFollower::Update, this));
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

		void SimpleFollower::Update()
		{
			OutOfBounds(m_Sprite);

			if (!CheckAlive()) return;

			if (m_DelayTime > 0)
			{
				m_DelayTime -= Game::s_DeltaTime;
				return;
			}

			m_DelayTime = m_UpdateDirectionDelay;

			int x = m_Sprite->GetX();
			int y = m_Sprite->GetY();

			int newX = x < m_Target->GetX() + m_TargetOffset.x ? x + m_MoveSpeed : x - m_MoveSpeed;
			int newY = y < m_Target->GetY() + m_TargetOffset.y ? y + m_MoveSpeed : y - m_MoveSpeed;

			if (x == m_Target->GetX() + m_TargetOffset.x) newX = x;
			if (y == m_Target->GetY() + m_TargetOffset.y) newY = y;

			m_Sprite->SetPosition(newX, newY);

		}

		void SimpleFollower::DestroySelf()
		{
			if (m_Destroyed) return;

			m_Destroyed = true;

			Game::RemoveUpdater(std::bind(&SimpleFollower::Update, this));
			
			if (m_Sprite)
				delete m_Sprite;
		}
	}
}