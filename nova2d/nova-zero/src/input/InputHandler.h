#pragma once
#include "SDL.h"
#include <vector>

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

			static bool IsKeyDown(SDL_Keycode key);
			static std::vector<SDL_Keycode> s_KeyIsPressed;

		};
	}
}