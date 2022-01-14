#include "EventListener.h"

namespace novazero
{
	namespace core
	{
		void EventListener::EventStep()
		{
			for (int i = 0; i < m_Conditions.size(); i++)
			{
				if (m_Conditions[i]() == true)
				{
					m_Events[i]();
				}
			}
		}

		void EventListener::AddEventListener(const char* name, bool(*conditionalFuction)(), void(*executeFunction)())
		{
			m_Names.push_back(name);
			m_Conditions.push_back(conditionalFuction);
			m_Events.push_back(executeFunction);
		}

		void EventListener::RemoveEventListener(const char* name)
		{
			int idx = -1;
			for (int i = 0; i < m_Names.size(); i++)
			{
				if (m_Names[i] == name)
				{
					idx = i;
					break;
				}
			}

			if (idx == -1) return;

			m_Names.erase(m_Names.begin() + idx);
			m_Conditions.erase(m_Conditions.begin() + idx);
			m_Events.erase(m_Events.begin() + idx);

		}
	}
}