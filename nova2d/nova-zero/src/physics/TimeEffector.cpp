#include "TimeEffector.h"
#include "../core/Game.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;

		TimeEffector::TimeEffector(Vec2Int position, float timeEffect, int effectRadius) : Deleteable("timeEffector_")
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "timeEffector_" + std::to_string(m_ID);
			m_TimeEffect = timeEffect;
			m_EffectRadius = effectRadius;

			SetPosition(position);

			m_CleanID = n2dAddDeleteable(this);
			SetEnabled(true);

			Game::s_SceneManager->s_TimeEffectorManager->AddEffector(this);
		}

		void TimeEffector::ConfigureTimeEffector(float timeEffect)
		{
			m_TimeEffect = timeEffect;
		}

		void TimeEffector::ConfigureTimeEffectorVisible(bool filled, std::string fillColor, 
			std::string outlineColor, char layer)
		{
			if (m_EffectCircle)
				m_EffectCircle->DestroySelf();

			m_EffectCircle = new DrawCircle(fillColor, outlineColor, filled,
				m_Position.x, m_Position.y, m_EffectRadius, layer);
		}

		void TimeEffector::TimeEffectorUpdate()
		{
			if (!IsEnabled()) return;

			m_EffectCircle->SetPosition(m_Position);

		}

		bool TimeEffector::TimeEffectedWithinEffect(const TimeEffected& effected)
		{
			Vec2Int otherCenter = effected.m_Physical->GetCenter();
			Vec2Int selfCenter = GetCenter();

			return std::pow(otherCenter.x - selfCenter.x, 2) +
				std::pow(otherCenter.y - selfCenter.y, 2) < std::pow(m_EffectRadius, 2);
		}

		void TimeEffector::DestroySelf()
		{
			if (m_EffectCircle)
				m_EffectCircle->DestroySelf();

			CleanUpdaters();
			Game::s_SceneManager->s_TimeEffectorManager->RemoveEffector(this);
			n2dRemoveDeleteable(m_CleanID);

			m_DeleteNow = 1;
		}
	}
}