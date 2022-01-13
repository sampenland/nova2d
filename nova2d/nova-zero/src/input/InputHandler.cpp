#include "InputHandler.h"
#include <cstring>

namespace novazero
{
	namespace input
	{
		InputHandler::InputHandler()
		{
			memset(m_KeyIsPressed, false, MAX_KEYS);
		}

		InputHandler::~InputHandler()
		{

		}

		bool InputHandler::IsKeyDown(SDL_Scancode key)
		{
			return m_KeyIsPressed[key];
		}

		void InputHandler::KeyDown(SDL_Event* e)
		{
			m_KeyIsPressed[e->key.keysym.scancode] = true;
		}

		void InputHandler::KeyUp(SDL_Event* e)
		{
			m_KeyIsPressed[e->key.keysym.scancode] = false;
		}

		void InputHandler::MouseClick(SDL_Event* e)
		{

		}
	}
}