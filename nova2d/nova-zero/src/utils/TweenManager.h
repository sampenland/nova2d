#pragma once
#include "Tweens.h"
#include <map>
#include <vector>
#include <functional>

namespace novazero
{
	namespace maths
	{
		using namespace utils;

		class Tween;

		class TweenManager
		{

		private:

			std::map<unsigned int, Tween*> m_Tweens;
			unsigned int m_CleanID = 0;

		public:

			TweenManager();

			void Reconfigure(unsigned int tweenID, float start, float end, float durationMS, bool loop, bool autodelete = true);
			unsigned int AddTween(float* propertyEffected, float start, float end, float durationMS, bool loop = false, bool autoDelete = false, TweenTypes type = TweenTypes::EaseInCubic);

			void EnableTween(unsigned int tweenID, bool enabled, bool reset);
			void ResetTween(unsigned int tweenID);
			void RemoveTween(unsigned int tweenID);

			void Update();

			void SetTweenType(Tween& t, TweenTypes type);
			void InterfaceToEasings(Tween& tween);

			void ClearTweens();

			int GetTweenCount() const { return (int)m_Tweens.size(); }

		};
	}
}