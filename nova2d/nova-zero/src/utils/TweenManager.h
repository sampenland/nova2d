#pragma once
#include <map>
#include <vector>

namespace novazero
{
	namespace maths
	{
		struct Tween
		{
			float start;
			float end;
			float step;
			float durationLeft;
			int* intPropertyEffected;
			float* floatPropertyEffected;
			bool isFloat;
		};

		class TweenManager
		{

		private:

			std::map<unsigned int, Tween*> m_Timers;
			unsigned int m_CleanID = 0;

		public:

			TweenManager();

			void AddTweenInt(int* propertyEffected, float start, float end, float durationMS);
			void AddTweenFloat(float* propertyEffected, float start, float end, float durationMS);
			void Update();

			void ClearTweens();

			int GetTweenCount() const { return (int)m_Timers.size(); }

		};
	}
}