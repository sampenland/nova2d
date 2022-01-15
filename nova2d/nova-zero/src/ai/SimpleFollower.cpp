#include "SimpleFollower.h"

namespace novazero
{
	namespace ai
	{
		using namespace core;
		using namespace maths;
		using namespace graphics;

		SimpleFollower::SimpleFollower(Positional* target, const float moveUpdateDelay)
			: m_AliveBounds(Rect(0,0,0,0)), m_MoveSpeed(2)
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

		void SimpleFollower::Configure(int moveSpeed, Rect aliveBounds)
		{
			m_MoveSpeed = moveSpeed;
			m_AliveBounds = aliveBounds;
		}

		void SimpleFollower::Update()
		{
			if (!CheckAlive()) return;

			if (OutOfBounds())
			{
				m_Alive = false;
				return;
			}

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

		bool SimpleFollower::OutOfBounds()
		{
			if (m_Sprite)
			{
				int x = m_Sprite->GetX();
				int y = m_Sprite->GetY();
				int w = m_Sprite->GetWidth();
				int h = m_Sprite->GetHeight();

				int bx = m_AliveBounds.x;
				int by = m_AliveBounds.y;
				int bw = m_AliveBounds.w;
				int bh = m_AliveBounds.h;

				return !(x > bx && x < bx + bw - w && y > by && y < by + bh - h);
			}

			return true;
		}

		bool SimpleFollower::CheckAlive()
		{
			if (!m_Alive)
			{
				if (!m_Destroyed) 
				{
					DestroySelf();
				}
				return false;
			}

			return m_Alive;
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