#pragma once
#include "SDL.h"
#include <vector>
#include "../core/Deleteable.h"
#include <functional>

namespace novazero
{
	namespace core
	{
		class EventListener : public Deleteable
		{

		private:
			
			std::vector<SDL_Keycode> m_KeyCodes;
			std::vector<std::function<bool(SDL_Keycode)>> m_KeysConditions;
			std::vector<std::function<void()>> m_KeysEvents;

			std::vector<SDL_Keycode> m_KeyCodes1;
			std::vector<std::function<bool(SDL_Keycode)>> m_KeysConditions1;
			std::vector<std::function<void()>> m_KeysEvents1;

			std::vector<int> m_JoysticksIDs;
			std::vector<int> m_JoystickButtons;
			std::vector<std::function<bool(int, int)>> m_JoysticksConditions;
			std::vector<std::function<void()>> m_JoysticksEvents;

			std::vector<int> m_JoysticksIDs1;
			std::vector<int> m_JoystickButtons1;
			std::vector<std::function<bool(int, int)>> m_JoysticksConditions1;
			std::vector<std::function<void()>> m_JoysticksEvents1;

			std::vector<int> m_JoystickAxisIDs;
			std::vector<int> m_JoystickAxisAxis;
			std::vector<std::function<bool(int, int)>> m_JoystickAxisConditions;
			std::vector<std::function<void(float)>> m_JoystickAxisEvents;

			unsigned int m_ID = 0;

		public:
			
			EventListener();
			~EventListener();

			void StartEventListener();
			void EndEventListener();

			void EventStep();

			void AddKeysEventListener(SDL_KeyCode key, std::function<bool(SDL_Keycode)> conditionalFunction, std::function<void()> executeFunction);
			void RemoveEventListener(SDL_KeyCode key);

			void AddKeysEventListener1(SDL_KeyCode key, std::function<bool(SDL_Keycode)> conditionalFunction, std::function<void()> executeFunction);
			void RemoveEventListener1(SDL_KeyCode key);

			void AddJoyEventListener(int joystickID, int button, std::function<bool(int, int)> conditionalFunction, std::function<void()> executeFunction);
			void RemoveJoyEventListener(int joystickID, int button);

			void AddJoyEventListener1(int joystickID, int button, std::function<bool(int, int)> conditionalFunction, std::function<void()> executeFunction);
			void RemoveJoyEventListener1(int joystickID, int button);

			void AddJoyAxisEventListener(int joystickID, int axis, std::function<bool(int, int)> conditionalFunction, std::function<void(float)> executeFunction);
			void RemoveJoyAxisEventListener(int joystickID);

			bool operator==(const EventListener& other);

			void DestroySelf();

		};
	}
}