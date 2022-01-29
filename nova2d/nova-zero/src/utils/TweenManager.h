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
			void* propertyEffected;
		};

		class TweenManager
		{

		private:

			std::map<unsigned int, Tween*> m_Timers;
			unsigned int m_CleanID = 0;

		public:

			TweenManager();

			void AddTween(void* propertyEffected, float start, float end, float durationMS);
			void Update();

			void DestroySelf();

		};
	}
}