#include "SimpleController.h"

namespace novazero
{
	namespace controllers
	{
		using namespace utils;

		SimpleController::SimpleController(const char* spriteSheet, Vec2 position, Vec2 size, char layer)
		{
			m_Sprite = new Sprite(position, spriteSheet, size);
			Game::s_Renderer->s_DrawLayers->AddSprite(m_Sprite, layer);
		}

		SimpleController::~SimpleController()
		{
			Game::s_Renderer->s_DrawLayers->RemoveSprite(m_Sprite->m_ID, m_Sprite->m_Layer);

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