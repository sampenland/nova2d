#include "TimeEffector.h"
#include "../core/Game.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;

		TimeEffector::TimeEffector(Vec2 position, float timeEffect, int effectRadius, 
			Rect effectRect, TimeEffectorType type) : Deleteable("timeEffector_")
		{
			m_ID = n2dGameGetID();
			m_DeleteName = "timeEffector_" + std::to_string(m_ID);
			m_TimeEffect = timeEffect;
			m_EffectRadius = (float)effectRadius;
			
			m_IsCircleEffect = type == TimeEffectorType::Circle;

			SetPosition(position);

			m_EffectRectHolder = new Rect(effectRect.x, effectRect.y, effectRect.w, effectRect.h);

			m_CleanID = n2dAddDeleteable(this);
			SetEnabled(true);

			Game::s_SceneManager->s_TimeEffectorManager->AddEffector(this);
		}

		void TimeEffector::ConfigureTimeEffector(float timeEffect)
		{
			m_TimeEffect = timeEffect;
		}

		void TimeEffector::ConfigureTimeEffectorVisible(bool filled, const std::string& fillColor,
			const std::string& outlineColor, char layer)
		{
			if (m_IsCircleEffect)
			{
				if (m_EffectCircle)
					m_EffectCircle->DestroySelf();

				m_EffectCircle = new DrawCircle(fillColor, outlineColor, filled, m_Position, (int)m_EffectRadius, layer);
			}
			else
			{
				if (m_EffectRect)
					m_EffectRect->DestroySelf();

				m_EffectRect = new DrawRect(fillColor, outlineColor, filled, Rect((float)m_Position.x, (float)m_Position.y, m_EffectRectHolder->w, m_EffectRectHolder->h), 2, layer);
				m_EffectRect->SetSize(Vec2Int((int)m_EffectRectHolder->w, (int)m_EffectRectHolder->h));
			}			
		}

		void TimeEffector::ReDrawIfNeeded()
		{
			if (m_IsCircleEffect)
			{
				if (m_EffectCircle->GetDrawCircleRadius() != m_EffectRadius)
				{
					m_EffectCircle->SetDrawCircleRadius((int)m_EffectRadius);
				}
			}
			else
			{
				if (m_EffectRect->GetDrawRectSize().x != m_EffectRectHolder->x ||
					m_EffectRect->GetDrawRectSize().y != m_EffectRectHolder->y)
				{
					m_EffectRect->SetDrawRectSize(m_EffectRectHolder);
				}
			}
		}

		void TimeEffector::TimeEffectorUpdate()
		{
			if (!IsEnabled()) return;

			if(m_EffectCircle)
				m_EffectCircle->SetPositionInt(m_Position);

			if(m_EffectRect)
				m_EffectRect->SetPositionInt(m_Position);

			ReDrawIfNeeded();

		}

		bool TimeEffector::TimeEffectedWithinEffect(const TimeEffected& effected)
		{
			Vec2 otherCenter = effected.m_Physical->GetCenter();
			Vec2 selfCenter = GetCenter();

			if (m_IsCircleEffect)
			{
				return std::pow(otherCenter.x - selfCenter.x, 2) +
					std::pow(otherCenter.y - selfCenter.y, 2) < std::pow(m_EffectRadius, 2);
			}
			else
			{
				return (otherCenter.x > m_EffectRect->GetX() &&
					otherCenter.x < m_EffectRect->GetX() + m_EffectRect->GetWidth() &&
					otherCenter.y > m_EffectRect->GetY() &&
					otherCenter.y < m_EffectRect->GetY() + m_EffectRect->GetHeight());
			}
		}

		void TimeEffector::DestroySelf()
		{
			if (m_Destroyed) return;

			m_Destroyed = true;

			if (m_EffectCircle)
				m_EffectCircle->DestroySelf();

			if (m_EffectRect)
				m_EffectRect->DestroySelf();

			CleanUpdaters();
			Game::s_SceneManager->s_TimeEffectorManager->RemoveEffector(this);
			n2dRemoveDeleteable(m_CleanID);

			SetDeleted(true);
		}
	}
}