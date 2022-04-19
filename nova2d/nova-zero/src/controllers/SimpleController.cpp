#include "SimpleController.h"
#include "../core/Game.h"

namespace novazero
{
	namespace controllers
	{
		using namespace utils;
		using namespace core;

		SimpleController::SimpleController(const std::string& assetName, Vec2 position, Vec2Int size, unsigned char layer)
			: EventListener()
		{
			m_Sprite = new Sprite(assetName, position, size, layer);
			LinkPositionalDrawable(m_Sprite);
		}

		void SimpleController::SetMoveSpeed(float mSpeed)
		{
			m_MoveSpeed = mSpeed;
		}

		void SimpleController::DestroySelf()
		{
			if (m_Sprite)
				m_Sprite->DestroySelf();
		}
	}
}