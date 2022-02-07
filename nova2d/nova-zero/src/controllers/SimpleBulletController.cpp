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
			: Collider(0), m_MoveSpeed(2)
		{
			m_UpdateDirectionDelay = moveUpdateDelay / 1000;
			m_Start = start;
			m_End = end;

			m_AliveBounds = Rect(0, 0, Game::s_Width, Game::s_Height);
			m_DelayTime = m_UpdateDirectionDelay;

			auto cleanID = n2dAddUpdater(SimpleBulletController::Update, this);
			m_CleanUpdaters.push_back(cleanID);

			Game::s_SceneManager->s_TimeEffectorManager->AddEffected(this);

			SetEnabled(true);
		}

		void SimpleBulletController::AddSprite(std::string assetName, Vec2 position, Vec2Int size, char layer)
		{
			m_DeleteName = assetName;
			m_Sprite = new Sprite(assetName, position, size, layer);
			ConfigureTimeEffected(m_Sprite);
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

			float newX = x < m_End.x ? x + speed : x - speed;
			float newY = y < m_End.y ? y + speed : y - speed;

			if (x == m_End.x) newX = x;
			if (y == m_End.y) newY = y;

			if (newX - (int)newX > 0) newX = ceil(newX);
			if (newY - (int)newY > 0) newY = ceil(newY);

			m_Sprite->SetPosition(Vec2(newX, newY));

		}

		void SimpleBulletController::OnCollision(Collision* collision)
		{

		}

		void SimpleBulletController::DestroySelf()
		{
  			if (m_Destroyed) return;

			if (f_OnDestroy)
				f_OnDestroy();

			m_Destroyed = true;
			m_Alive = false;

			CleanUpdaters();

			Game::s_SceneManager->s_TimeEffectorManager->RemoveEffected(this);

			if (m_UsingCollider)
			{
				SceneManager::s_CollisionManager->RemoveCollider(this);
			}

			if (m_Sprite)
				m_Sprite->DestroySelf();
			
			SetDeleted(true);
		}
	}
}