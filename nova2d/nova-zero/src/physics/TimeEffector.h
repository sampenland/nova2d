#pragma once
#include <string>
#include "../debug/DrawCircle.h"
#include "../core/Deleteable.h"
#include "../physics/TimeEffected.h"
#include "../core/Positional.h"
#include "../debug/DrawRect.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;
		using namespace maths;
		using namespace debug;

		enum class TimeEffectorType
		{
			Circle,
			Rect
		};

		class TimeEffector :
			public Deleteable,
			public Positional
		{

		private:

			unsigned int m_CleanID = 0;
			bool m_Destroyed = false;

		public:

			unsigned int m_ID = 0;
			bool m_Enabled = false;
			DrawCircle* m_EffectCircle = nullptr;
			Rect* m_EffectRectHolder = nullptr;
			DrawRect* m_EffectRect = nullptr;
			float m_EffectRadius = 2.f;
			float m_TimeEffect = 1.0f;
			bool m_IsCircleEffect = true;

		protected:
		public:

			TimeEffector(Vec2 position, float timeEffect, int effectRadius, 
				Rect effectRect, TimeEffectorType type);
			
			void ConfigureTimeEffector(float timeEffect);

			void ConfigureTimeEffectorVisible(bool filled, const std::string& fillColor,
				const std::string& outlineColor, char layer);

			int* GetEffectorRadiusRef() 
			{ 
				if (m_EffectCircle)
				{
					return m_EffectCircle->GetDrawCircleRadiusRef();
				}
				return nullptr;
			}

			int GetEffectorRadius()
			{
				if (m_EffectCircle)
				{
					return m_EffectCircle->GetDrawCircleRadius();
				}
			}

			void TimeEffectorUpdate();
			void ReDrawIfNeeded();

			void DestroySelf();

			bool TimeEffectedWithinEffect(const TimeEffected& effected);

		};
	}
}