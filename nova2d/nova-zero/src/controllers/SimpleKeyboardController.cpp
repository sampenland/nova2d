#include "SimpleKeyboardController.h"

namespace novazero
{
	namespace controllers
	{
		using namespace utils;

		SimpleKeyboardController::SimpleKeyboardController(const char* spriteSheet, Vec2 position)
		{
			m_Sprite = new Sprite(position, spriteSheet);
		}

		SimpleKeyboardController::~SimpleKeyboardController()
		{
			if (m_Sprite)
				delete m_Sprite;
		}

		void SimpleKeyboardController::Update()
		{
			EventStep();
		}
	}
}