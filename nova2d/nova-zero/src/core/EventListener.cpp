#include "EventListener.h"
#include "Game.h"

namespace novazero
{
	namespace core
	{
		EventListener::EventListener()
			: Deleteable("eventListener"), m_ID(0)
		{
			m_ID = n2dGameGetID();

			m_DeleteName = "eventListener_" + std::to_string(m_ID);

			StartEventListener();

		}

		EventListener::~EventListener()
		{
			
		}

		void EventListener::DestroySelf()
		{
			EndEventListener();
			m_DeleteNow = 1;
		}

		void EventListener::StartEventListener()
		{
 			auto cleanID = n2dAddUpdater(EventListener::EventStep, this);
			m_CleanUpdaters.push_back(cleanID);
		}

		void EventListener::EndEventListener()
		{
			CleanUpdaters();
		}

		void EventListener::EventStep()
		{
			for (size_t i = 0; i < m_KeysConditions.size(); i++)
			{
				if (m_KeysConditions[i](m_KeyCodes[i]) == true)
				{
					m_KeysEvents[i]();
				}
			}

			for (size_t i = 0; i < m_JoysticksConditions.size(); i++)
			{
				if (m_JoysticksConditions[i](m_JoysticksIDs[i], m_JoystickButtons[i]) == true)
				{
					m_JoysticksEvents[i]();
				}
			}

			for (size_t i = 0; i < m_JoystickAxisConditions.size(); i++)
			{
				m_JoystickAxisEvents[i](m_JoystickAxisConditions[i](m_JoystickAxisIDs[i], m_JoystickAxisAxis[i]));
			}

		}

		void EventListener::AddKeysEventListener(SDL_KeyCode key, f_ConditionalFunction conditionalFunction, f_VoidFunction executeFunction)
		{
			if (m_KeyCodes.end() != std::find(m_KeyCodes.begin(), m_KeyCodes.end(), key))
			{
				return;
			}

			m_KeyCodes.push_back(key);
			m_KeysConditions.push_back(conditionalFunction);
			m_KeysEvents.push_back(executeFunction);
		}
		
		void EventListener::RemoveEventListener(SDL_KeyCode key)
		{
			int idx = -1;
			for (size_t i = 0; i < m_KeyCodes.size(); i++)
			{
				if (m_KeyCodes[i] == key)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1) return;

			m_KeyCodes.erase(m_KeyCodes.begin() + idx);
			m_KeysConditions.erase(m_KeysConditions.begin() + idx);
			m_KeysEvents.erase(m_KeysEvents.begin() + idx);

		}

		void EventListener::AddJoyEventListener(int joystickID, int button, f_JoyStickConditionalFunction conditionalFunction, f_VoidFunction executeFunction)
		{
			if (m_JoysticksIDs.end() != std::find(m_JoysticksIDs.begin(), m_JoysticksIDs.end(), joystickID))
			{
				return;
			}

			m_JoysticksIDs.push_back(joystickID);
			m_JoystickButtons.push_back(button);
			m_JoysticksConditions.push_back(conditionalFunction);
			m_JoysticksEvents.push_back(executeFunction);
		}

		void EventListener::RemoveJoyEventListener(int joystickID)
		{
			int idx = -1;
			for (size_t i = 0; i < m_JoysticksIDs.size(); i++)
			{
				if (m_JoysticksIDs[i] == joystickID)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1) return;

			m_JoysticksIDs.erase(m_JoysticksIDs.begin() + idx);
			m_JoystickButtons.erase(m_JoystickButtons.begin() + idx);
			m_JoysticksConditions.erase(m_JoysticksConditions.begin() + idx);
			m_JoysticksEvents.erase(m_JoysticksEvents.begin() + idx);

		}

		void EventListener::AddJoyAxisEventListener(int joystickID, JoystickAxis axis, f_JoyStickAxisConditionalFunction conditionalFunction, f_FloatPassFunction executeFunction)
		{
			if (m_JoysticksIDs.end() != std::find(m_JoysticksIDs.begin(), m_JoysticksIDs.end(), joystickID))
			{
				return;
			}

			m_JoystickAxisIDs.push_back(joystickID);
			m_JoystickAxisAxis.push_back(axis);
			m_JoystickAxisConditions.push_back(conditionalFunction);
			m_JoystickAxisEvents.push_back(executeFunction);
		}

		void EventListener::RemoveJoyAxisEventListener(int joystickID)
		{
			int idx = -1;
			for (size_t i = 0; i < m_JoystickAxisIDs.size(); i++)
			{
				if (m_JoystickAxisIDs[i] == joystickID)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1) return;

			m_JoystickAxisIDs.erase(m_JoystickAxisIDs.begin() + idx);
			m_JoystickAxisAxis.erase(m_JoystickAxisAxis.begin() + idx);
			m_JoystickAxisConditions.erase(m_JoystickAxisConditions.begin() + idx);
			m_JoystickAxisEvents.erase(m_JoystickAxisEvents.begin() + idx);

		}

		bool EventListener::operator==(const EventListener& other)
		{
			return m_ID == other.m_ID;
		}
	}
}