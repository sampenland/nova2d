#include "../core/NovaCore.h"
#include "InputHandler.h"
#include <string>
#include "../core/Game.h"

namespace novazero
{
	namespace input
	{
		using namespace core;

		int InputHandler::s_JoyStickDeadzone = 8000;

		std::vector<SDL_Keycode> InputHandler::s_KeyIsPressed;
		SDL_Joystick* InputHandler::s_JoySticks[MAX_JOYSTICKS];
		std::map<int, float> InputHandler::s_JoyAxis[MAX_JOYSTICKS];
		std::map<int, bool> InputHandler::s_JoyHat[MAX_JOYSTICKS];

		InputHandler::InputHandler()
		{
			s_KeyIsPressed.reserve(1);

			memset(s_JoySticks, 0, MAX_JOYSTICKS);
			for (int i = 0; i < SDL_NumJoysticks(); i++)
			{
				s_JoySticks[i] = SDL_JoystickOpen(i);
			}

			CleanTextBuffer();

		}

		void InputHandler::SelectInputTarget(Inputable* inputTarget)
		{
			m_SelectedInput = inputTarget;
		}

		void InputHandler::OnTextChange(SDL_Event* e)
		{
			if (!m_SelectedInput) return;

			if (m_CharBufferIndex < m_CharBufferMax)
			{
				m_CharBuffer[m_CharBufferIndex] = e->text.text[0];
				m_CharBufferIndex++;
			}
		}

		void InputHandler::SetTextBufferIndex(int idx)
		{
			if (idx < m_CharBufferMax)
			{
				m_CharBufferIndex = idx;
			}
		}

		void InputHandler::CleanTextBuffer(int newCharBufferMax)
		{
			// Clear 100 BYTES of char buffer (all BYTES)
			memset(m_CharBuffer, 0, 100);
			m_CharBufferMax = newCharBufferMax;
			m_CharBufferIndex = 0;
		}

		void InputHandler::SetTextBuffer(std::string fillText, int maxChars)
		{
			m_CharBufferIndex = (int)fillText.length();
			if (m_CharBufferIndex >= maxChars)
			{
				SetTextBuffer("text", 12);
				return;
			}

			memset(m_CharBuffer, 0, 1024);
			m_CharBufferMax = maxChars;
			if ((int)fillText.length() < maxChars)
			{
				strcat(m_CharBuffer, fillText.c_str());
			}
			else
			{
				memset(m_CharBuffer, 0, 100);
				m_CharBufferIndex = 0;
			}
		}

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

		bool InputHandler::IsKeyUp(SDL_Keycode key)
		{
			return !IsKeyDown(key);
		}

