#include "SimpleController.h"

namespace novazero
{
	namespace controllers
	{
		using namespace utils;

		SimpleController::SimpleController(std::string assetName, Vec2Int position, Vec2Int size, char layer)
			: EventListener()
		{
			m_Sprite = new Sprite(assetName, position, size, layer);
		}

		SimpleController::~SimpleController()
		{
			if (m_Sprite)
				delete m_Sprite;
		}

		void SimpleController::SetMoveSpeed(int mSpeed)
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