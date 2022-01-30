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

		void GraverManager::ClearGravers()
		{
			for (size_t i = 0; i < m_AllGravers.size(); i++)
			{
				m_AllGravers[i]->DestroySelf();
			}
			m_AllGravers.clear();
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
					
					if (!graver.GraverWithinEffect(effGraver)) continue; // skip if out of range

					Vec2Int moveBy(0, 0);
					switch (graver.m_GraverType)
					{
					case GraverType::Explosion:
						
						moveBy = Vec2Int(0, 0);

						if (graver.m_Physical->GetX() < effGraver.m_Physical->GetX())
						{
							moveBy.x = graver.m_GraverEffectMagnitude.x;
						}
						else
						{
							moveBy.x = -graver.m_GraverEffectMagnitude.x;
						}

						if (graver.m_Physical->GetY() < effGraver.m_Physical->GetY())
						{
							moveBy.y = graver.m_GraverEffectMagnitude.x;
						}
						else
						{
							moveBy.y = -graver.m_GraverEffectMagnitude.x;
						}

						break;

					case GraverType::Implosion:
						
						moveBy = Vec2Int(0, 0);

						if (graver.m_Physical->GetX() < effGraver.m_Physical->GetX())
						{
							moveBy.x = -graver.m_GraverEffectMagnitude.x;
						}
						else
						{
							moveBy.x = graver.m_GraverEffectMagnitude.x;
						}

						if (graver.m_Physical->GetY() < effGraver.m_Physical->GetY())
						{
							moveBy.y = -graver.m_GraverEffectMagnitude.x;
						}
						else
						{
							moveBy.y = graver.m_GraverEffectMagnitude.x;
						}

						break;

					case GraverType::Vec2Force:
					default:
						moveBy = graver.m_GraverEffectMagnitude;
						break;
					}

					effGraver.m_GraverInfluencedMag += moveBy;
					
				}

			}

		}
	}
}