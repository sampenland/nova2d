#include "TimeEffectorManager.h"

namespace novazero
{
	namespace physics
	{
		TimeEffectorManager::TimeEffectorManager()
		{

		}

		void TimeEffectorManager::AddEffector(TimeEffector* effector)
		{
			if (std::find(m_AllEffectors.begin(), m_AllEffectors.end(), effector) == m_AllEffectors.end())
			{
				m_AllEffectors.push_back(effector);
			}
		}

		void TimeEffectorManager::RemoveEffector(TimeEffector* effector)
		{
			int idx = -1;
			for (size_t i = 0; i < m_AllEffectors.size(); i++)
			{
				if (m_AllEffectors[i]->m_ID == effector->m_ID)
				{
					idx = i;
					break;
				}
			}

			if (idx != -1)
			{
				EffectorReset(idx);
				m_AllEffectors.erase(m_AllEffectors.begin() + idx);
			}
		}

		void TimeEffectorManager::ClearEffectors()
		{
			for (size_t i = 0; i < m_AllEffectors.size(); i++)
			{
				EffectorReset(i);
				m_AllEffectors[i]->DestroySelf();
			}
			m_AllEffectors.clear();
		}

		void TimeEffectorManager::AddEffected(TimeEffected* effector)
		{
			if (std::find(m_AllEffected.begin(), m_AllEffected.end(), effector) == m_AllEffected.end())
			{
				m_AllEffected.push_back(effector);
			}
		}

		void TimeEffectorManager::RemoveEffected(TimeEffected* effected)
		{
			int idx = -1;
			for (size_t i = 0; i < m_AllEffected.size(); i++)
			{
				if (m_AllEffected[i]->m_ID == effected->m_ID)
				{
					idx = i;
					break;
				}
			}

			if (idx != -1)
			{
				m_AllEffected.erase(m_AllEffected.begin() + idx);
			}
		}

		void TimeEffectorManager::EffectorReset(int index)
		{
			TimeEffector& effector = *m_AllEffectors[index];

			for (size_t j = 0; j < m_AllEffected.size(); j++)
			{
				TimeEffected& effected = *m_AllEffected[j];
				effected.SetTimeInfluence(1.0f);
			}
		}

		void TimeEffectorManager::ClearEffected()
		{
			m_AllEffected.clear();
		}

		void TimeEffectorManager::Update()
		{
			UpdateEffectors();
		}


		void TimeEffectorManager::UpdateEffectors()
		{
			for (size_t i = 0; i < m_AllEffectors.size(); i++)
			{
				TimeEffector& effector = *m_AllEffectors[i];

				if (!effector.IsEnabled()) continue;

				for (size_t j = 0; j < m_AllEffected.size(); j++)
				{
					TimeEffected& effected = *m_AllEffected[j];

					if (!effected.IsTimeEffectEnabled()) continue;

					if (effector.TimeEffectedWithinEffect(effected))
					{
						effected.SetTimeInfluence(effector.m_TimeEffect);
					}
					else
					{
						effected.SetTimeInfluence(1.0f);
					}
				}

			}
		}
	}
}