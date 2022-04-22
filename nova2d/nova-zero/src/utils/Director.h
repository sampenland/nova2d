#pragma once
#include "../input/ScrollInput.h"
#include "../core/Timer.h"

namespace novazero
{
	namespace utils
	{
		using namespace input;
		using namespace core;

		class Director
		{

		private:

			ScrollInput* m_LightingSlider = nullptr;
			Timer* m_FPSTimer = nullptr;
			bool* m_ShowParticleCount = new bool;

		public:

			Director();

			void InitLighting();

			void Draw();

			void DestroySelf();
		};
	}
}