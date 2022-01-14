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


		public:

			InputHandler();
			~InputHandler();

			void KeyDown(SDL_Event* event);
			void KeyUp(SDL_Event* event);

			
			void MouseClick(SDL_Event* event);

		public:

			static bool s_KeyIsPressed[MAX_KEYS];
			static bool IsKeyDown(SDL_Keycode key);

		};
	}
}