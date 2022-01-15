#include "InputHandler.h"
#include <cstring>

#include "../logging/logging.h"

namespace novazero
{
	namespace input
	{
		std::vector<SDL_Keycode> InputHandler::s_KeyIsPressed;

		InputHandler::InputHandler()
		{
			s_KeyIsPressed.reserve(1);
		}

		InputHandler::~InputHandler() { }

		bool InputHandler::IsKeyDown(SDL_Keycode key)
		{
			for (size_t i = 0; i < s_KeyIsPressed.size(); i++)
			{
				if (key == s_KeyIsPressed[i])
				{
					return true;
				}
			}

			return false;
		}

		void InputHandler::KeyDown(SDL_Event* e)
		{
			if (std::end(s_KeyIsPressed) == std::find(s_KeyIsPressed.begin(), s_KeyIsPressed.end(), e->key.keysym.sym))
			{
				s_KeyIsPressed.push_back(e->key.keysym.sym);
			}
		}

		void InputHandler::KeyUp(SDL_Event* e)
		{
			int idx = -1;
			for (size_t i = 0; i < s_KeyIsPressed.size(); i++)
			{
				if (e->key.keysym.sym == s_KeyIsPressed[i])
				{
					idx = i;
					break;
				}
			}

			if (idx == -1) return;

			s_KeyIsPressed.erase(s_KeyIsPressed.begin() + idx);
		}

		void InputHandler::MouseClick(SDL_Event* e)
		{

		}
	}
}