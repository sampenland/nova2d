#pragma once
#include "../core/Defines.h"

namespace novazero
{
	namespace utils
	{
		// easings.net //
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
			EaseInOutv,

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
				return 1 - std::cos((x * PI) / 2);
			}

			static float EaseOutSine(float x)
			{
				return std::sin((x * PI) / 2);
			}
			
			static float EaseInOutSine(float x)
			{
				return -(std::cos(PI * x) - 1) / 2;
			}
			
			static float EaseInQuad(float x)
			{
				return x * x;
			}
			
			static float EaseOutQuad(float x)
			{
				return 1 - (1 - x) * (1 - x);
			}
			
			static float EaseInOutQuad(float x)
			{
				return x < 0.5 ? 2 * x * x : 1 - pow(-2 * x + 2, 2) / 2;
			}

			static float EaseInCubic(float x)
			{
				return x * x * x;
			}

			static float EaseOutCubic(float x)
			{
				return 1 - pow(1 - x, 3);
			}

			static float EaseInOutCubic(float x)
			{
				return x < 0.5 ? 4 * x * x * x : 1 - pow(-2 * x + 2, 3) / 2;
			}

			static float EaseInQuart(float x)
			{
				return x * x * x * x;
			}

			static float EaseOutQuart(float x)
			{
				return 1 - pow(1 - x, 4);
			}

			static float EaseInOutQuart(float x)
			{
				return x < 0.5 ? 8 * x * x * x * x : 1 - pow(-2 * x + 2, 4) / 2;
			}

			static float EaseInQuint(float x)
			{
				return x * x * x * x * x;
			}

			static float EaseOutQuint(float x)
			{
				return 1 - pow(1 - x, 5);
			}

			static float EaseInOutQuint(float x)
			{
				return x < 0.5 ? 16 * x * x * x * x * x : 1 - pow(-2 * x + 2, 5) / 2;
			}

			static float EaseInExpo(float x)
			{
				return x == 0 ? 0 : pow(2, 10 * x - 10);
			}

			static float EaseOutExpo(float x)
			{
				return x == 1 ? 1 : 1 - pow(2, -10 * x);
			}

			static float EaseInOutExpo(float x)
			{
				return x == 0
					? 0
					: x == 1
					? 1
					: x < 0.5 ? pow(2, 20 * x - 10) / 2
					: (2 - pow(2, -20 * x + 10)) / 2;
			}

			static float EaseInCirc(float x)
			{
				return 1 - sqrt(1 - pow(x, 2));
			}

			static float EaseOutCirc(float x)
			{
				return sqrt(1 - pow(x - 1, 2));
			}

			static float EaseInOutCirc(float x)
			{
				return x < 0.5
					? (1 - sqrt(1 - pow(2 * x, 2))) / 2
					: (sqrt(1 - pow(-2 * x + 2, 2)) + 1) / 2;
			}

			static float EaseInBack(float x)
			{
				const float c1 = 1.70158;
				const float c3 = c1 + 1;

				return c3 * x * x * x - c1 * x * x;
			}

			static float EaseOutBack(float x)
			{
				const float c1 = 1.70158;
				const float c3 = c1 + 1;

				return 1 + c3 * pow(x - 1, 3) + c1 * pow(x - 1, 2);
			}

			static float EaseInOutBack(float x)
			{
				const float c1 = 1.70158;
				const float c2 = c1 * 1.525;

				return x < 0.5
					? (pow(2 * x, 2) * ((c2 + 1) * 2 * x - c2)) / 2
					: (pow(2 * x - 2, 2) * ((c2 + 1) * (x * 2 - 2) + c2) + 2) / 2;
			}

			static float EaseInElastic(float x)
			{
				const float c4 = (2 * PI) / 3;

				return x == 0
					? 0
					: x == 1
					? 1
					: -pow(2, 10 * x - 10) * sin((x * 10 - 10.75) * c4);
			}

			static float EaseOutElastic(float x)
			{
				const float c4 = (2 * PI) / 3;

				return x == 0
					? 0
					: x == 1
					? 1
					: pow(2, -10 * x) * sin((x * 10 - 0.75) * c4) + 1;
			}

			static float EaseInOutElastic(float x)
			{
				const float c5 = (2 * PI) / 4.5;

				return x == 0
					? 0
					: x == 1
					? 1
					: x < 0.5
					? -(pow(2, 20 * x - 10) * sin((20 * x - 11.125) * c5)) / 2
					: (pow(2, -20 * x + 10) * sin((20 * x - 11.125) * c5)) / 2 + 1;
			}

			static float EaseOutBounce(float x)
			{
				const float n1 = 7.5625;
				const float d1 = 2.75;

				if (x < 1 / d1) {
					return n1 * x * x;
				}
				else if (x < 2 / d1) {
					return n1 * (x -= 1.5 / d1) * x + 0.75;
				}
				else if (x < 2.5 / d1) {
					return n1 * (x -= 2.25 / d1) * x + 0.9375;
				}
				else {
					return n1 * (x -= 2.625 / d1) * x + 0.984375;
				}
			}

			static float EaseInBounce(float x)
			{
				return 1 - EaseOutBounce(1 - x);
			}

			static float EaseInOutBounce(float x)
			{
				return x < 0.5
					? (1 - EaseOutBounce(1 - 2 * x)) / 2
					: (1 + EaseOutBounce(2 * x - 1)) / 2;
			}




		};
	}
}