#pragma once
#include <map>
#include <vector>
#include <functional>

namespace novazero
{
	namespace utils
	{
		struct Tween
		{
			std::function<float(float)> tweenEasingFunc = nullptr;

			bool isFloat = true;

			float xStart = 0.f;
			float xStep = 0.f;
			float xCurrent = 0.0f;
			const float xEnd = 1.f;

			float durationMS = 1000.f;
			float initStart = 0.f;
			float end = 0.f;
			float current = 0.f;
			float offset = 0.f;

			bool invert = false;
			bool negate = false;

			float* referenceF = nullptr;
			int* referenceI = nullptr;

			bool loop = false;
			float loopResetValue = 0.f;

			bool completed = false;
			bool deleteOnComplete = true;
			bool enabled = true;
		};

		// easings.net //
		// Tween-easing functions
		enum class TweenTypes
		{
			EaseInSine,
			EaseOutSine,
			EaseInOutSine,

			EaseInQuad,
			EaseOutQuad,
			EaseInOutQuad,

			EaseInCubic,
			EaseOutCubic,
			EaseInOutCubic,

			EaseInQuart,
			EaseOutQuart,
			EaseInOutQuart,

			EaseInQuint,
			EaseOutQuint,
			EaseInOutQuint,

			EaseInExpo,
			EaseOutExpo,
			EaseInOutExpo,

			EaseInCirc,
			EaseOutCirc,
			EaseInOutCirc,

			EaseInBack,
			EaseOutBack,
			EaseInOutBack,

			EaseInElastic,
			EaseOutElastic,
			EaseInOutElastic,

			EaseInBounce,
			EaseOutBounce,
			EaseInOutBounce

		};

		class TweenManager
		{

		private:

			std::map<unsigned int, Tween*> m_Tweens;
			unsigned int m_CleanID = 0;

		public:

			TweenManager();

			void Reconfigure(unsigned int tweenID, float start, float end, float durationMS, bool loop, bool autodelete = true);
			unsigned int AddTween(bool isFloat, void* propertyEffected, float start, float end, float durationMS, bool loop = false, bool autoDelete = false, TweenTypes type = TweenTypes::EaseInCubic);

			void EnableTween(unsigned int tweenID, bool enabled, bool reset);
			Tween& GetTween(unsigned int tweenID);
			void ResetTween(unsigned int tweenID);
			void ResetDuration(unsigned int tweenID, float durationMS);
			void SetTweenValue(unsigned int tweenID, float value);
			void SetTweenLoopValue(unsigned int tweenID, float valueBtw0And1);
			void RemoveTween(unsigned int tweenID);
			void RemoveOffset(unsigned int tweenID);

			void Update();

			void SetTweenType(Tween& t, TweenTypes type);
			void InterfaceToEasings(Tween& tween);

			void ClearTweens();

			int GetTweenCount() const { return (int)m_Tweens.size(); }

		};
	}
}