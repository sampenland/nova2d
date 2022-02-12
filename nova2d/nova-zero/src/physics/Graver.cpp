#include "Graver.h"
#include "../core/Game.h"
#include <cmath>

namespace novazero
{
	namespace physics
	{
		using namespace core;

		Graver::Graver() : Deleteable("graver") 
		{
			m_ID = n2dGameGetID();

			m_GraverEffectRadius = 1;
			m_GraverEffectMagnitude = Vec2(0, 0);
			m_GraverInfluencedMag = Vec2(0, 0);
			SetEnabled(false);

			m_CleanID = n2dAddDeleteable(this);

			Game::s_SceneManager->s_GraverManager->AddGraver(this);
		};

		// Graver Types:
		// implosion and explosion will use the vec2int.x value for strength
		// others use vec2int
		Graver::Graver(GraverType type, float effectRadius, 
			Vec2 defaultGraverEffectMag, Positional* physicalHook) : Deleteable("graver")
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "graver_" + std::to_string(m_ID);
			
			m_GraverType = type;

			m_GraverEffectRadius = effectRadius;
			m_GraverEffectMagnitude = defaultGraverEffectMag;
			m_GraverInfluencedMag = Vec2(0, 0);
			m_Physical = physicalHook;

			if (m_Physical)
				SetEnabled(true);
			else
				LOG(LVL_WARNING, "Graver hook is null, leaving disabled.");

			m_CleanID = n2dAddDeleteable(this);

			Game::s_SceneManager->s_GraverManager->AddGraver(this);

		}

		// Graver Types:
		// implosion and explosion will use the vec2int.x value for strength
		// others use vec2int
		void Graver::ConfigureGraver(GraverType type, float effectRadius, 
			Vec2 defaultGraverEffectMag, Positional* physicalHook)
		{
			m_GraverType = type;

			m_GraverEffectRadius = effectRadius;
			m_GraverEffectMagnitude = defaultGraverEffectMag;
			m_GraverInfluencedMag = Vec2(0, 0);
			m_Physical = physicalHook;

			if (m_Physical)
				SetEnabled(true);
			else
				LOG(LVL_WARNING, "Graver hook is null, leaving disabled.");

		}

		void Graver::GraverUpdate()
		{
			if (!IsEnabled()) return;

			if (m_Physical == nullptr)
			{
				LOG(LVL_NON_FATAL_ERROR, "Graver has no Positional Hook: " + m_DeleteName);
				return;
			}

			Vec2 currentPos = m_Physical->GetPosition();

			if (m_LookAtTarget && (m_GraverInfluencedMag.x > 0 || m_GraverInfluencedMag.y > 0))
			{
				Vec2Int currentPosInt = m_Physical->GetPositionInt();
				Vec2Int m_GraverInfluencedMagInt = Vec2Int((int)m_GraverInfluencedMag.x, (int)m_GraverInfluencedMag.y);
				int lookAtAngle = Vec2Int::LookAtAngle(currentPosInt,
					m_Physical->GetPositionInt() + m_GraverInfluencedMagInt, -90);

				m_Physical->GetLinkedSprite()->SetAngle(lookAtAngle);
			}

			float ix = (float)m_GraverInfluencedMag.x * n2dTimeScale;
			float iy = (float)m_GraverInfluencedMag.y * n2dTimeScale;
			m_GraverInfluencedMag = Vec2(ix, iy);
			m_Physical->SetPosition(currentPos + m_GraverInfluencedMag);
			
			if (m_EffectCircle)
				m_EffectCircle->SetPosition(m_Physical->GetCenter());

		}

		void Graver::ConfigureGraverVisible(bool filled, std::string fillColor, std::string outlineColor,
			float radius, char layer)
		{
			if (m_EffectCircle)
				m_EffectCircle->DestroySelf();

			m_EffectCircle = new DrawCircle(fillColor, outlineColor, filled, m_Physical->GetPosition(), radius, layer);

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

			Vec2 otherCenter = hook.GetCenter();
			Vec2 selfCenter = m_Physical->GetCenter();

			return std::pow(otherCenter.x - selfCenter.x, 2) +
				std::pow(otherCenter.y - selfCenter.y, 2) < std::pow(m_GraverEffectRadius, 2);
		}

		void Graver::DestroySelf()
		{
			if (m_Destroyed) return;
			m_Destroyed = true;

			n2dRemoveDeleteable(m_CleanID);
			Game::s_SceneManager->s_GraverManager->RemoveGraver(this);
			CleanUpdaters();
			
			if (m_EffectCircle)
				m_EffectCircle->DestroySelf();

			SetDeleted(true);
		}
	}
}