#include "GraverManager.h"

namespace novazero
{
	namespace physics
	{
		GraverManager::GraverManager()
		{

		}

		GraverManager::~GraverManager()
		{

		}

		void GraverManager::AddGraver(Graver* graver)
		{
			if (std::find(m_AllGravers.begin(), m_AllGravers.end(), graver) == m_AllGravers.end())
			{
				m_AllGravers.push_back(graver);
			}
		}

		void GraverManager::RemoveGraver(Graver* graver)
		{
			int idx = -1;
			for (size_t i = 0; i < m_AllGravers.size(); i++)
			{
				if (m_AllGravers[i]->m_ID == graver->m_ID)
				{
					idx = i;
					break;
				}
			}

			if (idx != -1)
			{
				m_AllGravers.erase(m_AllGravers.begin() + idx);
			}
		}

		void GraverManager::Update()
		{
			SumGroups();
			UpdateGravers();
		}

		void GraverManager::UpdateGravers()
		{
			for (size_t i = 0; i < m_AllGravers.size(); i++)
			{
				m_AllGravers[i]->GraverUpdate();
			}
		}

		void GraverManager::SumGroups()
		{
			m_GraverMags.clear();

			for (size_t i = 0; i < m_AllGravers.size(); i++)
			{
				m_GraverMags[m_AllGravers[i]->m_GraverGroupKeyID] += m_AllGravers[i]->m_GraverEffectMagnitude;
			}

		}
	}
}