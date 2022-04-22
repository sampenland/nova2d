#pragma once
#include <Box2D.h>
#include <vector>
#include "../maths/Maths.h"
#include "../graphics/Color.h"
#include "../graphics/Sprite.h"

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
			std::map<int32, Sprite*> m_Particles;

			std::string m_ParticleAssetName = "";
			Vec2Int m_AssetSize = Vec2Int(0, 0);

			int32 m_MaxParticles = 100;

			bool m_UsingLifetime = true;
			float m_MinLifeTime = 1.f;
			float m_MaxLifeTime = 100.f;

			unsigned char m_Layer = 4;

		public:

			ParticleSystem(const std::string& spriteTexture, Vec2Int size, 
				int32 maxParticles, float particleRadius, unsigned char layer);

			int32 CreateParticle(b2ParticleFlag type, Vec2 position, Vec2 velocity, Color color);
			void RemoveParticle(int32 index);

			void BurstParticles(int32 particleCount, Vec2 burstPosition, Vec2 velocity);
			void Update();
			void SetLifetime(float min, float max);

			int ParticleCount();

			void DestroySelf();

		};
	}
}