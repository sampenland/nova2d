#include "ParticleSystem.h"
#include "../core/Game.h"

namespace novazero
{
	namespace particles
	{
		using namespace core;

		ParticleSystem::ParticleSystem(const std::string& spriteTexture, Vec2Int size, 
			int32 maxParticles, float particleRadius, unsigned char layer)
		{
			m_ParticleAssetName = spriteTexture;
			m_ParticleRadius = particleRadius;

			m_AssetSize = new Vec2Int(size.x, size.y);
			
			m_BurstAngleMin = 75.f;
			m_BurstAngleMax = 105.f;
			
			m_Layer = layer;
			m_MaxParticles = maxParticles;

			b2ParticleSystemDef psDef;

			if (n2dGetCurrentWorld())
			{
				m_System = n2dGetCurrentWorld()->CreateParticleSystem(&psDef);
				m_System->SetMaxParticleCount(maxParticles);
				m_System->SetRadius(n2dPixelsToMeters(particleRadius));
			}
			else
			{
				LOGO(LVL_NFE, "Particle system not created.");
			}
		}

		int32 ParticleSystem::CreateParticle(b2ParticleFlag type, 
			Vec2 position, Vec2 velocity, Color color, bool customFilter)
		{
			if (!m_System) return -1;
			if (m_System->GetParticleCount() >= m_MaxParticles) return -1;

			b2ParticleDef pd;
			if (customFilter)
			{
				pd.flags = type | b2_destructionListenerParticle | b2_fixtureContactFilterParticle | b2_particleContactFilterParticle;
			}
			else
			{
				pd.flags = type | b2_destructionListenerParticle;
			}

			pd.velocity.Set(velocity.x, velocity.y);
			pd.color.Set((uint8)color.r, (uint8)color.g, (uint8)color.b, (uint8)color.a);
			
			b2Vec2 pos = Vec2::PixelsToMeters(position);
			pd.position.Set(pos.x, pos.y);

			Sprite* sprite = new Sprite(m_ParticleAssetName, 
				position, *m_AssetSize, m_Layer, m_Scale);

			Particle* particle = new Particle(sprite, this);
			pd.userData = (void*)particle;
			
			float lifetime = n2dRandomFloat(m_MinLifeTime, m_MaxLifeTime);
			pd.lifetime = lifetime; 

			int32 index = m_System->CreateParticle(pd);			
			particle->SetIndex(index);

			if (n2dDebugVerbose)
			{
				LOGS("[Created Particle_" + tostring(index) + " ]");
			}

			m_Particles[index] = particle;

			return index;
		}

		void ParticleSystem::Update()
		{
			if (m_EditorFeatureOnly)
			{
				if (m_System->GetRadius() != n2dPixelsToMeters(m_ParticleRadius))
				{
					m_System->SetRadius(n2dPixelsToMeters(m_ParticleRadius));
				}
			}

			const b2Vec2* positions = m_System->GetPositionBuffer();

			for (int i = 0; i < m_System->GetParticleCount(); i++)
			{
				const b2Vec2 pos = positions[i];
				const Vec2 screenPos = Vec2::MetersToPixels(pos);

				if (m_Particles[i])
				{
					m_Particles[i]->UpdatePosition(
						screenPos.x - ((*m_AssetSize).x * m_Scale)* 0.5f, 
						screenPos.y - ((*m_AssetSize).y * m_Scale)* 0.5f
					);
				}
				else
				{
					LOGS("null particle");
				}
			}
		}

		/*
			customFilter will make particles NOT collide with anything unless told to
			spread is the radius of the emitter (higher spread will prevent particle creation collision)
		*/
		void ParticleSystem::BurstParticles(int32 particleCount, Vec2 burstPosition, float velocity, float spread, bool customFilter)
		{
			for (int i = 0; i < particleCount; i++)
			{
				float deg = n2dRandomFloat(0, 360);
				Vec2 dir = Vec2::UnitVec2FromAngle(deg);
				Vec2 vel = Vec2(dir.x, dir.y);

				vel.multiply(Vec2(velocity, velocity));
				burstPosition += dir.scale(spread);

				CreateParticle(b2_waterParticle, burstPosition, vel, *n2dGetColor("white"), customFilter);
			}
		}

