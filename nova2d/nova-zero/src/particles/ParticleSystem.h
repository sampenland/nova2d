#pragma once
#include <Box2D.h>
#include <vector>
#include "../maths/Maths.h"
#include "../graphics/Color.h"

namespace novazero
{
	namespace particles
	{
		using namespace maths;
		using namespace graphics;

		class ParticleSystem
		{

		private:

			b2ParticleSystem* m_System = nullptr;
			std::vector<int32> m_ParticleIndices;

			int32 m_MaxParticles = 100;

			bool m_UsingLifetime = true;
			float m_MinLifeTime = 1.f;
			float m_MaxLifeTime = 100.f;

		public:

			ParticleSystem(int32 maxParticles, float particleRadius);

			int32 CreateParticle(b2ParticleFlag type, Vec2 position, Vec2 velocity, Color color);
			void DestroyParticle(int32 index);

			void SetLifetime(float min, float max);

			void DestroySelf();

		};
	}
}