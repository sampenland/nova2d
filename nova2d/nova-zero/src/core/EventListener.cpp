#include "EventListener.h"

#include "../core/Game.h"

namespace novazero
{
	namespace core
	{
		EventListener::EventListener()
			: m_ID(0)
		{
			m_ID = Game::s_IDCount;
			Game::s_IDCount++;
		}

		EventListener::~EventListener()
		{

		}

		void EventListener::EventStep()
		{
			for (size_t i = 0; i < m_KeysConditions.size(); i++)
			{
				if (m_KeysConditions[i](m_KeysNames[i]) == true)
				{
					m_KeysEvents[i]();
				}
			}
		}

		void EventListener::AddKeysEventListener(SDL_KeyCode key, f_KeyConditionalFunction conditionalFunction, f_EventPtrFunction executeFunction)
		{
			m_KeysNames.push_back(key);
			m_KeysConditions.push_back(conditionalFunction);
			m_KeysEvents.push_back(executeFunction);
		}
		
		void EventListener::RemoveEventListener(SDL_KeyCode key)
		{
			int idx = -1;
			for (size_t i = 0; i < m_KeysNames.size(); i++)
			{
				if (m_KeysNames[i] == key)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1) return;

			m_KeysNames.erase(m_KeysNames.begin() + idx);
			m_KeysConditions.erase(m_KeysConditions.begin() + idx);
			m_KeysEvents.erase(m_KeysEvents.begin() + idx);

		}

		bool EventListener::operator==(const EventListener& other)
		{
			return m_ID == other.m_ID;
		}
	}
}