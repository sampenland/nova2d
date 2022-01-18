#pragma once
#include "../logging/logging.h"
#include "SDL.h"
#include <vector>
#include "../core/Defines.h"
#include "../core/TypeDefs.h"

namespace novazero
{
	namespace input
	{
		class InputHandler
		{

		private:

			int m_JoyStickDeadzone = 8000;

		public:

			InputHandler();
			~InputHandler();

			void Configure(int joyStickDeadzone);

			void KeyDown(SDL_Event* event);
			void KeyUp(SDL_Event* event);
			
			void MouseClick(SDL_Event* event);

		public:

			static bool IsKeyDown(SDL_Keycode key);
			static std::vector<SDL_Keycode> s_KeyIsPressed;

			static float GetJoystickAxis(char joystickID, JoystickAxis axis);
			static bool IsJoystickButtonDown(char joystickID, int button);
			static SDL_Joystick* s_JoySticks[MAX_JOYSTICKS];

		};
	}
}