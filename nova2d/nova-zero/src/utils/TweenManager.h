#pragma once
#include <map>
#include <vector>

namespace novazero
{
	namespace maths
	{
		struct Tween
		{
			float initStart;
			float start;
			float end;
			float step;
			float durationLeft;
			int* intPropertyEffected;
			float* floatPropertyEffected;
			bool isFloat;
			bool loop;
		};

		class TweenManager
		{

		private:

			std::map<unsigned int, Tween*> m_Timers;
			unsigned int m_CleanID = 0;

		public:

			TweenManager();

			unsigned int AddTweenInt(int* propertyEffected, float start, float end, float durationMS, bool loop = false);
			unsigned int AddTweenFloat(float* propertyEffected, float start, float end, float durationMS, bool loop = false);

			void RemoveTween(unsigned int tweenID);

			void Update();

			void ClearTweens();

			int GetTweenCount() const { return (int)m_Timers.size(); }

		};
	}
}