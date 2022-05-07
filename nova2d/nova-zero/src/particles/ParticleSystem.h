#pragma once
#include "Box2D/Box2D.h"
#include <vector>
#include "../maths/Maths.h"
#include "../graphics/Color.h"
#include "../particles/Particle.h"
#include "../graphics/Sprite.h"

namespace novazero
{
	namespace particles
	{
		using namespace maths;
		using namespace graphics;

		enum class ParticleCollisionTypes
		{
			ParticleToParticle = b2_particleContactFilterParticle,
			FixtureToParticle = b2_fixtureContactFilterParticle,
			None = -1
		};

		class ParticleSystem
		{

		private:

			// Save settings
			float m_EmitterSpeed;
			float* m_EmitVelocity;
			float* m_EmitSpread;
			bool* m_SingleExplode;
			char* m_AssetPath;
			const int MAX_ASSET_PATH = 200;
			Vec2Int* m_AssetSize;
			float m_BurstAngleMin;
			float m_BurstAngleMax;
			float m_Scale = 1.f;


		private:

			b2ParticleSystem* m_System = nullptr;

			Timer* m_EmitTimer = nullptr;
			bool m_EmitterEnabled = false;
			Vec2 m_BurstPosition = Vec2(0, 0);
			
			std::map<int, Particle*> m_Particles;
			std::string m_ParticleAssetName = "";

			int32 m_MaxParticles = 100;

			bool m_UsingLifetime = true;
			float m_MinLifeTime = 1.f;
			float m_MaxLifeTime = 100.f;

			unsigned char m_Layer = 4;

		public:

			ParticleSystem(const std::string& spriteTexture, Vec2Int size, 
				int32 maxParticles, float particleRadius, unsigned char layer);

			/*
				customFilter will make particles NOT collide with anything unless told to			
			*/
			int32 CreateParticle(b2ParticleFlag type, Vec2 position, 
				Vec2 velocity, Color color, bool customFilter);
			void RemoveParticle(int32 index);

			void BurstParticles(int32 particleCount, Vec2 burstPosition, float velocity, float spread, bool customFilter = true);
			void BurstParticles(int32 particleCount, Vec2 burstPosition, float velocity, float spread, 
				float minAngleDeg, float maxAngleDeg, bool customFilter = true);
			void Update();
			void SetLifetime(float minSeconds, float maxSeconds);

			void ConfigureEmitter(std::string assetPath, bool enableEmitter, float emitSpeed, 
				float emitVelocity, float emitSpread, Vec2 burstPosition);

			char* GetAssetPath();
			void SetScale(float scale);

			float GetEmitAngleMin();
			float GetEmitAngleMax();

			float* GetEmitAngleMinRef();
			float* GetEmitAngleMaxRef();

			float* GetEmitterSpeedRef();
			float* GetEmitterSpeed();

			float* GetMinLifeTimeRef();
			float* GetMaxLifeTimeRef();
			
			int32* GetMaxParticleRef();

			bool* GetEmitterEnabled();

			int32 ParticleCount();

			void DestroySelf();

		};
	}
}