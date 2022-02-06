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
			float current;
			float end;
			float step;
			float durationLeft;
			int* intPropertyEffected;
			float* floatPropertyEffected;
			bool isFloat;
			bool loop;
			bool deleteOnComplete = true;
			bool enabled = true;
		};

		class TweenManager
		{

		private:

			std::map<unsigned int, Tween*> m_Timers;
			unsigned int m_CleanID = 0;

		public:

			TweenManager();

			void Reconfigure(unsigned int tweenID, float start, float end, float durationMS, bool loop, bool autodelete = true);
			unsigned int AddTweenInt(int* propertyEffected, float start, float end, float durationMS, bool loop = false, bool autoDelete = false);
			unsigned int AddTweenFloat(float* propertyEffected, float start, float end, float durationMS, bool loop = false, bool autoDelete = false);

			void EnableTween(unsigned int tweenID, bool enabled, bool reset);
			void ResetTween(unsigned int tweenID);
			void RemoveTween(unsigned int tweenID);

			void Update();

			void ClearTweens();

			int GetTweenCount() const { return (int)m_Timers.size(); }

		};
	}
}