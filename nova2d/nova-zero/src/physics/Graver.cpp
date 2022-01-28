#include "Graver.h"
#include "../core/Game.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;

		Graver::Graver() : Deleteable("graver") 
		{
			m_ID = n2dGameGetID();

			m_GraverEffectRadius = 1;
			m_GraverEffectMagnitude = Vec2Int(0, 0);
			m_GraverInfluencedMag = Vec2Int(0, 0);

			m_CleanID = n2dAddDeleteable(this);

			Game::s_SceneManager->s_GraverManager->AddGraver(this);
		};

		Graver::Graver(GraverType type, int effectRadius, 
			Vec2Int defaultGraverEffectMag, Positional* physicalHook) : Deleteable("graver")
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "graver_" + std::to_string(m_ID);
			
			m_GraverType = type;

			m_GraverEffectRadius = effectRadius;
			m_GraverEffectMagnitude = defaultGraverEffectMag;
			m_GraverInfluencedMag = Vec2Int(0, 0);
			m_Physical = physicalHook;

			m_CleanID = n2dAddDeleteable(this);

			Game::s_SceneManager->s_GraverManager->AddGraver(this);

		}

		void Graver::ConfigureGraver(GraverType type, int effectRadius, 
			Vec2Int defaultGraverEffectMag, Positional* physicalHook)
		{
			m_GraverType = type;

			m_GraverEffectRadius = effectRadius;
			m_GraverEffectMagnitude = defaultGraverEffectMag;
			m_GraverInfluencedMag = Vec2Int(0, 0);
			m_Physical = physicalHook;
		}

		void Graver::GraverUpdate()
		{
			if (m_Physical == nullptr)
			{
				LOG(LVL_NON_FATAL_ERROR, "Graver has no Positional Hook: " + m_DeleteName);
				return;
			}

			Vec2Int currentPos = m_Physical->GetPosition();
			m_Physical->SetPosition(currentPos + m_GraverInfluencedMag);
		}

		void Graver::AddEffectedGraver(Graver* graver)
		{
			m_EffectedGravers.push_back(graver);
		}

		void Graver::RemoveEffectedGraver(Graver* graver)
		{
			int idx = -1;
			for (size_t i = 0; i < m_EffectedGravers.size(); i++)
			{
				if (m_EffectedGravers[i]->m_ID == graver->m_ID)
				{
					idx = i;
					break;
				}
			}

			if (idx != -1)
			{
				m_EffectedGravers.erase(m_EffectedGravers.begin() + idx);
			}
		}

		bool Graver::GraverWithinEffect(const Graver& graver)
		{
			Positional& hook = *graver.m_Physical;

			Vec2Int otherCenter = hook.GetCenter();
			Vec2Int selfCenter = m_Physical->GetCenter();

			return ((otherCenter.x - selfCenter.x) ^ 2 + (otherCenter.y - selfCenter.y) ^ 2) < (m_GraverEffectRadius ^ 2);
		}

		Graver::~Graver()
		{
			
		}

		void Graver::DestroySelf()
		{
			n2dRemoveDeleteable(m_CleanID);
			Game::s_SceneManager->s_GraverManager->RemoveGraver(this);
			CleanUpdaters();
			m_DeleteNow = 1;
		}
	}
}