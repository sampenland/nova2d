#include "SimpleBulletController.h"
#include "../core/Game.h"

namespace novazero
{
	namespace controllers
	{
		using namespace core;
		using namespace maths;
		using namespace graphics;

		SimpleBulletController::SimpleBulletController(Vec2Int start, Vec2Int end, const float moveUpdateDelay)
			: m_MoveSpeed(2)
		{
			m_UpdateDirectionDelay = moveUpdateDelay / 1000;
			m_Start = start;
			m_End = end;

			m_AliveBounds = Rect(0.f, 0.f, (float)Game::s_Width, (float)Game::s_Height);
			m_DelayTime = m_UpdateDirectionDelay;

			auto cleanID = n2dAddUpdater(SimpleBulletController::Update, this);
			m_CleanUpdaters.push_back(cleanID);

			SetEnabled(true);
		}

		void SimpleBulletController::AddSprite(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer)
		{
			m_DeleteName = assetName;
			m_Sprite = new Sprite(assetName, position, size, layer);
			LinkPositionalDrawable(m_Sprite);
		}

		void SimpleBulletController::Configure(float moveSpeed, Rect aliveBounds)
		{
			m_MoveSpeed = moveSpeed;
			m_AliveBounds = aliveBounds;
			m_UsingAliveBounds = true;			
		}

		void SimpleBulletController::Update()
		{			
			if (!IsEnabled()) return;

			if (OutOfBounds(GetSprite()))
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

			float x = (float)GetSprite()->GetX();
			float y = (float)GetSprite()->GetY();
			float speed = m_MoveSpeed * n2dTimeScale;

			float newX = x < m_End.x ? x + speed : x - speed;
			float newY = y < m_End.y ? y + speed : y - speed;

			if (x == m_End.x) newX = x;
			if (y == m_End.y) newY = y;

			if (newX - (int)newX > 0) newX = ceil(newX);
			if (newY - (int)newY > 0) newY = ceil(newY);

			GetSprite()->SetPositionInt(Vec2Int((int)newX, (int)newY));

		}

		void SimpleBulletController::DestroySelf()
		{
  			if (m_Destroyed) return;

			if (f_OnDestroy)
				f_OnDestroy();

			m_Destroyed = true;
			m_Alive = false;

			CleanUpdaters();

			if (m_Sprite)
				m_Sprite->DestroySelf();

			SetDeleted(true);
		}
	}
}