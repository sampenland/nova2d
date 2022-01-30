#include "SimpleController.h"
#include "../core/Game.h"

namespace novazero
{
	namespace controllers
	{
		using namespace utils;
		using namespace core;

		SimpleController::SimpleController(std::string assetName, Vec2Int position, Vec2Int size, char layer)
			: EventListener()
		{
			m_Sprite = new Sprite(assetName, position, size, layer);
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

		void SimpleController::SetPosition(int x, int y)
		{
			m_Sprite->SetX(x);
			m_Sprite->SetY(y);
		}

		void SimpleController::SetX(int x)
		{
			m_Sprite->SetX(x);
		}

		void SimpleController::SetY(int y)
		{
			m_Sprite->SetY(y);
		}
	}
}