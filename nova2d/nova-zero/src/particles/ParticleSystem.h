#pragma once
#include "Box2D/Box2D.h"
#include <vector>
#include "../maths/Maths.h"
#include "../graphics/Color.h"
#include "../core/Timer.h"

namespace novazero
{
	namespace graphics
	{
		class Sprite;
	}

	namespace particles
	{
		using namespace novazero::core;
		using namespace novazero::maths;
		using namespace novazero::graphics;

		struct ParticleColorTransition
		{
			bool Enabled = false;
			bool StartToMid = true;
			Color Current;
			Color Start;
			Color Mid;
			Color End;
			float Speed = 1;
		};

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
			float* m_EmitSpread;
			bool* m_SingleExplode;
			char* m_AssetPath;
			const int MAX_ASSET_PATH = 200;
			Vec2Int* m_AssetSize;
			float m_BurstAngleMin;
			float m_BurstAngleMax;
			float m_Scale = 1.f;
			float m_EmitVelocity;

			bool m_UsingAlphaTransition = false;
			int m_StartAlpha = 255;
			int m_StartAlphaRnd = 0;
			int m_EndAlpha = 255;
			int m_EndAlphaRnd = 0;
			float m_AlphaChangeSpeed = 2.25f;

			bool m_UsingColorTransition = false;
			ParticleColorTransition m_ColorTransition;
			float m_StartColor[3];
			float m_MidColor[3];
			float m_EndColor[3];

		private:

			b2ParticleSystem* m_System = nullptr;

			Timer* m_EmitTimer = nullptr;
			bool m_EmitterEnabled = false;
			Vec2 m_BurstPosition = Vec2(0, 0);
			
			std::string m_ParticleAssetName = "";

			int32 m_MaxParticles = 100;

			bool m_UsingLifetime = true;

			float m_MinLifeTime = 1.f;
			float m_MaxLifeTime = 10.f;
			float m_ParticleRadius = 5.f;

			bool m_EditorFeatureOnly = false;

			unsigned char m_Layer = 4;

		public:

			ParticleSystem(const std::string& spriteTexture, Vec2Int size, 
				int32 maxParticles, float particleRadius, unsigned char layer);

			/*
				customFilter will make particles NOT collide with anything unless told to			
			*/
			int32 CreateParticle(b2ParticleFlag type, Vec2 position, 
				Vec2 velocity, ParticleColorTransition& colors, bool customFilter,
				Uint8 startAlpha = 255, Uint8 endAlpha = 255, float alphaChangeSpeed = 0.25f);
			
			void BurstParticles(int32 particleCount, Vec2 burstPosition, float velocity, float spread, bool customFilter = true);
			
			void BurstParticles(int32 particleCount, Vec2 burstPosition, float velocity, float spread, 
				float minAngleDeg, float maxAngleDeg, bool customFilter = true);
			
			void BurstSingleParticle(Vec2 burstPosition, int startAlpha, int endAlpha,
				float alphaChangeSpeed, float velocity, float spread,
				float minAngleDeg, float maxAngleDeg, ParticleColorTransition& colors, bool customFilter = true);
			
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

			float* GetEmitterVelocityRef();

			float* GetEmitterSpeedRef();
			float* GetEmitterSpeed();

			float* GetMinLifeTimeRef();
			float* GetMaxLifeTimeRef();
			
			float* GetParticleRadiusRef();

			bool* GetUsingAlphaTransitionRef();
			int* GetStartAlphaRef();
			int* GetStartAlphaRndRef();
			int* GetEndAlphaRef();
			int* GetEndAlphaRndRef();
			float* GetAlphaChangeSpeedRef();

			bool* GetUsingColorTransitionRef();
			ParticleColorTransition* GetColorTransitionRef();
			float* GetStartColorRef();
			float* GetMidColorRef();
			float* GetEndColorRef();
			
			int32* GetMaxParticleRef();

			bool* GetEmitterEnabled();

			void SetEditorFeature(bool editorEnabled);

			int32 ParticleCount();

			void DestroySelf();

		};
	}
}