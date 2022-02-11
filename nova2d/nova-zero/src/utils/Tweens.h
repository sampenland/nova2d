#pragma once
#include "../core/Defines.h"
#include <cmath>

namespace novazero
{
	namespace utils
	{
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

		class Tweens
		{
		private:

			Tweens() {};

		public:

			static float EaseInSine(float x)
			{
				return 1.f - std::cos((x * PI) / 2.f);
			}

			static float EaseOutSine(float x)
			{
				return std::sin((x * PI) / 2.f);
			}
			
			static float EaseInOutSine(float x)
			{
				return -(std::cos(PI * x) - 1.f) / 2.f;
			}
			
			static float EaseInQuad(float x)
			{
				return x * x;
			}
			
			static float EaseOutQuad(float x)
			{
				return 1.f - (1.f - x) * (1.f - x);
			}
			
			static float EaseInOutQuad(float x)
			{
				return x < 0.5f ? 2.f * x * x : 1.f - pow(-2.f * x + 2.f, 2.f) / 2.f;
			}

			static float EaseInCubic(float x)
			{
				return x * x * x;
			}

			static float EaseOutCubic(float x)
			{
				return 1.f - pow(1.f - x, 3.f);
			}

			static float EaseInOutCubic(float x)
			{
				return x < 0.5f ? 4.f * x * x * x : 1.f - pow(-2.f * x + 2.f, 3.f) / 2.f;
			}

			static float EaseInQuart(float x)
			{
				return x * x * x * x;
			}

			static float EaseOutQuart(float x)
			{
				return 1.f - pow(1.f - x, 4.f);
			}

			static float EaseInOutQuart(float x)
			{
				return x < 0.5f ? 8.f * x * x * x * x : 1.f - pow(-2.f * x + 2.f, 4.f) / 2.f;
			}

			static float EaseInQuint(float x)
			{
				return x * x * x * x * x;
			}

			static float EaseOutQuint(float x)
			{
				return 1.f - pow(1.f - x, 5.f);
			}

			static float EaseInOutQuint(float x)
			{
				return x < 0.5f ? 16.f * x * x * x * x * x : 1.f - pow(-2.f * x + 2.f, 5.f) / 2.f;
			}

			static float EaseInExpo(float x)
			{
				return x == 0.f ? 0.f : pow(2.f, 10.f * x - 10.f);
			}

			static float EaseOutExpo(float x)
			{
				return x == 1.f ? 1.f : 1.f - pow(2.f, -10.f * x);
			}

			static float EaseInOutExpo(float x)
			{
				return x == 0.f
					? 0.f
					: x == 1.f
					? 1.f
					: x < 0.5f ? pow(2.f, 20.f * x - 10.f) / 2.f
					: (2.f - pow(2.f, -20.f * x + 10.f)) / 2.f;
			}

			static float EaseInCirc(float x)
			{
				return 1.f - sqrt(1.f - pow(x, 2.f));
			}

			static float EaseOutCirc(float x)
			{
				return sqrt(1.f - pow(x - 1.f, 2.f));
			}

			static float EaseInOutCirc(float x)
			{
				return x < 0.5f
					? (1.f - sqrt(1.f - pow(2.f * x, 2.f))) / 2.f
					: (sqrt(1.f - pow(-2.f * x + 2.f, 2.f)) + 1.f) / 2.f;
			}

			static float EaseInBack(float x)
			{
				const float c1 = 1.70158f;
				const float c3 = c1 + 1.f;

				return c3 * x * x * x - c1 * x * x;
			}

			static float EaseOutBack(float x)
			{
				const float c1 = 1.70158f;
				const float c3 = c1 + 1.f;

				return 1.f + c3 * pow(x - 1.f, 3.f) + c1 * pow(x - 1.f, 2.f);
			}

			static float EaseInOutBack(float x)
			{
				const float c1 = 1.70158f;
				const float c2 = c1 * 1.525f;

				return x < 0.5f
					? (pow(2.f * x, 2.f) * ((c2 + 1.f) * 2.f * x - c2)) / 2.f
					: (pow(2.f * x - 2.f, 2.f) * ((c2 + 1.f) * (x * 2.f - 2.f) + c2) + 2.f) / 2.f;
			}

			static float EaseInElastic(float x)
			{
				const float c4 = (2.f * PI) / 3.f;

				return x == 0.f
					? 0.f
					: x == 1.f
					? 1.f
					: -pow(2.f, 10.f * x - 10.f) * sin((x * 10.f - 10.75f) * c4);
			}

			static float EaseOutElastic(float x)
			{
				const float c4 = (2.f * PI) / 3.f;

				return x == 0.f
					? 0.f
					: x == 1.f
					? 1.f
					: pow(2.f, -10.f * x) * sin((x * 10.f - 0.75f) * c4) + 1.f;
			}

			static float EaseInOutElastic(float x)
			{
				const float c5 = (2 * PI) / 4.5f;

				return x == 0.f
					? 0.f
					: x == 1.f
					? 1.f
					: x < 0.5f
					? -(pow(2.f, 20.f * x - 10.f) * sin((20.f * x - 11.125f) * c5)) / 2.f
					: (pow(2.f, -20.f * x + 10.f) * sin((20.f * x - 11.125f) * c5)) / 2.f + 1.f;
			}

			static float EaseOutBounce(float x)
			{
				const float n1 = 7.5625f;
				const float d1 = 2.75f;

				if (x < 1.f / d1) {
					return n1 * x * x;
				}
				else if (x < 2.f / d1) {
					return n1 * (x -= 1.5f / d1) * x + 0.75f;
				}
				else if (x < 2.5f / d1) {
					return n1 * (x -= 2.25f / d1) * x + 0.9375f;
				}
				else {
					return n1 * (x -= 2.625f / d1) * x + 0.984375f;
				}
			}

			static float EaseInBounce(float x)
			{
				return 1.f - EaseOutBounce(1.f - x);
			}

			static float EaseInOutBounce(float x)
			{
				return x < 0.5f
					? (1.f - EaseOutBounce(1.f - 2.f * x)) / 2.f
					: (1.f + EaseOutBounce(2.f * x - 1.f)) / 2.f;
			}




		};
	}
}