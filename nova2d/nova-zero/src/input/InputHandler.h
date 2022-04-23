#pragma once
#include "../logging/logging.h"
#include <vector>
#include "SDL.h"
#include "Inputable.h"
#include <map>
#include "../maths/Maths.h"

namespace novazero
{
	namespace input
	{
		using namespace maths;

		class InputHandler
		{

		private:

			char m_CharBuffer[1024] = {};
			int m_CharBufferMax = 1024;
			int m_CharBufferIndex = 0;

			Inputable* m_SelectedInput = nullptr;

			bool m_Touching = false;
			bool m_TouchingMotion = false;
			Vec2 m_TouchPosition = NULLVEC2;

			bool m_MouseWait = false;
			bool m_MouseLastUp = true;
			bool m_MouseJustDown = false;

			bool m_MouseLeftClicked = false;
			bool m_MouseRightClicked = false;
			bool m_MouseMiddleClicked = false;

			bool m_MouseMotion = false;

			Vec2 m_MouseHoverPosition = NULLVEC2;
			Vec2 m_MouseLeftPosition = NULLVEC2;
			Vec2 m_MouseRightPosition = NULLVEC2;
			Vec2 m_MouseMiddlePosition = NULLVEC2;

			static std::map<int, float> s_JoyAxis[MAX_JOYSTICKS];
			static std::map<int, bool> s_JoyHat[MAX_JOYSTICKS];

		public:

			InputHandler();

			void ConfigureJoystickDeadzone(int joyStickDeadzone);

			void KeyDown(SDL_Event* event);
			void KeyUp(SDL_Event* event);

			void TouchDown(SDL_Event* event);
			void TouchMotion(SDL_Event* event);
			void TouchUp(SDL_Event* event);

			Vec2 GetTouchLocation() const;

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
			
			void ResetMouseDowns();
			void MouseMotion(SDL_Event* event);
			void MouseDown(SDL_Event* event);
			void MouseUp(SDL_Event* event);
			Vec2 GetMousePosition() const;
			bool IsMouseJustDown() const;
			bool IsMouseDown(int mouseButton) const;
			bool IsMouseUp(int mouseButton) const;
			bool IsMouseMoving() const;

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