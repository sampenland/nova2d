#pragma once
#include "Tweens.h"
#include <map>
#include <vector>
#include <functional>

namespace novazero
{
	namespace maths
	{
		struct Tween
		{
			std::function<float(float)> tweenEasingFunc = nullptr;

			float initStart = 0.f;
			float current = 0.f;
			float end = 0.f;
			float step = 0.f;
			float durationLeft = 0.f;
			int* intPropertyEffected;
			float* floatPropertyEffected;
			bool isFloat = true;
			bool loop = false;
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
			unsigned int AddTweenInt(TweenTypes type, int* propertyEffected, float start, float end, float durationMS, bool loop = false, bool autoDelete = false);
			unsigned int AddTweenFloat(TweenTypes type, float* propertyEffected, float start, float end, float durationMS, bool loop = false, bool autoDelete = false);

			void EnableTween(unsigned int tweenID, bool enabled, bool reset);
			void ResetTween(unsigned int tweenID);
			void RemoveTween(unsigned int tweenID);

			void Update();

			void SetTweenType(Tween& t, TweenTypes type);
			void FloatTween(std::map<unsigned int, Tween*>::iterator it);
			void IntTween(std::map<unsigned int, Tween*>::iterator it);

			void ClearTweens();

			int GetTweenCount() const { return (int)m_Timers.size(); }

		};
	}
}