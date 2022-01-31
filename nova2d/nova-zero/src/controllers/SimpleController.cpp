#include "SimpleController.h"
#include "../core/Game.h"

namespace novazero
{
	namespace controllers
	{
		using namespace utils;
		using namespace core;

		SimpleController::SimpleController(std::string assetName, Vec2 position, Vec2Int size, char layer)
			: EventListener()
		{
			m_Sprite = new Sprite(assetName, position, size, layer);
			Game::s_SceneManager->s_TimeEffectorManager->AddEffected(this);
			ConfigureTimeEffected(m_Sprite);
		}

		SimpleController::~SimpleController()
		{
			if (m_Sprite)
				m_Sprite->DestroySelf();
		}

		void SimpleController::SetMoveSpeed(float mSpeed)
		{
			m_MoveSpeed = mSpeed;
		}

		void SimpleController::SetPositionInt(int x, int y)
		{
			m_Sprite->SetX((float)x);
			m_Sprite->SetY((float)y);
		}

		void SimpleController::SetPosition(float x, float y)
		{
			m_Sprite->SetX(x);
			m_Sprite->SetY(y);
		}

		void SimpleController::SetX(float x)
		{
			m_Sprite->SetX(x);
		}

		void SimpleController::SetY(float y)
		{
			m_Sprite->SetY(y);
		}

		void SimpleController::DestroySelf()
		{
			Game::s_SceneManager->s_TimeEffectorManager->RemoveEffected(this);
		}
	}
}