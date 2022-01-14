#include "InputHandler.h"
#include <cstring>

namespace novazero
{
	namespace input
	{
		bool InputHandler::s_KeyIsPressed[];

		InputHandler::InputHandler()
		{
			memset(s_KeyIsPressed, false, MAX_KEYS);
		}

		InputHandler::~InputHandler()
		{

		}

		bool InputHandler::IsKeyDown(SDL_Keycode key)
		{
			return s_KeyIsPressed[key];
		}

		void InputHandler::KeyDown(SDL_Event* e)
		{
			s_KeyIsPressed[e->key.keysym.sym] = true;
		}

		void InputHandler::KeyUp(SDL_Event* e)
		{
			s_KeyIsPressed[e->key.keysym.sym] = false;
		}

		void InputHandler::MouseClick(SDL_Event* e)
		{

		}
	}
}