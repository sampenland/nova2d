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
				Graver& graver = *m_AllGravers[i];

				// Clear all effected graver mags so that they can be reset
				for (size_t effGravIdx = 0; effGravIdx < graver.m_EffectedGravers.size(); effGravIdx++)
				{
					Graver& effGraver = *graver.m_EffectedGravers[effGravIdx];
					effGraver.m_GraverInfluencedMag = Vec2Int(0, 0);
				}

				// Sum mag
				for (size_t effGravIdx = 0; effGravIdx < graver.m_EffectedGravers.size(); effGravIdx++)
				{
					Graver& effGraver = *graver.m_EffectedGravers[effGravIdx];
					
					if (!graver.GraverWithinEffect(effGraver))continue; // skip if out of range

					switch (graver.m_GraverType)
					{
					case GraverType::Explosion:
						break;

					case GraverType::Implosion:
						break;

					case GraverType::XPushY:
						break;

					case GraverType::YPushX:
						break;

					case GraverType::Vec2Force:
					default:
						effGraver.m_GraverInfluencedMag += graver.m_GraverEffectMagnitude;
						break;
					}
					
				}

			}

		}
	}
}