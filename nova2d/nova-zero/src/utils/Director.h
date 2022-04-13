#pragma once
#include "../input/ScrollInput.h"

namespace novazero
{
	namespace utils
	{
		using namespace input;

		class Director
		{

		private:

			ScrollInput* m_LightingSlider = nullptr;

		public:

			Director();

			void InitLighting();

			void Draw();

			void DestroySelf();
		};
	}
}