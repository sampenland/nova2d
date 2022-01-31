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

		public:

			unsigned int m_ID = 0;
			bool m_Enabled = false;
			DrawCircle* m_EffectCircle = nullptr;
			Rect* m_EffectRectHolder = nullptr;
			DrawRect* m_EffectRect = nullptr;
			int m_EffectRadius = 2;
			float m_TimeEffect = 1.0f;
			bool m_IsCircleEffect = true;

		protected:
		public:

			TimeEffector(Vec2Int position, float timeEffect, int effectRadius, Rect effectRect, TimeEffectorType type);
			
			void ConfigureTimeEffector(float timeEffect);

			void ConfigureTimeEffectorVisible(bool filled, std::string fillColor, 
				std::string outlineColor, char layer);

			void TimeEffectorUpdate();
			void DestroySelf();

			bool TimeEffectedWithinEffect(const TimeEffected& effected);

		};
	}
}