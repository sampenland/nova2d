#pragma once
#include <string>

namespace novazero
{
	namespace physics
	{

		class TimeEffector
		{

		private:

			unsigned int m_CleanID = 0;

		public:

			unsigned int m_ID = 0;
			int m_BubbleEffectRadius = 2;
			bool m_Enabled = false;

			float m_TimeEffect = 1.0f;

		protected:
			TimeEffector();
		public:

			void ConfigureTimeEffector(float timeEffect);

			void ConfigureTimeEffectorVisible(bool filled, std::string fillColor, std::string outlineColor,
				int radius, char layer);

			void TimeEffectorUpdate();
			void DestroySelf();

			bool TimeEffectorWithinEffect(const TimeEffector& effector);

		};
	}
}