#pragma once
#include <vector>

namespace novazero
{
	namespace core
	{
		class EventListener
		{

		protected:

			EventListener() {};

		private:

			std::vector<bool (*)()> m_Conditions;
			std::vector<void (*)()> m_Events;
			std::vector<const char*> m_Names;

		public:
			
			void EventStep();			
			void AddEventListener(const char* name, bool (*conditionalFuction)(), void (*executeFunction)());
			void RemoveEventListener(const char* name);

			virtual void Update() = 0;

		};
	}
}