#pragma once

#include "SDL.h"

#define MAX_KEYS 1024
#define MAX_MOUSE_BUTTONS 20

namespace novazero
{
	namespace input
	{
		class InputHandler
		{

		private:

			bool m_KeyIsPressed[MAX_KEYS];

		public:

			InputHandler();
			~InputHandler();

			void KeyDown(SDL_Event* event);
			void KeyUp(SDL_Event* event);

			bool IsKeyDown(SDL_Scancode key);
			
			void MouseClick(SDL_Event* event);

		};
	}
}