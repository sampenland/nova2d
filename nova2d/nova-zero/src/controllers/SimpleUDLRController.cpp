#include "SimpleUDLRController.h"

namespace novazero
{
	namespace controllers
	{
		using namespace utils;

		SimpleUDLRController::SimpleUDLRController(const char* spriteSheet, Vec2 position, Vec2 size, char layer)
		{
			m_Sprite = new Sprite(position, spriteSheet, size);
			Game::s_Renderer->s_DrawLayers->AddSprite(m_Sprite, layer);
		}

		SimpleUDLRController::~SimpleUDLRController()
		{
			Game::s_Renderer->s_DrawLayers->RemoveSprite(m_Sprite->m_ID, m_Sprite->m_Layer);

			if (m_Sprite)
				delete m_Sprite;
		}

		void SimpleUDLRController::Update()
		{
			EventStep();
		}
	}
}