		void InputHandler::KeyDown(SDL_Event* e)
		{
			if (e->key.keysym.sym == SDLK_BACKSPACE)
			{
				if (m_CharBufferIndex > 0) m_CharBufferIndex--;
			}

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

		void InputHandler::TouchDown(SDL_Event* event)
		{
			m_Touching = true;
			m_TouchPosition.x = event->tfinger.x * Game::s_Width;
			m_TouchPosition.y = event->tfinger.y * Game::s_Height;

			if (n2dDebugVerbose)
			{
				LOGS("Touched at: " + tostring(m_TouchPosition.x) + ", " + tostring(m_TouchPosition.y));
			}
		}

		void InputHandler::TouchMotion(SDL_Event* event)
		{
			m_Touching = true;
			m_TouchingMotion = true;
			m_TouchPosition.x = event->tfinger.x * Game::s_Width;
			m_TouchPosition.y = event->tfinger.y * Game::s_Height;

			if (n2dDebugVerbose)
			{
				LOGS("Touched Motion: " + tostring(m_TouchPosition.x) + ", " + tostring(m_TouchPosition.y));
			}
		}

		void InputHandler::TouchUp(SDL_Event* event)
		{
			m_Touching = false;
			m_TouchingMotion = false;
			m_TouchPosition.x = event->tfinger.x * Game::s_Width;
			m_TouchPosition.y = event->tfinger.y * Game::s_Height;

			if (n2dDebugVerbose)
			{
				LOGS("Touched Released at: " + tostring(m_TouchPosition.x) + ", " + tostring(m_TouchPosition.y));
			}

		}

		/*
		Returns touch location or NULLVEC2 if not touching
		*/
		Vec2 InputHandler::GetTouchLocation() const
		{
			if (m_Touching)
			{
				return m_TouchPosition;
			}
			else
			{
				return NULLVEC2; // Screen not being touched
			}
		}

		void InputHandler::ConfigureJoystickDeadzone(int joyStickDeadzone)
		{
			s_JoyStickDeadzone = joyStickDeadzone;
		}

		void InputHandler::JoyAxisChange(SDL_Event* event)
		{
			s_JoyAxis[event->jdevice.which][event->jaxis.axis] = event->jaxis.value;
		}

		void InputHandler::JoyHatChange(SDL_Event* event)
		{
			s_JoyHat[event->jdevice.which][SDL_HAT_LEFT] = false;
			s_JoyHat[event->jdevice.which][SDL_HAT_RIGHT] = false;
			s_JoyHat[event->jdevice.which][SDL_HAT_UP] = false;
			s_JoyHat[event->jdevice.which][SDL_HAT_DOWN] = false;

			s_JoyHat[event->jdevice.which][event->jhat.value] = true;
			
		}

		bool InputHandler::GetJoystickHat(char joystickID, Uint8 button)
		{
			std::map<int, bool>::iterator f = s_JoyHat[joystickID].find(button);

			if (f != s_JoyHat->end())
			{
				return s_JoyHat[joystickID].at(button);
			}

			return false;
		}
		
		bool InputHandler::IsJoystickButtonDown(char joystickID, int button)
		{
			if (joystickID > MAX_JOYSTICKS - 1) return false;
			return SDL_JoystickGetButton(s_JoySticks[joystickID], button) == 1;
		}

		bool InputHandler::IsJoystickButtonUp(char joystickID, int button)
		{
			return !IsJoystickButtonDown(joystickID, button);
		}

		float InputHandler::GetJoystickAxis(char joystickID, int axis)
		{
			std::map<int, float>::iterator f = s_JoyAxis[joystickID].find(axis);

			if (f != s_JoyAxis->end())
			{
				return s_JoyAxis[joystickID].at(axis);
			}

			return 0.f;
		}

		void InputHandler::ResetMouseDowns()
		{
			m_MouseJustDown = false;
			m_MouseWait = false;
		}

		void InputHandler::MouseMotion(SDL_Event* e)
		{
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			
			m_MouseHoverPosition = Vec2((float)mouseX, (float)mouseY);
			
			if (n2dIsMouseDown(SDL_BUTTON_LEFT))
			{
				m_MouseLeftPosition = Vec2((float)mouseX, (float)mouseY);
			}
			else if (n2dIsMouseDown(SDL_BUTTON_RIGHT))
			{
				m_MouseRightPosition = Vec2((float)mouseX, (float)mouseY);
			}
			else if (n2dIsMouseDown(SDL_BUTTON_MIDDLE))
			{
				m_MouseMiddlePosition = Vec2((float)mouseX, (float)mouseY);
			}
			else
			{
				m_MouseHoverPosition = Vec2((float)mouseX, (float)mouseY);
			}

			m_MouseMotion = true;

		}

		void InputHandler::MouseDown(SDL_Event* e)
		{
			if (!m_MouseJustDown && !m_MouseWait)
			{
				if (m_MouseLastUp)
				{
					m_MouseJustDown = true;
					m_MouseLastUp = false;
				}
			}
			else
			{
				m_MouseWait = true;
				m_MouseJustDown = false;
			}
			m_MouseLastUp = false;

			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);

			if (n2dDebugVerbose)
			{
				LOGS("[" + tostring(e->button.button) + "] Mouse Down at: (" + tostring(mouseX) + ", " + tostring(mouseY) + ")");
			}

			if (e->button.button == SDL_BUTTON_LEFT)
			{
				m_MouseLeftClicked = true;
				m_MouseRightClicked = false;
				m_MouseMiddleClicked = false;

				m_MouseLeftPosition = Vec2((float)mouseX, (float)mouseY);

			}
			else if (e->button.button == SDL_BUTTON_RIGHT)
			{
				m_MouseLeftClicked = false;
				m_MouseRightClicked = true;
				m_MouseMiddleClicked = false;

				m_MouseRightPosition = Vec2((float)mouseX, (float)mouseY);
			}
			else if (e->button.button == SDL_BUTTON_MIDDLE)
			{
				m_MouseLeftClicked = false;
				m_MouseRightClicked = true;
				m_MouseMiddleClicked = true;

				m_MouseMiddlePosition = Vec2((float)mouseX, (float)mouseY);
			}			
		}

		void InputHandler::MouseUp(SDL_Event* e)
		{
			if (!m_MouseLastUp)
			{
				m_MouseLastUp = true;
			}

			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			
			if (n2dDebugVerbose)
			{
				LOGS("[" + tostring(e->button.button) + "] Mouse UP at: (" + tostring(mouseX) + ", " + tostring(mouseY) + ")");
			}

			if (e->button.button == SDL_BUTTON_LEFT)
			{
				m_MouseLeftClicked = false;
				m_MouseLeftPosition = Vec2((float)mouseX, (float)mouseY);

			}
			else if (e->button.button == SDL_BUTTON_RIGHT)
			{
				m_MouseRightClicked = false;
				m_MouseRightPosition = Vec2((float)mouseX, (float)mouseY);
			}
			else if (e->button.button == SDL_BUTTON_MIDDLE)
			{
				m_MouseMiddleClicked = false;
				m_MouseMiddlePosition = Vec2((float)mouseX, (float)mouseY);
			}

			m_MouseMotion = false;

		}

		Vec2 InputHandler::GetMousePosition() const
		{
			if (n2dIsMouseDown(SDL_BUTTON_LEFT))
			{
				return m_MouseLeftPosition;
			}
			else if (n2dIsMouseDown(SDL_BUTTON_RIGHT))
			{
				return m_MouseRightPosition;
			}
			else if (n2dIsMouseDown(SDL_BUTTON_MIDDLE))
			{
				return m_MouseMiddlePosition;
			}
			else
			{
				return m_MouseHoverPosition;
			}
		}

		bool InputHandler::IsMouseJustDown() const
		{
			return m_MouseJustDown;
		}

		bool InputHandler::IsMouseDown(int mouseButton) const
		{
			if (mouseButton == SDL_BUTTON_LEFT)
			{
				return m_MouseLeftClicked;
			}
			else if (mouseButton == SDL_BUTTON_RIGHT)
			{
				return m_MouseRightClicked;
			}
			else if (mouseButton == SDL_BUTTON_MIDDLE)
			{
				return m_MouseMiddleClicked;
			}
			else
			{
				return false;
			}
		}

		bool InputHandler::IsMouseUp(int mouseButton) const
		{
			return !IsMouseDown(mouseButton);
		}

		bool InputHandler::IsMouseMoving() const
		{
			return m_MouseMotion;
		}

		void InputHandler::DestroySelf()
		{
			for (int i = 0; i < SDL_NumJoysticks(); i++)
			{
				SDL_JoystickClose(s_JoySticks[i]);
				s_JoySticks[i] = NULL;
			}
		}
	}
}