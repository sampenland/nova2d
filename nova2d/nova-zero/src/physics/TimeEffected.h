#pragma once
#include "../core/Positional.h"

namespace novazero
{
	namespace physics
	{
		using namespace core;

		class TimeEffected
		{

		private:

			bool m_TimeEffectEnabled = true;
			float m_TimeInfluencedEffect = 1.0f;
			unsigned int m_CleanID = 0;

		protected:

			TimeEffected(Positional* physical)
			{
				m_Physical = physical;
			}
			TimeEffected();

		public:

			unsigned int m_ID = 0;
			Positional* m_Physical = nullptr;

			void ConfigureTimeEffected(Positional* positional)
			{
				if (m_Physical)
					delete m_Physical;
				m_Physical = positional;

				SetTimeEffectEnabled(true);
			}

			void SetTimeInfluence(float effect) { m_TimeInfluencedEffect = effect; }
			float GetTimeInfluence() { return m_TimeInfluencedEffect; }

			void SetTimeEffectEnabled(bool v) { m_TimeEffectEnabled = v; }
			bool IsTimeEffectEnabled() const { return m_TimeEffectEnabled; }

		};
	}
}