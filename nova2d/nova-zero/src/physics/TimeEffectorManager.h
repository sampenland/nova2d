#pragma once
#include "TimeEffector.h"
#include "TimeEffected.h"

#include <map>
#include <vector>

namespace novazero
{
	namespace physics
	{
		class TimeEffectorManager
		{

		private:

			std::vector<TimeEffector*> m_AllEffectors;
			std::vector<TimeEffected*> m_AllEffected;

		public:

			TimeEffectorManager();

			void AddEffector(TimeEffector* effector);
			void RemoveEffector(TimeEffector* effector);
			void ClearEffectors();

			void AddEffected(TimeEffected* effected);
			void RemoveEffected(TimeEffected* effected);
			void ClearEffected();

			int GetEffectorCount() { return (int)m_AllEffectors.size(); }
			int GetEffectedCount() { return (int)m_AllEffected.size(); }

			void Update();
			void UpdateEffectors();

		};
	}
}