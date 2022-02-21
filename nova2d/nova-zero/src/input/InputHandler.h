#pragma once
#include "../logging/logging.h"
#include <vector>
#include "SDL.h"
#include "../core/Defines.h"
#include "Inputable.h"
#include <map>

namespace novazero
{
	namespace input
	{
		class InputHandler
		{

		private:

			char m_CharBuffer[1024] = {};
			int m_CharBufferMax = 1024;
			int m_CharBufferIndex = 0;

			Inputable* m_SelectedInput = nullptr;

			static std::map<int, float> s_JoyAxis[MAX_JOYSTICKS];
			static std::map<int, bool> s_JoyHat[MAX_JOYSTICKS];

		public:

			InputHandler();

			void Configure(int joyStickDeadzone);

			void KeyDown(SDL_Event* event);
			void KeyUp(SDL_Event* event);

			void JoyAxisChange(SDL_Event* event);
			void JoyHatChange(SDL_Event* event);

			void SelectInputTarget(Inputable* inputTarget);
			void ClearInputTarget() { m_SelectedInput = nullptr; m_CharBufferIndex = 0; };

			void OnTextChange(SDL_Event* e);
			void CleanTextBuffer(int newCharBufferMax = 1024);
			void SetTextBufferIndex(int idx);
			void SetTextBuffer(std::string fillText, int maxChars);

			void GetCharBufferAsString(std::string& bufferOUT) 
			{ 
				std::string r = "";
				for (int i = 0; i < m_CharBufferIndex; i++)
				{
					r += m_CharBuffer[i];
				}
			
				bufferOUT = r;
			}
			
			void MouseClick(SDL_Event* event);

			void DestroySelf();

		public:

			static bool IsKeyDown(SDL_Keycode key);
			static bool IsKeyUp(SDL_Keycode key);
			static std::vector<SDL_Keycode> s_KeyIsPressed;

			static int s_JoyStickDeadzone;

			static bool GetJoystickHat(char joystickID, Uint8 button);
			static float GetJoystickAxis(char joystickID, int axis);
			static bool IsJoystickButtonDown(char joystickID, int button);
			static bool IsJoystickButtonUp(char joystickID, int button);
			static SDL_Joystick* s_JoySticks[MAX_JOYSTICKS];

		};
	}
}