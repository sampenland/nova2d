#pragma once
#include "../graphics/Sprite.h"

namespace novazero
{
	namespace particles
	{
		class ParticleSystem;

		using namespace graphics;

		class Particle
		{

		private:

			int m_Index = 0;
			Sprite* m_Sprite = nullptr;
			ParticleSystem* m_PSystem = nullptr;

		public:

			Particle(Sprite* sprite, ParticleSystem* pSystem);

			void UpdatePosition(float x, float y);
			void SetIndex(int index);

			void DestroySelf();

		};
	}
}