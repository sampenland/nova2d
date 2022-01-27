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

		void GraverManager::RemoveGraver(unsigned int id)
		{
			int idx = -1;
			for (size_t i = 0; i < m_AllGravers.size(); i++)
			{
				if (m_AllGravers[i]->m_ID == id)
				{
					m_AllGravers[i]->DestroySelf();
					return;
				}
			}
		}

		void GraverManager::Update()
		{
			SumGroups();
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