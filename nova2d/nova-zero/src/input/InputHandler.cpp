#include "InputHandler.h"
#include <cstring>

namespace novazero
{
	namespace input
	{
		std::vector<SDL_Keycode> InputHandler::s_KeyIsPressed;
		SDL_Joystick* InputHandler::s_JoySticks[MAX_JOYSTICKS];

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

		InputHandler::~InputHandler() 
		{
			for (int i = 0; i < SDL_NumJoysticks(); i++)
			{
				SDL_JoystickClose(s_JoySticks[i]);
				s_JoySticks[i] = NULL;
			}
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

		void InputHandler::Configure(int joyStickDeadzone)
		{
			m_JoyStickDeadzone = joyStickDeadzone;
		}
		
		bool InputHandler::IsJoystickButtonDown(char joystickID, int button)
		{
			if (joystickID > MAX_JOYSTICKS - 1) return false;
			return SDL_JoystickGetButton(s_JoySticks[joystickID], button) == 1;
		}

		float InputHandler::GetJoystickAxis(char joystickID, JoystickAxis axis)
		{
			if (joystickID > MAX_JOYSTICKS - 1) return false;
			return SDL_JoystickGetAxis(s_JoySticks[joystickID], (int)axis);
		}

		void InputHandler::MouseClick(SDL_Event* e)
		{

		}
	}
}