		/*
			customFilter will make particles NOT collide with anything unless told to
			spread is the radius of the emitter (higher spread will prevent particle creation collision)
		*/
		void ParticleSystem::BurstParticles(int32 particleCount, Vec2 burstPosition, 
			float velocity, float spread, float minAngleDeg, float maxAngleDeg, bool customFilter)
		{
			for (int i = 0; i < particleCount; i++)
			{
				float deg = n2dRandomFloat(minAngleDeg, maxAngleDeg) - 180;
				Vec2 dir = Vec2::UnitVec2FromAngle(deg);
				Vec2 vel = Vec2(dir.x, dir.y);
				
				vel.multiply(Vec2(velocity, velocity));
				burstPosition += dir.scale(spread);

				CreateParticle(b2_waterParticle, burstPosition, vel, *n2dGetColor("white"), customFilter);
			}
		}

		void ParticleSystem::RemoveParticle(int32 index)
		{
			if (!m_System) return;

			if (m_Particles.find(index) != m_Particles.end())
			{
				m_System->DestroyParticle(index);				
				m_Particles.erase(index);

				if (n2dDebugVerbose)
					LOGS("Particle custom removed: " + tostring(index));
			}
			else
			{
				LOGS("Unknown particle");
			}
		}

		void ParticleSystem::SetLifetime(float minSeconds, float maxSeconds)
		{
			m_System->SetDestructionByAge(true);
			m_UsingLifetime = true;
			m_MinLifeTime = minSeconds;
			m_MaxLifeTime = maxSeconds;
		}

		void ParticleSystem::ConfigureEmitter(std::string assetPath, bool enableEmitter, float emitSpeed, 
			float emitVelocity, float emitSpread, Vec2 burstPosition)
		{
			m_EmitterEnabled = enableEmitter;

			m_AssetPath = new char[MAX_ASSET_PATH];
			std::strcpy(m_AssetPath, assetPath.c_str());

			m_EmitVelocity = new float;
			*m_EmitVelocity = emitVelocity;

			m_EmitterSpeed = emitSpeed;

			m_EmitSpread = new float;
			*m_EmitSpread = emitSpread;

			m_BurstPosition = burstPosition;

			if (m_EmitTimer)
				m_EmitTimer->DestroySelf();

			float* speed = &m_EmitterSpeed;
			m_EmitTimer = new Timer(speed, speed, [=]() {

				if (m_EmitterEnabled)
				{
					BurstParticles(1, m_BurstPosition, *m_EmitVelocity, *m_EmitSpread, 
						m_BurstAngleMin, m_BurstAngleMax);
				}

			});

		}

		int32 ParticleSystem::ParticleCount()
		{
			if (!m_System) return 0;
			return m_System->GetParticleCount();
		}

		char* ParticleSystem::GetAssetPath()
		{
			return m_AssetPath;
		}

		void ParticleSystem::SetScale(float scale)
		{
			m_Scale = scale;
		}

		float ParticleSystem::GetEmitAngleMin()
		{
			return m_BurstAngleMin;
		}

		float ParticleSystem::GetEmitAngleMax()
		{

			return m_BurstAngleMax;
		}

		float* ParticleSystem::GetEmitAngleMinRef()
		{
			return &m_BurstAngleMin;
		}

		float* ParticleSystem::GetEmitAngleMaxRef()
		{

			return &m_BurstAngleMax;
		}
		
		float* ParticleSystem::GetEmitterSpeedRef()
		{
			return &m_EmitterSpeed;
		}

		float* ParticleSystem::GetMinLifeTimeRef()
		{
			return &m_MinLifeTime;
		}

		float* ParticleSystem::GetMaxLifeTimeRef()
		{
			return &m_MaxLifeTime;
		}

		float* ParticleSystem::GetParticleRadiusRef()
		{
			return &m_ParticleRadius;
		}

		int32* ParticleSystem::GetMaxParticleRef()
		{
			return &m_MaxParticles;
		}

		void ParticleSystem::SetEditorFeature(bool editorEnabled)
		{
			m_EditorFeatureOnly = editorEnabled;
		}

		bool* ParticleSystem::GetEmitterEnabled()
		{
			return &m_EmitterEnabled;
		}
		
		void ParticleSystem::DestroySelf()
		{
			if (n2dGetCurrentWorld())
			{
				n2dGetCurrentWorld()->DestroyParticleSystem(m_System);
			}
		}
	}
}